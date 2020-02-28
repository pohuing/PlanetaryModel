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
#include "Entities/CircularStrategy.h"
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
	
	Parser sun_mesh("resources/sun.obj");
	
	Engine engine;
	auto transform = Transform(glm::vec3(0), glm::vec3(1));
	auto sun = std::make_unique<Sun>(sun_mesh.GenerateMeshWithTexture(STBImage()), transform);

	for (auto i = 0; i < planet_names.size(); i++)
	{
		auto name = planet_names[i];
		Parser planet("resources/" + name + ".obj");
		STBImage texture("resources/" + name + ".jpg");
		sun->AddChild(
			std::make_unique<Planet>(
				Transform(glm::vec3(0)),
				planet.GenerateMeshWithTexture(std::move(texture)),
				CircularStrategy(3 + i*2 + 1, M_PI / 2 * i, (planet_names.size() - i + 1)/2)
				));
	}

	engine.AddEntity(std::move(sun));
	engine.Mainloop();
}
