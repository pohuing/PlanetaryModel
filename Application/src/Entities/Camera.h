#pragma once
#include <GLM/glm.hpp>
#include <string>

enum DIRECTION {
	FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN
};


class Camera 
{
public:
	Camera();
	glm::mat4 GetViewMatrix();
	void MovePosition(glm::vec3 offset);
	void MoveRelative(DIRECTION direction, float time);
	void PointTo(float degrees);
	void Turn(float degrees_x, float degrees_y);

private:
	void UpdateCenter();
	// Where the camera is
	glm::vec3 m_eye;
	// Where it's pointing at
	glm::vec3 m_relative_center;
	float m_yaw, m_pitch;
	float m_cameraspeed;
	// Which direction up is in
	glm::vec3 m_right, m_up;
};