#pragma once
#include <vector>
#include <memory>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>

#include "../Entities/IBody.h"
#include "../Rendering/Shaderprogram.h"
#include "../Entities/Camera.h"

class Engine {
public:
	Engine();
	//~Engine();
	void AddEntity(std::unique_ptr<IBody> entity);
	void Mainloop();

private:
	int GlSetup();
	void HandleInput(double mouse_diff_x, double mouse_diff_y, float delta_time);
	std::vector<std::unique_ptr<IBody>> m_entities;
	Shaderprogram m_shaderprogramm;
	GLFWwindow* m_window = nullptr;
	Camera m_camera;
};
