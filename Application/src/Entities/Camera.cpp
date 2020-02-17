#include "Camera.h"
#include <GLM/ext.hpp>
#include <cmath>
#include <stdio.h>
#include <iostream>
#define PI 3.14159265

Camera::Camera() {
	m_cameraspeed = 1;
	m_eye = glm::vec3(0, 0, -3);
	m_yaw = m_pitch = 0;
	m_up = glm::vec3(0, 1, 0);
	m_center = glm::vec3(0, 0, -2);
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(m_eye, m_center, m_up);
}

void Camera::MovePosition(glm::vec3 offset) {
	m_eye += offset;
	m_center += offset;
}

void Camera::MoveForward() {
	MoveForward(m_cameraspeed);
}

void Camera::MoveForward(float distance) {
	MoveRelative(glm::vec3(distance));
}

void Camera::MoveRelative(glm::vec3 offset) {
	auto directional_change = offset;
	directional_change = directional_change * m_center;
	m_center += directional_change;
	m_eye += directional_change;
}

void Camera::PointTo(float degrees) {
	std::cout << "Unimplemented Point to" << std::endl;
}

void Camera::Turn(float degrees_x, float degrees_y) {
	m_yaw += degrees_y;
	m_pitch += degrees_x;
	UpdateCenter();
}

void Camera::UpdateCenter() {
	glm::vec3 center_relative;
	center_relative.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	center_relative.y = sin(glm::radians(m_pitch));
	center_relative.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_center = m_eye + center_relative;
}
