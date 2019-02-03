#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "Vector.h"
#include "Keyboard.h"
#include "Time.h"
#include "Window.h"
#include "Buffer.h"
#include "Actor.h"
#include "Application.h"

class Engine final
{
private:

	bool m_running = false;
	Window* m_window = nullptr;
	Application* m_app = nullptr;

	bool InitWindow();
	bool InitOGL();
	bool LoadResources();
	void GameLoop();
	void CheckEvents();
	void LogicUpdate();
	void Render();
	void DestroyResources();

public:

	Clock m_clock;

	const Window* GetWindow() const
	{
		return m_window;
	}

	bool IsRunning() const
	{
		return m_running;
	}

	void Start(Application* app);
};

extern Engine* const g_engine;

