#pragma once

#include "functional-block/blocking-fb/BlockingFunctionalBlock.h"
#include "opengl/program/Program.h"

#include "../data-model/DataModel.h"

namespace uifb
{
	class UIFunctionalBlock : public core::BlockingFunctionalBlock
	{
	public:
		UIFunctionalBlock(core::Window* wnd);
		virtual ~UIFunctionalBlock();
	public:
		virtual void OnInitScene() override;
		virtual void OnAssignWindowListeners() override;
		virtual void OnAssignSpreaderListeners() override;
		virtual void OnUpdateWindow(float dt, float time) override;
	public:
	protected:
		void OnStarted() override;
	protected:
		data::DataModel dataModel;

		glm::vec3 cameraPos;

		opengl::Program* m_RenderProg;

		glm::mat4 m_ProjMat;
		glm::mat4 m_ViewMat;
		glm::mat4 m_ModelMat;


		GLuint VAO;
		GLuint VBO;
		GLuint IBO;

		GLuint planeVBO;
		GLuint planeVAO;
		GLuint planeIBO;

		GLuint SSBO_Counters;
		GLuint SSBO_Buffer;

		unsigned int pass1Id;
		unsigned int pass2Id;

		GLuint clearVals[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF }; // 0xFFFFFFFF;

		
	//	unsigned int count;

		int width;
		int height;
	};
}



