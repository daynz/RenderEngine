#include "Engine.hpp"

Engine* Engine::instance()
{
	return m_Instance;
}

Engine* Engine::instance(unsigned int scrW, unsigned int scrH)
{
	if (!m_Instance)
	{
		m_Instance = new Engine(scrW, scrH);
	}
	return m_Instance;
}

unsigned int Engine::scrWidth() const
{
	return m_ScrWidth;
}

unsigned int Engine::scrHeight() const
{
	return m_ScrHeight;
}

GLFWwindow* Engine::window() const
{
	return m_Window;
}

Engine::Engine(unsigned int scrW, unsigned int scrH)
	:m_ScrWidth(scrW), m_ScrHeight(scrH)
{
	init();
}

Engine::~Engine()
{
	clearup();
}

void Engine::initImgui()
{
	ImGui::CreateContext();
	const char* glsl_version = "#version 130";
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void Engine::initOpenGL()
{
	glfwInit();
	this->m_Window = glfwCreateWindow(m_ScrWidth, m_ScrHeight, "RenderEngine", nullptr, nullptr);
	if (!this->m_Window)
	{
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_Window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
	}
}

void Engine::init()
{
	initOpenGL();
	initImgui();
}

void Engine::clearup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	if(!m_Instance)
		delete m_Instance;
}

void Engine::renderLoop()
{
	while (!glfwWindowShouldClose(this->m_Window))
	{
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// ************ GUI **************
		ImGui::Begin("a");
		ImGui::Text("hello world");
		ImGui::End();
		// ************ GUI **************

		// Rendering
		ImGui::Render();

		static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_Window);
	}
}

Engine* Engine::m_Instance;
