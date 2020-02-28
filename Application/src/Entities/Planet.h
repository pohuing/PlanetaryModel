#pragma once
#include "../Rendering/Shaderprogram.h"
#include "IBody.h"
#include "Mesh.h"
#include "CircularStrategy.h"
#include "Transform.h"


class Planet : public IBody {
public:
	Planet();
	Planet(Transform transform);
	Planet(Transform transform, Mesh&& mesh);
	Planet(Transform transform, Mesh&& mesh, CircularStrategy strategy);
	~Planet() = default;

	void Draw(const Shaderprogram& shaderprogram) override;
	void Update(double time, Transform parent) override;
	void Place(Transform new_position) override;
	Transform GetTransform() override;

private:
	Mesh m_mesh;
	Transform m_transform;
	CircularStrategy m_strategy;
};