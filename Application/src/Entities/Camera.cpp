#include "Camera.h"
#include <GLM/ext.hpp>
#include <cmath>
#include <stdio.h>
#include <iostream>
#define PI 3.14159265

Camera::Camera()
{
	m_eye = glm::vec3(0, 0, -3);
	m_center = glm::vec3(0, 0, -2);
	m_up = glm::vec3(0, 1, 0);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_eye, m_center, m_up);
}

void Camera::MovePosition(glm::vec3 offset)
{
	m_eye += offset;
	m_center += offset;
}

void Camera::MoveForward(float distance)
{
	auto direction = m_center - m_eye;
	m_center += distance * direction;
	m_eye += distance * direction;
}

void Camera::MoveRelative(glm::vec3 offset)
{
	auto direction = m_center - m_eye;
	/*if (direction.z == 0 || direction.z >=0.95)
	{
		m_center += offset;
		m_eye += offset;
		return;
	}*/
	//handling backwards movement prolly fixable with a better equation but this is good enough for now
	if (direction.z < 0)
	{
		offset = -offset;
	}
	double radians = 2* PI- atan(direction.x/direction.z);
	double x, z;
	x = offset.x * cos(radians) - offset.z * sin(radians);
	z = offset.x * sin(radians) + offset.z * cos(radians);
	m_center.x += x;
	m_center += offset.y;
	m_center.z += z;
	m_eye.x += x;
	m_eye += offset.y;
	m_eye.z += z;
}

void Camera::PointTo(float degrees)
{
	double x, z;
	x = sin(degrees * PI / 180);
	z = cos(degrees * PI / 180);
	m_center.x = m_eye.x + x;
	m_center.z = m_eye.z + z;
	std::cout << "New vector length: " << glm::length(m_center - m_eye) << std::endl;
	std::cout << "X:" << m_center.x << " Z:" << m_center.z << std::endl;
}

void Camera::Turn(float degrees_x, float degrees_y) {
	TurnY(degrees_y);
	TurnX(degrees_x);
}

void Camera::TurnX(float degrees) {
	float radians = degrees * PI / 180;
	float y, z;
	auto direction_vector = m_center - m_eye;
	y = direction_vector.y * cos(radians) - direction_vector.z * sin(radians);
	z = direction_vector.y * sin(radians) + direction_vector.z * cos(radians);
	m_center.y = m_eye.y + y;
	m_center.z = m_eye.z + z;
	direction_vector = m_center - m_eye;
	std::cout << "Distance Length: " << glm::length(direction_vector) << std::endl;
	std::cout << "Looking into direction y: " << direction_vector.y << " Z: " << direction_vector.z << std::endl;
}

void Camera::TurnY(float degrees)
{
	float radians = degrees * PI / 180;
	float x, z;
	auto direction_vector = m_center - m_eye;
	x = direction_vector.x * cos(radians) - direction_vector.z * sin(radians);
	z = direction_vector.x * sin(radians) + direction_vector.z * cos(radians);
	m_center.x = m_eye.x + x;
	m_center.z = m_eye.z + z;
	direction_vector = m_center - m_eye;
	std::cout << "Distance Length: " << glm::length(direction_vector) << std::endl;
	std::cout << "Looking into direction X: " << direction_vector.x << " Z: " << direction_vector.z << std::endl;
}
