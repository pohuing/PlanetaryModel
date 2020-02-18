#pragma once
#include <iostream>
#include "../Rendering/ShaderProgramm.h"
#include "../Entities/Transform.h"
#include "GLEW/glew.h"


class IBody {
public:
	virtual void Update() = 0;
	virtual void Draw(const Shaderprogramm& shaderprogramm) = 0;
	virtual void Place(Transform newTransform) = 0;
	virtual Transform GetTransform() = 0;
};
