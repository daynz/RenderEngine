#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Engine
{
public:
	static Engine* instance();
	static Engine* instance(unsigned int scrW, unsigned int scrH);

#pragma region get
	unsigned int scrWidth()const;
	unsigned int scrHeight()const;
	GLFWwindow* window()const;
	

#pragma endregion get

#pragma region set


#pragma endregion set

	static void clearup();
	void renderLoop();

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
	GLFWwindow* m_Window;
};