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
	STBImage sun_texture("resources/sun.jpg");
	Parser sun_mesh("resources/sun.obj");
	sun_mesh.ReadFile();
	
	STBImage earth_texture("resources/earth.jpg");
	Parser earth("resources/earth.obj");
	earth.ReadFile();

	STBImage mercury_texture("resources/mercury.jpg");
	Parser mercury("resources/mercury.obj");
	mercury.ReadFile();
	
	Engine engine;
	auto transform = Transform(glm::vec3(0), glm::vec3(1));
	auto sun = std::make_unique<Sun>(Mesh(sun_mesh.GetVertices(), sun_mesh.GetIndices(), std::move(sun_texture)), transform);


	auto strat = Strategy(5, M_PI/2);
	auto trans = Transform(glm::vec3(0), glm::vec3(0.3));
	sun->AddChild(
		std::make_unique<Planet>(trans, Mesh(earth.GetVertices(), earth.GetIndices(), std::move(earth_texture)), Strategy(5, M_PI / 2, 0.5))
	);

	strat = Strategy(3, M_PI);
	trans = Transform(glm::vec3(0), glm::vec3(0.1));
	sun->AddChild(
		std::make_unique<Planet>(trans, Mesh(mercury.GetVertices(), mercury.GetIndices(), std::move(mercury_texture)), Strategy(3, M_PI, 365/88 * 0.5))
	);

	
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
