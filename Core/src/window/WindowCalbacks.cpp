#include "Window.h"

#include <iostream>

#include "./events/MouseEvents.h"




void core::Window::ErrorCallback(int error, const char* description)
{
	std::cout << "code = " << error << " description = " << description << std::endl;
}

void core::Window::OnMouseButtonAction(int button, int action, int mods)
{
	core::mouse::ClickEvent clk(button, action, mods);
	eventST->PushEvent(&clk);
}

void core::Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* myWnd = (Window*)glfwGetWindowUserPointer(window);
	myWnd->OnKeyAction(key, scancode, action, mods);
}

void core::Window::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	Window* myWnd = (Window*)glfwGetWindowUserPointer(window);
	myWnd->OnMouseMoveAction(xpos, ypos);
}

void core::Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Window* myWnd = (Window*)glfwGetWindowUserPointer(window);
	myWnd->OnMouseButtonAction(button, action, mods);
}

void core::Window::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* myWnd = (Window*)glfwGetWindowUserPointer(window);
	myWnd->OnScrollAction(xoffset, yoffset);
}