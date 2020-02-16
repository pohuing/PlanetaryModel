#pragma once
#include <GLM/glm.hpp>
#include <string>

class Camera 
{
public:
	Camera();
	glm::mat4 GetViewMatrix();
	void MovePosition(glm::vec3 offset);
	void MoveForward(float distance);
	void MoveRelative(glm::vec3 offset);
	void PointTo(float degrees);
	void Turn(float degrees_x, float degrees_y);
	void TurnY(float degrees);
	void TurnX(float degrees);

private:
	// Where the camera is
	glm::vec3 m_eye;
	// Where it's looking at
	glm::vec3 m_center;
	// Which direction up is in
	glm::vec3 m_up;
};