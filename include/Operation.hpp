#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Camera.hpp"

class Operation
{
public:
	void processInput(GLFWwindow* window, float deltaTime);
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	static Operation* instance();
	static Operation* instance(int w, int h, Camera camera);
private:
	static Operation* m_Instance;
	Operation(int w, int h, Camera camera);
	int scrWidth = 800;
	int scrHeight = 600;

	int lastX;
	int lastY;

	Camera camera;
};