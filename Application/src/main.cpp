#include <GLM/glm.hpp>
#include <memory>
#include <utility>

#include "Entities/Planet.h"
#include "Engine/Engine.h"
#include "Entities/Transform.h"
#include "Entities/Mesh.h"
#include "Engine/ObjParser.h"

int main() {
	Parser a("resources/cube.obj");
	a.ReadFile();
	
	Transform transforms[] = {
		{glm::vec3(2,0,0)},
		{glm::vec3(5,0,0)},
		{glm::vec3(10,10,10), glm::vec3(0.1)},
		{glm::vec3(0,5,0)},
	};

	Engine engine;
	auto planet = std::make_unique<Planet>();
	engine.AddEntity(std::move(planet));
	for(auto& tf : transforms) {
		planet = std::make_unique<Planet>(tf);
		engine.AddEntity(std::move(planet));
	}
	auto sphere_mesh = Mesh(a.GetVertices(), a.GetIndices());
	auto sphere = std::make_unique<Planet>(Transform(glm::vec3(-5, -5, -5)), std::move(sphere_mesh));
	engine.AddEntity(std::move(sphere));
	engine.Mainloop();
}
