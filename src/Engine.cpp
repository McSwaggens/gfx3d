#include "Engine.h"

Engine* const g_engine = new Engine();

void Engine::Start(Application* app)
{
	if (!app)
	{
		std::cerr << "No app given to engine initializer" << std::endl;
		return;
	}
	m_app = app;

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
	SetupKeyboard(m_window->GetGLFWWindow());
	LoadResources();
	GameLoop();
	DestroyResources();
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

	m_window = new Window("Game Window", 1920, 1080);

	if (!m_window->GetGLFWWindow()) // FIXME
	{
		std::cout << "Failed to create window" << std::endl;
		return false;
	}


	std::cout << "Window created" << std::endl;
	return true;
}

bool Engine::InitOGL()
{
	// Set the OpenGL context
	m_window->BindContext();

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
	m_app->Init();
	return true;
}

void Engine::DestroyResources()
{
	std::cout << "Destroying resources" << std::endl;

	if (m_app)
	{
		m_app->Destroy();
		free(m_app);
	}

	// GLFW stuff needs to go last
	// Destroy the window
	delete m_window;

	// Terminate GLFW
	glfwTerminate();
}

void Engine::CheckEvents()
{
	SwapKeyboardStates();
	glfwPollEvents();

	if (glfwWindowShouldClose(m_window->GetGLFWWindow()))
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

	m_app->Update();
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

	m_window->SwapBuffers();
}

