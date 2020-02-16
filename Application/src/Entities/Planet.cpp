#include "Planet.h"

//
//Planet::Planet()
//{
//	glm::vec3 frontNormal = glm::vec3(0.0f, 0.0f, 1.0f);
//	glm::vec3 backNormal = glm::vec3(0.0f, 0.0f, -1.0f);
//	glm::vec3 leftNormal = glm::vec3(-1.0f, 0.0f, 0.0f);
//	glm::vec3 rightNormal = glm::vec3(1.0f, 0.0f, 0.0f);
//	glm::vec3 topNormal = glm::vec3(0.0f, 1.0f, 0.0f);
//	glm::vec3 bottomNormal = glm::vec3(0.0f, -1.0f, 0.0f);
//
//	std::vector<Vertex> vertices
//	{
//		// front
//		Vertex(glm::vec3(-1.0, -1.0,  1.0), frontNormal),		// 0 links unten vorne
//		Vertex(glm::vec3(1.0, -1.0,  1.0),	frontNormal), 		// 1 rechts unten vorne
//		Vertex(glm::vec3(1.0,  1.0,  1.0),	frontNormal),		// 2 rechts oben vorne
//		Vertex(glm::vec3(-1.0,  1.0,  1.0), frontNormal),		// 3 links oben vorne
//		// back
//		Vertex(glm::vec3(-1.0, -1.0, -1.0),  backNormal),		// 4 links unten hinten
//		Vertex(glm::vec3(1.0, -1.0, -1.0),  backNormal),		// 5 rechts unten hinten
//		Vertex(glm::vec3(1.0,  1.0, -1.0),  backNormal),		// 6 rechts oben hinten
//		Vertex(glm::vec3(-1.0,  1.0, -1.0),  backNormal),		// 7 links oben hinten
//		// left
//		Vertex(glm::vec3(-1.0, -1.0, -1.0),  leftNormal),		// 8 links unten hinten
//		Vertex(glm::vec3(-1.0, -1.0, 1.0),	 leftNormal),		// 9 links unten vorne
//		Vertex(glm::vec3(-1.0,  1.0, 1.0),	 leftNormal),		// 10 links oben vorne
//		Vertex(glm::vec3(-1.0,  1.0, -1.0),  leftNormal),		// 11 links oben hinten
//		// right
//		Vertex(glm::vec3(1.0, -1.0, 1.0),	 rightNormal),		// 12 rechts unten vorne
//		Vertex(glm::vec3(1.0, -1.0, -1.0),	 rightNormal),		// 13 rechts unten hinten
//		Vertex(glm::vec3(1.0,  1.0, -1.0),	 rightNormal),		// 14 rechts oben hinten
//		Vertex(glm::vec3(1.0,  1.0, 1.0),	 rightNormal),		// 15 rechts oben vorne
//		// top
//		Vertex(glm::vec3(-1.0, 1.0, 1.0),	 topNormal),		// 16 links oben vorne
//		Vertex(glm::vec3(1.0, 1.0, 1.0),	 topNormal),		// 17 rechts oben vorne
//		Vertex(glm::vec3(1.0,  1.0, -1.0),	 topNormal),		// 18 rechts oben hinten
//		Vertex(glm::vec3(-1.0,  1.0, -1.0),  topNormal),		// 19 links oben hinten
//		// bottom
//		Vertex(glm::vec3(-1.0, -1.0, -1.0), bottomNormal),	// 20 links unten hinten
//		Vertex(glm::vec3(1.0, -1.0, -1.0),	bottomNormal),	// 21 rechts unten hinten
//		Vertex(glm::vec3(1.0,  -1.0, 1.0),	bottomNormal),	// 22 rechts unten vorne
//		Vertex(glm::vec3(-1.0,  -1.0, 1.0), bottomNormal)		// 23 links unten vorne
//	};
//	std::vector<GLuint> indices
//	{
//		// front
//		0, 1, 2,
//		2, 3, 0,
//
//		// back
//		4, 5, 6,
//		6, 7, 4,
//
//		// left
//		8, 9, 10,
//		10, 11, 8,
//
//		// right
//		12, 13, 14,
//		14, 15, 12,
//
//		// top
//		16, 17, 18,
//		18, 19, 16,
//
//		// bottom
//		20, 21, 22,
//		22, 23, 20
//
//	};
//
//	m_Transform = Transform();
//	m_mesh = Mesh(vertices, indices);
//}
//
//Planet::~Planet()
//{
//}
//
//void Planet::Draw(const Shaderprogramm& shaderprogramm) {
//	shaderprogramm.SetModelMatrix(m_Transform.GetModelMatrix());
//	m_mesh.Draw();
//}
//void Planet::Update() {
//
//}