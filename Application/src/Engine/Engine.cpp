#include "Engine.h"
static auto SCR_WIDTH = 800;
static auto SCR_HEIGHT = 800;
static auto FRAMEBUFER_SIZE_CHANGED = false;

void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
	printf("\n");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	FRAMEBUFER_SIZE_CHANGED = true;
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

int Engine::GlSetup() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
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
#ifdef DEBUG
	// TODO: figure out why enabling these lines fixes the sun render
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(message_callback, 0);
	std::cout << "Enabled GL debug output" << std::endl;
#endif
	glfwSwapInterval(1);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return 0;
}

void Engine::AddEntity(std::unique_ptr<IBody> entity) {
	m_entities.push_back(std::move(entity));
}

void Engine::HandleInput(double mouse_diff_x, double mouse_diff_y, float delta_time)
{
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
	if(glfwGetKey(m_window, GLFW_KEY_I) == GLFW_PRESS)
	{
		m_entities[0]->Place(m_entities[0]->GetTransform().GetTranslation() + glm::vec3(1));
	}
	if(glfwGetKey(m_window, GLFW_KEY_K) == GLFW_PRESS)
	{
		m_entities[0]->Place(m_entities[0]->GetTransform().GetTranslation() + glm::vec3(-1));
	}
	if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_window, true);
	}
	m_camera.ProcessMouseMovement(mouse_diff_x, mouse_diff_y);
}

void Engine::Mainloop() {
	double mouse_x = 0, mouse_y = 0, old_mouse_x = 0, old_mouse_y = 0, mouse_diff_x = 0, mouse_diff_y = 0;
	float old_time = 0, delta_time = 0;
	auto projection = glm::perspective(glm::radians(90.f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 1000.f);
	auto view = glm::lookAt(glm::vec3(2, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	
	m_shaderprogramm.Bind();
	m_shaderprogramm.SetViewMatrix(view);
	m_shaderprogramm.SetProjectionMatrix(projection);
	m_shaderprogramm.SetLightColor(glm::vec3(1, 1, 1));
	m_shaderprogramm.SetLightPosition(glm::vec3(10, 10, 10));
	m_shaderprogramm.SetObjectColor(glm::vec3(1, 1, 1));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);


	while(!glfwWindowShouldClose(m_window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (FRAMEBUFER_SIZE_CHANGED)
		{
			projection = glm::perspective(glm::radians(90.f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 1000.f);
			m_shaderprogramm.Bind();
			m_shaderprogramm.SetProjectionMatrix(projection);
			FRAMEBUFER_SIZE_CHANGED = false;
		}
		glfwGetCursorPos(m_window, &mouse_x, &mouse_y);
		mouse_diff_x = mouse_x - old_mouse_x;
		mouse_diff_y = mouse_y - old_mouse_y;
		old_mouse_x = mouse_x;
		old_mouse_y = mouse_y;
		auto current_time = glfwGetTime();
		delta_time = current_time - old_time;
		old_time = current_time;
		HandleInput(mouse_diff_x, mouse_diff_y, delta_time);

		m_shaderprogramm.Bind();
		m_shaderprogramm.SetViewPosition(m_camera.Position);
		m_shaderprogramm.SetViewMatrix(m_camera.GetViewMatrix());
		for(auto& entity : m_entities) {
			entity->Update(current_time, Transform());
			entity->Draw(m_shaderprogramm);
		}

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glfwTerminate();
}
