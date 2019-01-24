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

GLFWwindow* g_window = nullptr;
Clock g_clock;
Shader g_basic_shader;
bool g_running = false;

void Framebuffer_SizeChanged_Callback(GLFWwindow* g_window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool InitWindow()
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	g_window = glfwCreateWindow(1920, 1080, "gfx3d", NULL, NULL);

	if (!g_window)
	{
		std::cout << "Failed to create g_window" << std::endl;
		return false;
	}

	glfwSetFramebufferSizeCallback(g_window, Framebuffer_SizeChanged_Callback);

	std::cout << "g_window created" << std::endl;
	return true;
}

bool InitOGL()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "glfwInit failed." << std::endl;
		return false;
	}

	// Create a g_window
	if (!InitWindow())
	{
		return false;
	}

	// Set the OpenGL context
	glfwMakeContextCurrent(g_window);

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

void KillWindow()
{
	if (g_window)
	{
		glfwDestroyWindow(g_window);
		g_window = nullptr;
	}
}

void ShutdownOGL()
{
	std::cout << "Shutting down OpenGL" << std::endl;

	// Safely kill the g_window
	KillWindow();

	// Terminate GLFW
	glfwTerminate();
}

uint32_t g_quad_vao;
uint32_t g_quad_vbo;
Vector g_quad_vertices[] =
{
	Vector(-1.0f, -1.0f),
	Vector(-1.0f,  1.0f),
	Vector( 1.0f,  1.0f),
	Vector( 1.0f, -1.0f)
};

uint32_t g_quad_ibo;
uint8_t g_quad_indices[] =
{
	0, 1, 2, 2, 3, 0
};

void LoadQuad()
{
	// Generate buffer objects
	glGenBuffers(1, &g_quad_vbo);
	glGenBuffers(1, &g_quad_ibo);


	// Fill vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, g_quad_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertices), &g_quad_vertices, GL_STATIC_DRAW);

	// Fill index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_quad_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_quad_indices), &g_quad_indices, GL_STATIC_DRAW);

	// Generate VAO
	glGenVertexArrays(1, &g_quad_vao);
	glBindVertexArray(g_quad_vao);
	glBindBuffer(GL_ARRAY_BUFFER, g_quad_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_quad_ibo);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


void LoadResources()
{
	std::cout << "Loading resources" << std::endl;
	g_basic_shader = Shader::create("basic");
	LoadQuad();
}

void ReleaseResources()
{
	std::cout << "Releasing resources" << std::endl;
	g_basic_shader.destroy();

	glDeleteVertexArrays(1, &g_quad_vao);
	glDeleteBuffers(1, &g_quad_vbo);
	glDeleteBuffers(1, &g_quad_ibo);
}

void CheckEvents()
{
	SwapKeyboardStates();
	glfwPollEvents();

	if (glfwWindowShouldClose(g_window))
	{
		g_running = false;
	}
}

void Logic()
{
	if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		g_running = false;
	}
}

void Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(g_quad_vao);
	g_basic_shader.enable();
	glDrawElements(GL_TRIANGLES, sizeof(g_quad_indices) / sizeof(uint8_t), GL_UNSIGNED_BYTE, nullptr);
	glBindVertexArray(0);

	glfwSwapBuffers(g_window);
}

void MainLoop()
{
	g_running = true;
	while (g_running)
	{
		g_clock.Update();
		CheckEvents();
		Logic();
		Render();
	}
}

int main(int argc, char* argv[])
{
	g_clock.Start();
	if (InitOGL())
	{
		std::cout << std::fixed;
		std::cout.precision(17);
		SetupKeyboard(g_window);
		LoadResources();
		MainLoop();
		ReleaseResources();
		ShutdownOGL();
	}

	return 0;
}
