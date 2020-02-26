#include "Strategy.h"

Strategy::Strategy(double distance)
	:m_distance(distance)
{
	
}

Strategy::Strategy(double distance, double time_offset)
	:m_distance(distance), m_time_offset(time_offset)
{
}

Strategy::Strategy(double distance, double time_offset, double time_multiplier)
	: m_distance(distance), m_time_offset(time_offset), m_multiplier(time_multiplier)
{
}

glm::vec3 Strategy::Update(double time, Transform target) const
{
	auto target_location = target.GetTranslation();
	return glm::vec3(
		sin(time * m_multiplier +m_time_offset) * m_distance + target_location.x,
		target_location.y, 
		cos(time * m_multiplier +m_time_offset) * m_distance + target_location.z);
}
