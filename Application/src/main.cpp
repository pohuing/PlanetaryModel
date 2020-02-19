#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#include <utility>
#include "Entities/Planet.h"
#include "Engine/Engine.h"
#include "Entities/Mesh.h"
#include "Entities/Transform.h"
#include <memory>

int main() {
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
	engine.Mainloop();
}
