#pragma once
#include "../Rendering/Shaderprogram.h"
#include "../Entities/Transform.h"


class IBody {
public:
	virtual void Update() = 0;
	virtual void Draw(const Shaderprogram& shaderprogramm) = 0;
	virtual void Place(Transform newTransform) = 0;
	virtual Transform GetTransform() = 0;
	virtual ~IBody() = default;
};
