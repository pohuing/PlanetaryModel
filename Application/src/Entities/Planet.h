#pragma once
#include "IBody.h"
#include "../Rendering/ShaderProgramm.h"
#include "Transform.h"
#include "Mesh.h"
#include <vector>
#include <utility>

class Planet : public IBody {
public:
	Planet();
	Planet(Transform transform);

	Planet(Transform transform, Mesh mesh);

	~Planet() {};
	void Draw(const Shaderprogramm& shaderprogramm);
	void Update() {};

	void Place(Transform newPosition);

	Transform GetTransform();

private:
	Mesh m_mesh;
	Transform m_Transform;
};