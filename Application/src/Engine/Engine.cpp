#include "Engine.h"
#define SCR_WIDTH 1920
#define SCR_HEIGHT 1000

void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
	printf("\n");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

Engine::Engine()
{
	std::ifstream vstream("resources/BasicVertexShader.shader");
	std::stringstream vbuffer;
	vbuffer << vstream.rdbuf();

	std::ifstream fstream("resources/BasicFragmentShader.shader");
	std::stringstream fbuffer;
	fbuffer << fstream.rdbuf();

	Setup();
	m_entities = std::vector<std::unique_ptr<IBody>>();
	std::swap(m_shaderprogramm, Shaderprogramm(vbuffer.str(), fbuffer.str()));
	m_shaderprogramm.Bind();

}

void Engine::AddEntity(std::unique_ptr<IBody> entity)
{
	m_entities.push_back(std::move(entity));
}

int Engine::Setup()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Failed to initialize GLEW, ERROR: " << glewGetErrorString(err) << std::endl;
		return -1;
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(message_callback, 0);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return 0;
}

void Engine::Mainloop()
{
	double mouse_x = 0, mouse_y = 0, old_mouse_x = 0, old_mouse_y = 0, mouse_diff_x = 0, mouse_diff_y = 0;

	m_shaderprogramm.SetViewMatrix(glm::lookAt(glm::vec3(2, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

	glm::mat4 projection = glm::perspective(glm::radians(90.f), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.f);
	m_shaderprogramm.SetProjectionMatrix(projection);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(m_window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetCursorPos(m_window, &mouse_x, &mouse_y);
		mouse_diff_x = mouse_x - old_mouse_x;
		mouse_diff_y = mouse_y - old_mouse_y;
		old_mouse_x = mouse_x;
		old_mouse_y = mouse_y;

		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_camera.MoveRelative(glm::vec3(1, 0.f, 0.f));
		}
		if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_camera.MoveRelative(glm::vec3(-1, 0.f, 0.f));
			//x -= 0.1f;
		}
		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_camera.MoveRelative(glm::vec3(0.0f, 0.f, 1));
		}
		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_camera.MoveRelative(glm::vec3(0.f, 0.f, -1));
		}
		if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS) {
			m_camera.Turn(0,-0.1);
		}
		if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS) {
			m_camera.Turn(0,0.1);
		}
		m_camera.Turn(mouse_diff_y, mouse_diff_x);
		m_shaderprogramm.SetViewMatrix(m_camera.GetViewMatrix());
		for (auto& entity : m_entities)
		{
			entity.get()->Update();
			entity.get()->Draw(m_shaderprogramm);
		}

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glfwTerminate();
}
