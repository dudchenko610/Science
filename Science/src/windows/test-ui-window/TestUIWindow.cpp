#include "TestUIWindow.h"

#include <iostream>
#include "app/App.h"
#include "opengl/core/error-checker/ErrorChecker.h"

#include "ui-fb/UIFunctionalBlock.h"

test::TestUIWindow::TestUIWindow(const int w, const int h) : core::Window(w, h, "TestUIWindow")
{
	std::cout << "TestUIWindow Constructor " << std::endl;
}

test::TestUIWindow::~TestUIWindow()
{
	std::cout << "TestUIWindow Destructor " << std::endl;
}

void test::TestUIWindow::OnStarted()
{
	Window::OnStarted();

	std::cout << "TestUIWindow OnStart" << std::endl;

	core::FunctionalBlock* fb =  mthreading::Thread::StartThread<uifb::UIFunctionalBlock>(this);
	functionalBlocks.Add(fb);
}

void test::TestUIWindow::OnUpdate(float dt)
{
	// fps, or maybe some other custom services
}

void test::TestUIWindow::OnKeyAction(int key, int scancode, int action, int mods)
{
	std::cout << " - key_callback_ - Key was pressed " << key << std::endl;

	if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	{
		std::cout << " - 0 - GLFW_PRESS " << key << std::endl;

		CloseWindow();
	}
	
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		app::OpenWindowEvent ev( mthreading::Thread::StartThread<test::TestUIWindow>(1000, 600) );
		app::App::Get().PushEvent( &ev );
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		app::TerminateProgramEvent ev;
		app::App::Get().PushEvent( &ev );
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		

	}


}

void test::TestUIWindow::OnMouseMoveAction(double xpos, double ypos)
{
}

void test::TestUIWindow::OnMouseButtonAction(int button, int action, int mods)
{
	Window::OnMouseButtonAction(button, action, mods);
}

void test::TestUIWindow::OnScrollAction(double xoffset, double yoffset)
{
}
