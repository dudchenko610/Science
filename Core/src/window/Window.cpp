#include "Window.h"

#include <iostream>
#include <chrono> 

#include "../app/App.h"


static std::mutex globMtx;

void GLAPIENTRY  debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	// Convert GLenum parameters to strings

//	std::cout << "Source = " << source << std::endl;
//	std::cout << "Message = " << message << std::endl;

	//printf("%s:%s[%s](%d): %s\n", sourceStr, typeStr, severityStr, id, message);
}

core::Window::Window(const int w, const int h, const char* l) :
	width(w), height(h), label(l), glfwWindow(nullptr), time(0), mthreading::ResolverWorkerThread()
{
	std::cout << "Window Constructor" << std::endl;
}

core::Window::~Window()
{
	std::cout << "Window Destructor" << std::endl;

	// Some window sends terminate message to app -> app sends close message to window -> window sends close message to functional blocks
}

void core::Window::Run()
{
	globMtx.lock();

	glfwSetErrorCallback(&core::Window::ErrorCallback);

	glfwWindow = glfwCreateWindow(width, height, label, NULL, NULL);

	if (!glfwWindow)
	{
		globMtx.unlock();

		app::WindowCrushedEvent ev(this);
		app::App::Get().PushEvent( &ev );

		return;
	}

	// Error
	glfwSetWindowUserPointer(glfwWindow, this);

	// Key
	glfwSetKeyCallback(glfwWindow, &core::Window::KeyCallback);

	// Mouse
	glfwSetCursorPosCallback(glfwWindow, &core::Window::MouseMoveCallback);
	glfwSetMouseButtonCallback(glfwWindow, &core::Window::MouseButtonCallback);
	glfwSetScrollCallback(glfwWindow, &core::Window::ScrollCallback);

	glfwMakeContextCurrent(glfwWindow);
	glfwSwapInterval(1);

	globMtx.unlock();

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error while GLEW init!" << std::endl;
	}

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);
	const unsigned char* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	int major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	//std::cout << std::endl;


	printf("GL Vendor            : %s\n", vendor);
	printf("GL Renderer          : %s\n", renderer);
	printf("GL Version (string)  : %s\n", version);
	printf("GL Version (integer) : %d.%d\n", major, minor);
	printf("GLSL Version         : %s\n", glslVersion);

	/*

	GLint nExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
	for (int i = 0; i < nExtensions; i++)
		printf("%s\n", glGetStringi(GL_EXTENSIONS, i));


	*/

	//std::cout << glGetString(GL_VERSION) << std::endl;

	glDebugMessageCallback(debugCallback, NULL);

	this->eventST = mthreading::Thread::StartThread<core::EventSpreaderThread>(this);
	this->OnStarted();

	functionalBlocks.ForEach(
		[](core::FunctionalBlock* fb)
		{
			fb->OnStartWindow();
		}
	);

	std::chrono::time_point<std::chrono::steady_clock> startPoint = std::chrono::high_resolution_clock::now();

	std::chrono::microseconds delay;
	float dt;

	while (!glfwWindowShouldClose(glfwWindow))
	{

		delay = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startPoint);
		startPoint = std::chrono::high_resolution_clock::now();

		dt = delay.count() / 1000000.0f;
		time += dt;

		functionalBlocks.ForEach(
			[this, &dt](core::FunctionalBlock* fb)
			{
				fb->OnUpdateWindow(dt, time);
			}
		);

		this->OnUpdate(dt);

		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();

		CheckForEvents();

	}

	globMtx.lock();
	glfwDestroyWindow(glfwWindow);
	globMtx.unlock();

	this->OnStoped();
	
}

void core::Window::OnStarted()
{
	eventMap.SetEventLogic<mthreading::StopThreadEvent>
	(
		[this](mthreading::StopThreadEvent* e)
		{
			CloseWindow();
		}
	);

	eventMap.SetEventLogic<mthreading::ThreadStopedEvent>
	(
		[this](mthreading::ThreadStopedEvent* e)
		{
			if (e->thread == this->eventST)
			{
				std::cout << "WINDOW THREAD_STOPED EventSpreaderThread" << std::endl;

				delete this->eventST;
				this->eventST = nullptr;

			}
			else
			{
				core::FunctionalBlock* fb = reinterpret_cast<FunctionalBlock*>(e->thread);
				functionalBlocks.RemoveByValue(fb);

				delete fb;
			}

			if (functionalBlocks.GetSize() == 0 && this->eventST == nullptr)
			{
				std::cout << "WINDOW glfwSetWindowShouldClose" << std::endl;
				glfwSetWindowShouldClose(this->glfwWindow, GLFW_TRUE);
			}
		}
	);

}

void core::Window::OnStoped()
{
	std::cout << "Window OnStoped" << std::endl;

	mthreading::ThreadStopedEvent ev(this);
	app::App::Get().PushEvent( &ev );
}


void core::Window::GetCursorPosition(double* xpos, double* ypos)
{
	glfwGetCursorPos(glfwWindow, xpos, ypos);
}


void core::Window::GetWindowSize(int* width, int* height)
{
	*width = this->width;
	*height = this->height;
}


void core::Window::CloseWindow()
{
	mthreading::StopThreadEvent ev;
	this->eventST->PushEvent( &ev );


	functionalBlocks.ForEach(
		[](core::FunctionalBlock* fb)
		{
			mthreading::StopThreadEvent e;
			fb->PushEvent( &e );
		}
	);


}


