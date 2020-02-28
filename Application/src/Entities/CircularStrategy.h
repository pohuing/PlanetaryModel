#pragma once
#include "IStrategy.h"
#include "Transform.h"

class CircularStrategy : public IStrategy
{
public:
	CircularStrategy() = default;
	CircularStrategy(double distance);
	CircularStrategy(double distance, double time_offset);
	CircularStrategy(double distance, double time_offset, double time_multiplier);
	glm::vec3 Update(double time, Transform target) override;
private:
	double m_distance = 0;
	double m_time_offset = 0;
	double m_multiplier = 1;
};