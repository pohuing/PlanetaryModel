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
	std::vector<std::string> planet_names;
	planet_names.emplace_back("mercury");
	planet_names.emplace_back("venus");
	planet_names.emplace_back("earth");
	planet_names.emplace_back("mars");
	planet_names.emplace_back("jupiter");
	planet_names.emplace_back("saturn");
	planet_names.emplace_back("uranus");
	planet_names.emplace_back("neptune");
	
	STBImage sun_texture("resources/sun.jpg");
	Parser sun_mesh("resources/sun.obj");
	sun_mesh.ReadFile();
	
	Engine engine;
	auto transform = Transform(glm::vec3(0), glm::vec3(1));
	auto sun = std::make_unique<Sun>(Mesh(sun_mesh.GetVertices(), sun_mesh.GetIndices(), std::move(sun_texture)), transform);

	for (auto i = 0; i < planet_names.size(); i++)
	{
		auto name = planet_names[i];
		Parser planet("resources/" + name + ".obj");
		planet.ReadFile();
		STBImage texture("resources/" + name + ".jpg");
		sun->AddChild(
			std::make_unique<Planet>(
				Transform(glm::vec3(0)),
				Mesh(planet.GetVertices(), planet.GetIndices(), std::move(texture)),
				Strategy(3 + i + 1, M_PI / 2 * i, 0.01)
				));
	}

	engine.AddEntity(std::move(sun));

	//Parser cube("resources/cubey.obj");
	//cube.ReadFile();
	//STBImage cubey_texture("resources/cubey.jpg");
	//engine.AddEntity(std::move(std::make_unique<Planet>(
	//	Transform({ 5, 5, 5 }),
	//	Mesh(cube.GetVertices(), cube.GetIndices(), std::move(cubey_texture))
	//	)));


	//engine.AddEntity(std::move(std::make_unique<Planet>(
	//	Transform({ -5, 5, 5 }),
	//	Mesh(earth.GetVertices(), earth.GetIndices(), std::move(earth_texture))
	//	)));
	engine.Mainloop();
}
