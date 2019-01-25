#include "Engine.h"

Engine* const g_engine = new Engine();

void Engine::Start()
{
	if (m_running)
	{
		std::cout << "An attempt was made to initialize the engine again" << std::endl;
		return;
	}
	m_running = true;

	std::cout << "Initializing Engine..." << std::endl;

	m_clock.Start();
	InitWindow();
	InitOGL();
	SetupKeyboard(m_window);
	LoadResources();
	GameLoop();
	DestroyResources();
}

void Framebuffer_SizeChanged_Callback(GLFWwindow* g_window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool Engine::InitWindow()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "glfwInit failed." << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(1920, 1080, "gfx3d", NULL, NULL);

	if (!m_window)
	{
		std::cout << "Failed to create window" << std::endl;
		return false;
	}

	glfwSetFramebufferSizeCallback(m_window, Framebuffer_SizeChanged_Callback);

	std::cout << "Window created" << std::endl;
	return true;
}

bool Engine::InitOGL()
{
	// Set the OpenGL context
	glfwMakeContextCurrent(m_window);

	// Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "glewInit failed." << std::endl;
		return false;
	}

	std::cout << "OpenGL fully initialized" << std::endl;
	return true;
}

bool Engine::LoadResources()
{
	std::cout << "Loading resources" << std::endl;
	return true;
}

void Engine::DestroyResources()
{
	std::cout << "Destroying resources" << std::endl;

	// GLFW stuff needs to go last
	// Destroy the window
	glfwDestroyWindow(m_window);
	m_window = nullptr;

	// Terminate GLFW
	glfwTerminate();
}

void Engine::CheckEvents()
{
	SwapKeyboardStates();
	glfwPollEvents();

	if (glfwWindowShouldClose(m_window))
	{
		m_running = false;
	}
}

void Engine::LogicUpdate()
{
	if (IsKeyReleased(GLFW_KEY_ESCAPE))
	{
		m_running = false;
	}
}

void Engine::GameLoop()
{
	while (m_running)
	{
		m_clock.Update();
		CheckEvents();
		LogicUpdate();
		Render();
	}
}

void Engine::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glBindVertexArray(g_quad_vao);
	// g_basic_shader.enable();
	// glDrawElements(GL_TRIANGLES, sizeof(g_quad_indices) / sizeof(uint8_t), GL_UNSIGNED_BYTE, nullptr);
	// glBindVertexArray(0);

	glfwSwapBuffers(m_window);
}

