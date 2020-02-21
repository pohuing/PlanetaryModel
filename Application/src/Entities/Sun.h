#pragma once
#include <vector>
#include <GLEW/glew.h>
#include "Planet.h"
#include "Transform.h"
#include "Mesh.h"

class Sun : public IBody
{
public:
	Sun(Mesh mesh);
	Sun(Mesh mesh, Transform transform);
	~Sun() = default;
	void AddChild(std::unique_ptr<Planet> child);

	void Update(double Time) override;
	void Draw(const Shaderprogram& shaderprogram) override;
	void Place(Transform new_transform) override;
	Transform GetTransform() override;
	
private:
	std::vector<std::unique_ptr<Planet>> m_children;
	Transform m_transform;
	Mesh m_mesh;
};
