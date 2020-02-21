#include <GLM/glm.hpp>
#include <memory>
#include <utility>
#define _USE_MATH_DEFINES
#include <math.h>


#include "Entities/Planet.h"
#include "Engine/Engine.h"
#include "Entities/Transform.h"
#include "Entities/Mesh.h"
#include "Engine/ObjParser.h"
#include "Entities/Strategy.h"
#include "Entities/Sun.h"

int main() {
	Parser a("resources/sphere.obj");
	a.ReadFile();
		
	Engine engine;
	auto transform = Transform(glm::vec3(0), glm::vec3(1));
	auto sun = std::make_unique<Sun>(Mesh(a.GetVertices(), a.GetIndices()), transform);

	for(auto i = 1; i < 5; i++)
	{
		auto strat = Strategy(5, i*M_PI/2);
		auto trans = Transform(glm::vec3(0), glm::vec3(0.3));
		sun->AddChild(
			std::make_unique<Planet>(trans, Mesh(a.GetVertices(), a.GetIndices()), strat)
		);
	}
	
	engine.AddEntity(std::move(sun));
	engine.Mainloop();
}
