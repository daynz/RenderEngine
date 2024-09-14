#include "Engine.hpp"
#include <iostream>
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
	:m_ScrWidth(scrW), m_ScrHeight(scrH), deltaTime(0.0f), lastFrame(0.0f), firstMouse(true)
{
	init();
	this->lastX = (float)m_ScrWidth / 2.0f;
	this->lastY = (float)m_ScrHeight / 2.0f;
	shader = new Shader("../shader/testModelv.glsl", "../shader/testModelf.glsl");
	camera = new Camera(this->m_ScrWidth, this->m_ScrHeight);
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
	setOpenGL();
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
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		processInput(m_Window, deltaTime);

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// ************ GUI **************
		ImGui::Begin("imgui");
		ImGui::Text("imgui");
		ImGui::End();
		// ************ GUI **************

		// Rendering
		ImGui::Render();

		glClearColor(0.98f, 0.76f, 0.98f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera->zoom()), (float)scrWidth() / (float)scrHeight(), camera->near(), camera->far());
		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		shader->use();
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		shader->setMat4("model", model);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_Window);
	}
}

void Engine::setOpenGL()
{
	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* win, double xpos, double ypos) {
		instance()->mouse_callback(win, xpos, ypos);
	});
	glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xoffset, double yoffset) {
		instance()->scroll_callback(win, xoffset, yoffset);
		});
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
}

void Engine::setModel()
{
	testModel(VAO);
}

Engine* Engine::m_Instance = nullptr;

void Engine::processInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->processKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->processKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->processKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->processKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera->processKeyboard(UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		camera->processKeyboard(DOWN, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camera->processKeyboard(SPEEDUP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		camera->processKeyboard(SPEEDDOWN, deltaTime);
	}
}

void Engine::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = (float)xposIn;
	float ypos = (float)yposIn;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera->processMouseMovement(xoffset, yoffset);
}

void Engine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->processMouseScroll((float)yoffset);
}

void testModel(unsigned int& VAO)
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};

	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_BUFFER, 0);
	glBindVertexArray(0);
}