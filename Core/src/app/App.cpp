#include "App.h"

#include <iostream>

#include "events/AppEvents.h"
#include "../common/multithreading/events/thread-events/ThreadEvents.h"

app::App::App()
{
	std::cout << "Constructor App" << std::endl;
	//stbi_set_flip_vertically_on_load(1); // flip loading image because of open gl requires image to be flipped
}

app::App::~App()
{
	std::cout << "Destructor App" << std::endl;
}

app::App& app::App::Get()
{
	std::cout << "App GET" << std::endl;

	static App application;
	return application;
}

int app::App::InitGLFW()
{
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	glfwWindowHint(GLFW_SAMPLES, 8);

	return 0;
}

void app::App::Start(core::Window* startWindow)
{
	windows.Add(startWindow);
	Go();
}

void app::App::OnStarted()
{
	eventMap.SetEventLogic<app::OpenWindowEvent>
	(
		[this](app::OpenWindowEvent* e)
		{
			std::cout << "Open window" << std::endl;
			windows.Add(e->wnd);
		}
	);

	eventMap.SetEventLogic<app::TerminateProgramEvent>
	(
		[this](app::TerminateProgramEvent* e)
		{
			std::cout << "Terminate program" << std::endl;

			this->windows.ForEach(
				[](core::Window* window)
				{
					mthreading::StopThreadEvent ev;
					window->PushEvent(&ev);
				}
			);
		}
	);

	eventMap.SetEventLogic<mthreading::ThreadStopedEvent>
	(
		[this](mthreading::ThreadStopedEvent* e)
		{
			std::cout << "Window closed" << std::endl;

			core::Window* window = (core::Window*) (e->thread);
			windows.RemoveByValue(window);

			delete window;
		}
	);
}

void app::App::OnStoped()
{
	std::cout << "__STOPED__" << std::endl;
	glfwTerminate();
}

void app::App::OnHandleEvent(core::IEvent* e)
{
	EmbeddedResolver::OnHandleEvent(e);

	if (this->windows.IsEmpty())
	{
		std::cout << "__STOP__" << std::endl;
		this->Stop();
	}
}
