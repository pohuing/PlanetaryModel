#pragma once
#include "../Rendering/Shaderprogram.h"
#include "../Entities/Transform.h"


class IBody {
public:
	virtual void Update(double time) = 0;
	virtual void Draw(const Shaderprogram& shaderprogram) = 0;
	virtual void Place(Transform new_transform) = 0;
	virtual Transform GetTransform() = 0;
	virtual ~IBody() = default;
};
