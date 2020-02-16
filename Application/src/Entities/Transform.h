#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

class Transform {
public:
	Transform();

	glm::vec3 GetTranslation();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();
	glm::mat4 GetModelMatrix();

	void SetTranslation(float x, float y, float z);
	void SetRotation(float pitch, float yaw, float roll);
	void SetScale(float x, float y, float z);

private:
	glm::vec3 m_translation;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};