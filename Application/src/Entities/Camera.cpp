#include "Camera.h"
#include <GLM/ext.hpp>
#include <cmath>
#include <stdio.h>
#include <iostream>
#define PI 3.14159265

Camera::Camera() {
	m_cameraspeed = 1;
	m_eye = glm::vec3(0, 0, 0);
	m_yaw = m_pitch = 0;
	m_up = glm::vec3(0, 1, 0);
	m_relative_center = glm::vec3(0, 0, -1.f);
	m_right = glm::vec3(1, 0, 0);
	m_up = glm::vec3(0, 1, 0);
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(m_eye, m_eye + m_relative_center, m_up);
}

void Camera::MovePosition(glm::vec3 offset) {
	m_eye += offset;
}

void Camera::MoveRelative(DIRECTION offset, float time) {
	float distance = time * m_cameraspeed;
	switch(offset) {
	case DIRECTION::FORWARD:
		m_eye += distance * m_relative_center;
		break;
	case DIRECTION::BACKWARD:
		m_eye -= distance * m_relative_center;
		break;
	case DIRECTION::RIGHT:
		m_eye += distance * m_right;
		break;
	case DIRECTION::LEFT:
		m_eye -= distance * m_right;
		break;
	case DIRECTION::UP:
		m_eye += distance * m_up;
		break;
	case DIRECTION::DOWN:
		m_eye -= distance * m_up;
		break;
	}

	std::cout << "X: " << m_eye.x << " Y: " << m_eye.y << " Z: " << m_eye.z << std::endl;
}

void Camera::PointTo(float degrees) {
	std::cout << "Unimplemented Point to" << std::endl;
}

void Camera::Turn(float degrees_x, float degrees_y) {
	m_yaw += degrees_y;
	m_pitch += degrees_x;
	if(m_pitch > 89) {
		m_pitch = 89.f;
	}else if(m_pitch < -89) {
		m_pitch = -89.f;
	}
	std::cout << "Pitch: " << m_pitch << " Yaw: " << m_yaw << std::endl;
	UpdateCenter();
}

void Camera::UpdateCenter() {
	glm::vec3 center_relative;
	m_relative_center.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_relative_center.y = sin(glm::radians(m_pitch));
	m_relative_center.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_relative_center = glm::normalize(m_relative_center);
	m_right = glm::normalize(glm::cross(m_eye, glm::vec3(0,1,0)));
	m_up = glm::normalize(glm::cross(m_right, m_eye));
}
