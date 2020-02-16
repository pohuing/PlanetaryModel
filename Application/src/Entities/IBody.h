#pragma once
#include <iostream>
#include "../Rendering/ShaderProgramm.h"
#include "GLEW/glew.h"


class IBody {
public:
	virtual void Update() = 0;
	virtual void Draw(const Shaderprogramm& shaderprogramm) = 0;
};
