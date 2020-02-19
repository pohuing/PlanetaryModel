#pragma once
#include "IBody.h"
#include "../Rendering/Shaderprogram.h"
#include "Transform.h"
#include "Mesh.h"


class Planet : public IBody {
public:
	Planet();
	Planet(Transform transform);
	Planet(Transform transform, Mesh&& mesh);
	~Planet() = default;

	void Draw(const Shaderprogram& shaderprogramm) override;
	void Update() override {};
	void Place(Transform newPosition) override;
	Transform GetTransform() override;

private:
	Mesh m_mesh;
	Transform m_Transform;
};