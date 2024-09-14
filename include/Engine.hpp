#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Camera.hpp"
#include "Shader.hpp"

class Engine
{
public:
	static Engine* instance();
	static Engine* instance(unsigned int scrW, unsigned int scrH);

	unsigned int scrWidth()const;
	unsigned int scrHeight()const;
	GLFWwindow* window()const;

	static void clearup();
	void renderLoop();

	void setOpenGL();
	void setModel();

	void processInput(GLFWwindow* window, float deltaTime);
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	Shader* shader;
protected:

private:
	Engine(unsigned int scrW,unsigned int scrH);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	~Engine();

	void initImgui();
	void initOpenGL();
	void init();

	static Engine* m_Instance;

	unsigned int m_ScrWidth, m_ScrHeight;
	float deltaTime;
	float lastFrame;

	GLFWwindow* m_Window;
	Camera* camera;
	float lastX;
	float lastY;
	bool firstMouse;

	unsigned int VAO;
};

void testModel(unsigned int& VAO);