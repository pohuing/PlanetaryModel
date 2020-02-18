#pragma once
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "../Entities/IBody.h"
#include "../Rendering/ShaderProgramm.h"
#include "../Entities/Camera.h"
#include "../Entities/Transform.h"

class Engine
{
public:
	Engine();
	//~Engine();
	void AddEntity(std::unique_ptr<IBody> entity);
	int Setup();
	void Mainloop();


private:
	std::vector<std::unique_ptr<IBody>> m_entities;
	Shaderprogramm m_shaderprogramm;
	GLFWwindow* m_window;
	Camera m_camera;
};

