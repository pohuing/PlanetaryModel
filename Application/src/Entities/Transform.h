#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "../Entities/Transform.h"

class Transform {
public:
	Transform();
	Transform(glm::vec3 translation);

	glm::vec3 GetTranslation() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	glm::mat4 GetModelMatrix() const;

	void SetTranslation(float x, float y, float z);
	void SetRotation(float pitch, float yaw, float roll);
	void SetScale(float x, float y, float z);

	Transform operator+(const glm::vec3& offset);
	void operator+=(const glm::vec3& offset);
	void operator+=(const Transform& other);

private:
	glm::vec3 m_translation;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};