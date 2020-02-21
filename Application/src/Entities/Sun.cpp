#include "Sun.h"

Sun::Sun(Mesh mesh)
	:m_transform(glm::vec3(0,0,10)), m_children(), m_mesh(std::move(mesh)){}

Sun::Sun(Mesh mesh, Transform transform)
	:m_transform(transform), m_mesh(std::move(mesh)), m_children(){}

void Sun::AddChild(std::unique_ptr<Planet> child)
{
	m_children.push_back(std::move(child));
}

void Sun::Draw(const Shaderprogram& shaderprogramm)
{
	shaderprogramm.SetModelMatrix(m_transform.GetModelMatrix());
	m_mesh.Draw();
	shaderprogramm.Bind();
	shaderprogramm.SetLightPosition(m_transform.GetTranslation());
	shaderprogramm.SetLightColor(glm::vec3(1, 1, 1));
	for (auto& child : m_children)
	{
		child->Draw(shaderprogramm);
	}
}

void Sun::Update(double time)
{
	for (auto& child:m_children)
	{
		child->Update(time, m_transform);
	}
	m_mesh.Draw();
}

void Sun::Place(Transform newPosition)
{
	m_transform = newPosition;
}

Transform Sun::GetTransform()
{
	return m_transform;
}
