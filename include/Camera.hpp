#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	TURELEFT,
	TURERIGHT,
	SPEEDUP,
	SPEEDDOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ROLL = 0.0f;
const float SPEED = 2.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;//变焦

class Camera
{
public:
	Camera(
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f),
		float m_Fov_Y = 45.0f,
		float m_Near = 0.1f,
		float m_Far = 100.0f,
		float m_Yaw = YAW,
		float m_Pitch = PITCH,
		float m_Roll = ROLL,
		float m_Speed = SPEED,
		float m_Sensitivity = SENSITIVITY,
		float m_Zoom = ZOOM,
		int scrWidth = 800,
		int scrHeight = 600
	);
	Camera(int scrw, int scrh);

	//获取观察矩阵
	glm::mat4 getViewMatrix();

	void processKeyboard(Camera_Movement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void processMouseSroll(float yoffset);

	void position(const glm::vec3& p);
	void front(const glm::vec3& f);
	void up(const glm::vec3& u);
	void fovy(float f);
	void aspect(float a);
	void near(float n);
	void far(float f);
	void yaw(float y);
	void pitch(float p);
	void roll(float r);
	void speed(float s);
	void sensitivity(float s);
	void zoom(float z);

	glm::vec3 position() const;
	glm::vec3 front() const;
	glm::vec3 up() const;
	float fovy() const;
	float aspect() const;
	float near() const;
	float far() const;
	float yaw() const;
	float pitch() const;
	float roll() const;
	float speed() const;
	float sensitivity() const;
	float zoom() const;

	void show()const;

private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	float m_Fov_Y;
	float m_Aspect;
	float m_Near;
	float m_Far;
	float m_Yaw;
	float m_Pitch;
	float m_Roll;
	float m_Speed;
	float m_Sensitivity;
	float m_Zoom;

	int scrWidth;
	int scrHeight;

	void updateCameraVectors();
	
protected:

};