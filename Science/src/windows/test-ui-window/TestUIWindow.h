#pragma once

#include "window/Window.h"

#include "opengl/program/Program.h"
#include "opengl/vertex-array/VertexArray.h"
#include "opengl/vertex-buffer/VertexBuffer.h"
#include "opengl/vertex-buffer/layout/VertexBufferLayout.h"

namespace test
{
	class TestUIWindow : public core::Window
	{
	public:
		TestUIWindow(const int w, const int h);
		~TestUIWindow();
	public:
		void OnStarted() override;
		void OnUpdate(float dt) override;
		void OnKeyAction(int key, int scancode, int action, int mods) override;

		void OnMouseMoveAction(double xpos, double ypos) override;
		void OnMouseButtonAction(int button, int action, int mods) override;
		void OnScrollAction(double xoffset, double yoffset) override;

	private:
		// order in initialization list depends on order of next declarations
	};
}


