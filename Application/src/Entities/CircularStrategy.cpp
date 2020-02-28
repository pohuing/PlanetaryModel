#include "CircularStrategy.h"

CircularStrategy::CircularStrategy(double distance)
	:m_distance(distance)
{
	
}

CircularStrategy::CircularStrategy(double distance, double time_offset)
	:m_distance(distance), m_time_offset(time_offset)
{
}

CircularStrategy::CircularStrategy(double distance, double time_offset, double time_multiplier)
	: m_distance(distance), m_time_offset(time_offset), m_multiplier(time_multiplier)
{
}

glm::vec3 CircularStrategy::Update(double time, Transform target)
{
	auto target_location = target.GetTranslation();
	return glm::vec3(
		sin(time * m_multiplier +m_time_offset) * m_distance + target_location.x,
		target_location.y, 
		cos(time * m_multiplier +m_time_offset) * m_distance + target_location.z);
}
