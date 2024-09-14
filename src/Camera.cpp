#include "Camera.hpp"
#include <iostream>
Camera::Camera(glm::vec3 m_Position, glm::vec3 m_Front, glm::vec3 m_Up, float m_Fov_Y, float m_Near, float m_Far, float m_Yaw, float m_Pitch, float m_Roll, float m_Speed, float m_Sensitivity, float m_Zoom, int scrWidth, int scrHeight)
	:m_Position(m_Position), m_Front(m_Front), m_Up(m_Up), m_Fov_Y(m_Fov_Y), m_Near(m_Near), m_Far(m_Far), m_Yaw(m_Yaw), m_Pitch(m_Pitch), m_Roll(m_Roll), m_Speed(m_Speed), m_Sensitivity(m_Sensitivity), m_Zoom(m_Zoom), scrWidth(scrWidth), scrHeight(scrHeight)
{
	m_Aspect = (float)scrWidth / (float)scrHeight;
	m_WorldUp = m_Up;
	updateCameraVectors();
}

Camera::Camera(int scrw, int scrh)
	:Camera()
{
	this->scrWidth = scrw;
	this->scrHeight = scrh;
	m_Aspect = (float)scrWidth / (float)scrHeight;
	m_WorldUp = m_Up;
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = m_Speed * deltaTime;
	if (direction == FORWARD)
		m_Position += m_Front * velocity;
	if (direction == BACKWARD)
		m_Position -= m_Front * velocity;
	if (direction == LEFT)
		m_Position -= m_Right * velocity;
	if (direction == RIGHT)
		m_Position += m_Right * velocity;
	if (direction == UP)
		m_Position = glm::vec3(m_Position.x, m_Position.y + velocity, m_Position.z);
	if (direction == DOWN)
		m_Position = glm::vec3(m_Position.x, m_Position.y - velocity, m_Position.z);
	if (direction == TURELEFT)
		m_Position;
	if (direction == TURERIGHT)
		m_Position;
	if (direction == SPEEDUP)
		m_Speed = 10.0f;
	if (direction == SPEEDDOWN)
		m_Speed = 2.5f;
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= m_Sensitivity;
	yoffset *= m_Sensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	if (constrainPitch)
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
	m_Zoom -= (float)yoffset;
	if (m_Zoom < 1.0f)
		m_Zoom = 1.0f;
	if (m_Zoom > 45.0f)
		m_Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw))/* * cos(glm::radians(m_Roll))*/;
	front.y = sin(glm::radians(m_Pitch))/* * sin(glm::radians(m_Roll))*/; 
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	//show();
}

void Camera::position(const glm::vec3& p)
{
	this->m_Position = p;
}

glm::vec3 Camera::position() const
{
	return m_Position;
}

void Camera::front(const glm::vec3& f)
{
	this->m_Front = f;
}

glm::vec3 Camera::front() const
{
	return m_Front;
}

void Camera::up(const glm::vec3& u)
{
	this->m_Up = u;
}

glm::vec3 Camera::up() const
{
	return this->m_Up;
}

void Camera::fovy(float f)
{
	this->m_Fov_Y = f;
}

float Camera::fovy() const
{
	return m_Fov_Y;
}

void Camera::aspect(float a)
{
	this->m_Aspect = a;
}

float Camera::aspect() const
{
	return m_Aspect;
}

void Camera::near(float n)
{
	this->m_Near = n;
}

float Camera::near() const
{
	return m_Near;
}

void Camera::far(float f)
{
	this->m_Far = f;
}

float Camera::far() const
{
	return m_Far;
}

void Camera::yaw(float y)
{
	this->m_Yaw = y;
}

float Camera::yaw() const
{
	return m_Yaw;
}

void Camera::pitch(float p)
{
	this->m_Pitch = p;
}

float Camera::pitch() const
{
	return m_Pitch;
}

void Camera::roll(float r)
{
	this->m_Roll = r;
}

float Camera::roll() const
{
	return m_Roll;
}

void Camera::speed(float s)
{
	this->m_Speed = s;
}

float Camera::speed() const
{
	return m_Speed;
}

void Camera::sensitivity(float s)
{
	this->m_Sensitivity = s;
}

float Camera::sensitivity() const
{
	return m_Sensitivity;
}

void Camera::zoom(float z)
{
	this->m_Zoom = z;
}

float Camera::zoom() const
{
	return m_Zoom;
}

void Camera::show() const
{
	std::cout << m_Position.x << "," << m_Position.y << "," << m_Position.z << std::endl;
}
