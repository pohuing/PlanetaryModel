#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#include <utility>
#include "Entities/Planet.h"
#include "Engine/Engine.h"


int main() {
	Engine engine;
	auto planet = std::make_unique<Planet>();
	engine.AddEntity(std::move(planet));
	engine.Mainloop();
}

