#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "vector.h"
#include "Keyboard.h"
#include "Time.h"
#include "Window.h"
#include "Buffer.h"

class Engine final
{
private:

	bool m_running = false;
	Clock m_clock;
	Window* m_window = nullptr;
	Buffer* m_buffer = nullptr;

	bool InitWindow();
	bool InitOGL();
	bool LoadResources();
	void GameLoop();
	void CheckEvents();
	void LogicUpdate();
	void Render();
	void DestroyResources();

public:
	void Start();
};

extern Engine* const g_engine;

