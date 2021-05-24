#include "UIFunctionalBlock.h"

#include <iostream>
#include "window/events/MouseEvents.h"

#include "window/Window.h"
#include "../data-model/view/events/ViewEvents.h"

#include "common/multithreading/state_mutex/state_mutex.h"

#include <cstdlib>

enum RENDER_SYCH : int
{
	WND_LOCKED = 0,
	FREED_BY_WND = 1,
	UI_LOCKED = 2,
	FREED_BY_UI = 3
};

static mthreading::state_mutex wndMtx(RENDER_SYCH::FREED_BY_UI);


static int NUMBER_OF_VIEWS = 40;

uifb::UIFunctionalBlock::UIFunctionalBlock(core::Window* wnd) : BlockingFunctionalBlock(wnd),

	//m_ProjMat(glm::perspective(glm::radians(45.0f), 5.0f / 3.0f, 0.1f, 100.0f)),
	m_ProjMat(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f)),
	VAO(0),
//	count(6),

	width(1000),
	height(600),
	dataModel(NUMBER_OF_VIEWS),

	cameraPos(0.0f, 0.0f, 1.0f),
	m_ViewMat(glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)))

{
	std::cout << "Constructor UIFunctionalBlock" << std::endl;
}

uifb::UIFunctionalBlock::~UIFunctionalBlock()
{
	std::cout << "Destructor UIFunctionalBlock" << std::endl;
}

void uifb::UIFunctionalBlock::OnAssignWindowListeners()
{
	windowPrepareEM.SetEventLogic<core::mouse::ClickEvent>
	(
		[this](core::mouse::ClickEvent* clc)
		{

			if (clc->button == GLFW_MOUSE_BUTTON_RIGHT && clc->action == GLFW_PRESS)
			{
				double x, y;
				wnd->GetCursorPosition(&x, &y);

				int width = 0, height = 0;
				wnd->GetWindowSize(&width, &height);

				int _y = height - y;
				int _x = x;

				int offset = _y * width * 16 + _x * 16;

				glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO_Counters);
				glGetNamedBufferSubData(SSBO_Counters, offset, 4 * sizeof(unsigned int), clc->out_data);
			}
		}
	);
}

void uifb::UIFunctionalBlock::OnAssignSpreaderListeners()
{
	eventSprThEM.SetEventLogic<core::mouse::ClickEvent>
	(
		[](core::mouse::ClickEvent* clc)
		{
			return true; //clc->out_data[0] != 0xFFFFFFFF;
		}
	);
}

void uifb::UIFunctionalBlock::OnInitScene()
{
	//https://www.bfilipek.com/2015/01/persistent-mapped-buffers-in-opengl.html#persistence
	
	m_RenderProg = new opengl::Program("res/shaders/test-ui", "VS.glsl", "FS.glsl", "GS.glsl");
	m_RenderProg->Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	m_RenderProg->SetUniformMat4f("u_Projection", this->m_ProjMat);
	m_RenderProg->SetUniformMat4f("u_View", m_ViewMat);
	m_RenderProg->SetUniformMat4f("u_Model", model);

	this->pass1Id = glGetSubroutineIndex(m_RenderProg->GetId(), GL_FRAGMENT_SHADER, "pass1");
	this->pass2Id = glGetSubroutineIndex(m_RenderProg->GetId(), GL_FRAGMENT_SHADER, "pass2");

	// Setup the main VAO
	{
		// set up the VAO
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
	
		// view's VBO
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, NUMBER_OF_VIEWS * sizeof(data::ViewVertex), nullptr, GL_DYNAMIC_COPY); // allocates new memory (pinned memory) 

		unsigned int stride = sizeof(data::ViewVertex);

		// setup data layout
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (const void*) offsetof(data::ViewVertex, pos));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (const void*) offsetof(data::ViewVertex, dimension));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride, (const void*) offsetof(data::ViewVertex, color));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, stride, (const void*) offsetof(data::ViewVertex, parentIndex));


		// indices VBO
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUMBER_OF_VIEWS * sizeof(unsigned int), nullptr, GL_DYNAMIC_COPY);


		// bind buffer of VBO as SSBO
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, VBO); // 0 - binding point

		// ssbo counters
		glGenBuffers(1, &SSBO_Counters);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, SSBO_Counters); // 1 - binding point

		glBufferData(GL_SHADER_STORAGE_BUFFER, this->width * this->height * 4 * sizeof(GLuint), NULL, GL_DYNAMIC_DRAW);  // for my screen it is 17 920 000 bytes
		glClearNamedBufferData(SSBO_Counters, GL_RGBA32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, clearVals);
	}


	// Setup the plane VAO
	{

		glGenVertexArrays(1, &planeVAO);
		glBindVertexArray(planeVAO);

		data::ViewVertex vertData = { {0.0f, 0.0f},   {2.0f, 2.0f},   {1.0f, 0.0f, 0.0f, 1.0f},  0 };

		unsigned int stride = sizeof(data::ViewVertex);

		glGenBuffers(1, &planeVBO);

		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(data::ViewVertex), &vertData, GL_DYNAMIC_COPY);

		// setup data layout
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (const void*)offsetof(data::ViewVertex, pos));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (const void*)offsetof(data::ViewVertex, dimension));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride, (const void*)offsetof(data::ViewVertex, color));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, stride, (const void*)offsetof(data::ViewVertex, parentIndex));


	}


	// should be in update
	glViewport(0, 0, this->width, this->height);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glEnable(GL_MULTISAMPLE);
	glEnable(GL_POLYGON_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void uifb::UIFunctionalBlock::OnUpdateWindow(float dt, float time)
{
	if (wndMtx.try_lock(RENDER_SYCH::FREED_BY_UI, RENDER_SYCH::WND_LOCKED))
	{
		// copy data from ui-fb to opengl side

		std::cout << " ____ copy data from ui-fb to opengl side ____ view number = " << this->dataModel.GetViewNumber() << std::endl;

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, NUMBER_OF_VIEWS * 36, this->dataModel.GetVertexData());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->dataModel.GetViewNumber() * sizeof(unsigned int), this->dataModel.GetIndexData());


		wndMtx.unlock(RENDER_SYCH::FREED_BY_WND);
	}

	m_RenderProg->Bind();
	glBindVertexArray(VAO);

	//m_RenderProg->SetUniformMat4f("u_View", m_ViewMat);

	// pass 1
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &this->pass1Id);
	glClearNamedBufferData(SSBO_Counters, GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT, clearVals);

	glDrawElements(GL_POINTS, this->dataModel.GetViewNumber(), GL_UNSIGNED_INT, nullptr);

	//glMemoryBarrier(GL_FRAMEBUFFER_BARRIER_BIT);

	// pass 2
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &this->pass2Id);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(planeVAO);

	//m_RenderProg->SetUniformMat4f("u_View", glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	glDrawArrays(GL_POINTS, 0, 1);
}


void uifb::UIFunctionalBlock::OnStarted()
{
	BlockingFunctionalBlock::OnStarted();

	eventMap.SetEventLogic<core::mouse::ClickEvent>
	(
		[this](core::mouse::ClickEvent* clc)
		{
			if (clc->button == GLFW_MOUSE_BUTTON_LEFT && clc->action == GLFW_PRESS)
			{
			//	std::cout << "vec2 = " << sizeof(glm::f32vec2) << std::endl;
			//	std::cout << "vec4 = " << sizeof(glm::f32vec4) << std::endl;
			//	std::cout << "data::ViewVertex = " << sizeof(data::ViewVertex) << std::endl;


				std::cout << "GLFW_MOUSE_BUTTON_LEFT, view number = " << dataModel.GetViewNumber() <<  std::endl;

				double x, y;
				wnd->GetCursorPosition(&x, &y);

				int width = 0, height = 0;
				wnd->GetWindowSize(&width, &height);

				float _y = (height - y) / (float) height;
				float _x = x / (float) width;

				_y = 2 * _y - 1;
				_x = 2 * _x - 1;

				std::cout << "x = " << _x << " y = " << _y << std::endl;

				float r = rand() / (float) RAND_MAX;
				float b = rand() / (float) RAND_MAX;
				float g = rand() / (float) RAND_MAX;

				interface::CreateViewEvent ev({_x, _y}, {0.2f, 0.2f}, {r, b, g, 0.7f});
				PushEvent(&ev);
			}

			if (clc->button == GLFW_MOUSE_BUTTON_RIGHT && clc->action == GLFW_PRESS)
			{
				std::cout << "out_data[0, r] = " << clc->out_data[0] << std::endl;
				std::cout << "out_data[1, g] = " << clc->out_data[1] << std::endl;
				std::cout << "out_data[2, b] = " << clc->out_data[2] << std::endl;
				std::cout << "out_data[3, a] = " << clc->out_data[3] << std::endl;
			}
			
		}
	);

	eventMap.SetEventLogic<interface::CreateViewEvent>
	(
		[this](interface::CreateViewEvent* clc)
		{
			std::cout << "interface::CreateViewEvent" << std::endl;

			wndMtx.lock(RENDER_SYCH::FREED_BY_UI, RENDER_SYCH::FREED_BY_WND, RENDER_SYCH::UI_LOCKED);
			dataModel.CreateView(clc);
			wndMtx.unlock(RENDER_SYCH::FREED_BY_UI);

			std::cout << "CREATED" << std::endl;
		}
	);

}