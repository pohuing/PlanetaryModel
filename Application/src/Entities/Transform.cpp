#include "Transform.h"

Transform::Transform() {
	m_translation = glm::vec3{ 0.f, 0.f, 0.f };
	m_rotation = glm::vec3{ 0.f, 0.f, 0.f };
	m_scale = glm::vec3{ 1.0f, 1.0f, 1.0f };
}

Transform::Transform(glm::vec3 translation)
	:m_translation(translation) {
	m_rotation = glm::vec3(0);
	m_scale = glm::vec3(1);
}
Transform::Transform(glm::vec3 translation, glm::vec3 scale)
	: m_translation(translation), m_scale(scale) {
	m_rotation = glm::vec3(0);
}
;

glm::mat4 Transform::GetModelMatrix() const {
	glm::mat4 translation = glm::translate(glm::mat4(1.f), m_translation);

	glm::vec3 rot = m_rotation;
	glm::mat4 rotationX = glm::rotate(glm::mat4(1.f), glm::radians(rot.x), glm::vec3(1.f, 0.f, 0.0f));
	glm::mat4 rotationY = glm::rotate(glm::mat4(1.f), glm::radians(rot.y), glm::vec3(0.f, 1.f, 0.0f));
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1.f), glm::radians(rot.z), glm::vec3(0.f, 0.f, 1.0f));

	glm::mat4 finalRot = rotationX * rotationY * rotationZ;

	glm::mat4 scale = glm::scale(glm::mat4(1.f), m_scale);

	return translation * finalRot * scale;
}

glm::vec3 Transform::GetTranslation() const {
	return m_translation;
}

glm::vec3 Transform::GetRotation()const {
	return m_rotation;
}

glm::vec3 Transform::GetScale()const {
	return m_scale;
}

void Transform::SetTranslation(float x, float y, float z) {
	m_translation.x = x;
	m_translation.y = y;
	m_translation.z = z;
}

void Transform::SetRotation(float pitch, float yaw, float roll) {
	m_rotation.x = pitch;
	m_rotation.y = yaw;
	m_rotation.z = roll;
}

void Transform::SetScale(float x, float y, float z) {
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

Transform Transform::operator+(const glm::vec3& offset) const {
	return { m_translation + offset };
}

void Transform::operator+=(const glm::vec3& offset) {
	m_translation += offset;
}

void Transform::operator+=(const Transform& other) {
	m_translation += other.GetTranslation();
}