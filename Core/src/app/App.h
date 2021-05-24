#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../common/multithreading/synchronizers/embedded-resolver/EmbeddedResolver.h" 
#include "../window/Window.h"

#include "collections/array-list/ArrayList.h"


namespace app
{

	class App : public mthreading::EmbeddedResolver
	{
	public:
		App(const App&) = delete;

		static App& Get();
	private:
		App();
		~App();
	public:
		int InitGLFW();
		void Start(core::Window* startWindow);
	public:
		void OnStarted() override;
		void OnStoped() override;

		void OnHandleEvent(core::IEvent* e) override;

	private:
		friend class core::Window;
	private:
		collection::ArrayList<core::Window*> windows;
		friend class core::Window;

		//unsigned int eventEnums[];
	};
}



