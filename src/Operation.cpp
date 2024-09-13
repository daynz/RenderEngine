#include "Operation.hpp"

void Operation::processInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.processKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.processKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.processKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.processKeyboard(RIGHT, deltaTime);
	}
}

void Operation::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = (float)xposIn;
	float ypos = (float)yposIn;

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

void Operation::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseSroll((float)yoffset);
}

Operation* Operation::instance()
{
	return m_Instance;
}

Operation* Operation::instance(int w, int h, Camera camera)
{
	if (!m_Instance)
	{
		m_Instance = new Operation(w, h, camera);
	}
	return m_Instance;
}

Operation* Operation::m_Instance = nullptr;

Operation::Operation(int w, int h, Camera camera)
	:scrWidth(w), scrHeight(h), lastX(w / 2), lastY(h / 2), camera(camera)
{

}

