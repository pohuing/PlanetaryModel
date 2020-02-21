#pragma once
#include "Transform.h"

class Strategy
{
public:
	Strategy() = default;
	Strategy(double distance);
	Strategy(double distance, double time_offset);
	glm::vec3 Update(double time, Transform target) const;
private:
	double m_distance = 0;
	double m_time_offset = 0;
};