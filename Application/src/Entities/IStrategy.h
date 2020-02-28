#pragma once
#include "Transform.h"


class IStrategy
{
public:
	virtual glm::vec3 Update(double time, Transform parent) = 0;
};