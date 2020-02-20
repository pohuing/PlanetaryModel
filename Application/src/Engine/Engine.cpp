#include "Engine.h"
constexpr int SCR_WIDTH = 800;
constexpr int SCR_HEIGHT = 800;

void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
	printf("\n");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

std::string readFile(const char* const &path)
{
	std::ifstream ifs(path, std::ios::in | std::ios::ate | std::ios::binary);
	if(!ifs.is_open())
	{
		throw std::runtime_error("Could not open" + std::string(path));
	}
	std::string data(ifs.tellg(), 0);
	ifs.seekg(0);
	ifs.read(&data[0], data.size());
	return data;
}

Engine::Engine() : m_camera(glm::vec3(0, 0, 0)) {
	GlSetup();
	m_shaderprogramm = Shaderprogram(readFile("resources/BasicVertexShader.shader"), readFile("resources/BasicFragmentShader.shader"));
	m_shaderprogramm.Bind();
}

void Engine::AddEntity(std::unique_ptr<IBody> entity) {
	m_entities.push_back(std::move(entity));
}

int Engine::GlSetup() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Planetary Model", nullptr, nullptr);
	if(m_window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	GLenum err = glewInit();
	if(GLEW_OK != err) {
		std::cout << "Failed to initialize GLEW, ERROR: " << glewGetErrorString(err) << std::endl;
		return -1;
	}

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(message_callback, 0);
	glfwSwapInterval(1);
	
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return 0;
}

void Engine::Mainloop() {
	double mouse_x = 0, mouse_y = 0, old_mouse_x = 0, old_mouse_y = 0, mouse_diff_x = 0, mouse_diff_y = 0;
	float old_time = 0, delta_time = 0;
	m_shaderprogramm.SetViewMatrix(glm::lookAt(glm::vec3(2, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

	glm::mat4 projection = glm::perspective(glm::radians(90.f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.f);
	m_shaderprogramm.SetProjectionMatrix(projection);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	m_shaderprogramm.SetLightColor(glm::vec3(0, 1, 0));
	m_shaderprogramm.SetLightPosition(glm::vec3(10, 10, 10));
	m_shaderprogramm.SetObjectColor(glm::vec3(1, 1, 1));

	while(!glfwWindowShouldClose(m_window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetCursorPos(m_window, &mouse_x, &mouse_y);
		mouse_diff_x = mouse_x - old_mouse_x;
		mouse_diff_y = mouse_y - old_mouse_y;
		old_mouse_x = mouse_x;
		old_mouse_y = mouse_y;
		auto current_time = glfwGetTime();
		delta_time = current_time - old_time;
		old_time = current_time;

		m_entities[1]->Place(glm::vec3(sin(current_time) * 2, 0, 2));
		m_entities[0]->Place(glm::vec3(0, sin(current_time) * 2, 4));
		m_entities[5]->Place(glm::vec3(sin(current_time) * 3 + 10, 10, cos(current_time) * 3 + 10));


		if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
			m_camera.ProcessKeyboard(RIGHT, delta_time);
		}
		if(glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
			m_camera.ProcessKeyboard(LEFT, delta_time);
		}
		if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
			m_camera.ProcessKeyboard(FORWARD, delta_time);
		}
		if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
			m_camera.ProcessKeyboard(BACKWARD, delta_time);
		}
		if(glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			m_camera.ProcessKeyboard(UP, delta_time);
		}
		if(glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			m_camera.ProcessKeyboard(DOWN, delta_time);
		}
		if(glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS) {
			m_camera.ProcessMouseMovement(0, -0.1);
		}
		if(glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS) {
			m_camera.ProcessMouseMovement(0, 0.1);
		}
		m_camera.ProcessMouseMovement(mouse_diff_x, mouse_diff_y);
		m_shaderprogramm.SetViewPosition(m_camera.Position);
		m_shaderprogramm.SetViewMatrix(m_camera.GetViewMatrix());
		for(auto& entity : m_entities) {
			entity->Update();
			entity->Draw(m_shaderprogramm);
		}

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glfwTerminate();
}
