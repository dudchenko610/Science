#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <mutex>

#include "../common/multithreading/synchronizers/resolver-thread/resolver-worker-thread/ResolverWorkerThread.h"
#include "../common/multithreading/synchronizers/resolver-thread/resolver-blocking-thread/ResolverBlockingThread.h"
#include "../events/IEvent.h"

#include "collections/queue/thread-safe/QueueSafe.h"
#include "collections/array-list/ArrayList.h"
#include "../functional-block/FunctionalBlock.h"
#include "../app/events/AppEvents.h"
#include "../common/multithreading/events/thread-events/ThreadEvents.h"
#include "../common/identifiable/Identifiable.h"

//#include "../events/Event.h"

#include "event-spreader-thread/EventSpreaderThread.h"

namespace core
{
	class Window  : public mthreading::ResolverWorkerThread
	{
	friend class EventSpreaderThread;
	public:
		Window(const int width, const int height, const char* label);
		virtual ~Window();
	public:
		virtual void OnUpdate(float dt) = 0;

		virtual void OnMouseMoveAction(double xpos, double ypos) = 0;
		virtual void OnMouseButtonAction(int button, int action, int mods);
		virtual void OnScrollAction(double xoffset, double yoffset) = 0;

		virtual void OnKeyAction(int key, int scancode, int action, int mods) = 0;

	public:
		void Run() override;
		void OnStarted() override;
		void OnStoped() override;
	private:
		static void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void ErrorCallback(int error, const char* description);
	public:
		void GetCursorPosition(double* x, double* y);
		void GetWindowSize(int* width, int* height);
	protected:
		void CloseWindow();
	protected:

		core::EventSpreaderThread* eventST; // event spreader thread
		collection::ArrayList<FunctionalBlock*> functionalBlocks;

		GLFWwindow* glfwWindow;

		const int width;
		const int height;
		const char* label;

		float time;
	};
}



