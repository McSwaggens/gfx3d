#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <ratio>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "vector.h"
#include "Keyboard.h"
#include "Time.h"

GLFWwindow* window = nullptr;
Shader basic_shader;
bool running = false;

Clock g_clock;

const long double g_golden_ratio = (1.0 + sqrt(5.0)) / 2.0;

void framebuffer_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool init_window()
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1920, 1080, "gfx3d", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
		return false;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	std::cout << "Window created" << std::endl;
	return true;
}

bool init_opengl()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "glfwInit failed." << std::endl;
		return false;
	}

	// Create a window
	if (!init_window())
	{
		return false;
	}

	// Set the OpenGL context
	glfwMakeContextCurrent(window);

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

void kill_window()
{
	if (window)
	{
		glfwDestroyWindow(window);
		window = nullptr;
	}
}

void shutdown_opengl()
{
	std::cout << "Shutting down OpenGL" << std::endl;

	// Safely kill the window
	kill_window();

	// Terminate GLFW
	glfwTerminate();
}

static_assert(sizeof(GLuint) == sizeof(uint32_t), "GLuint != uint32_t");


uint32_t quad_vao;

uint32_t quad_vbo;
Vector quad_vertices[] =
{
	Vector(-1.0f, -1.0f),
	Vector(-1.0f,  1.0f),
	Vector( 1.0f,  1.0f),
	Vector( 1.0f, -1.0f)
};

uint32_t quad_ibo;
uint8_t quad_indices[] =
{
	0, 1, 2, 2, 3, 0
};

void load_quad()
{
	// Generate buffer objects
	glGenBuffers(1, &quad_vbo);
	glGenBuffers(1, &quad_ibo);


	// Fill vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), &quad_vertices, GL_STATIC_DRAW);

	// Fill index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_indices), &quad_indices, GL_STATIC_DRAW);

	// Generate VAO
	glGenVertexArrays(1, &quad_vao);
	glBindVertexArray(quad_vao);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ibo);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


void load_resources()
{
	std::cout << "Loading resources" << std::endl;
	basic_shader = Shader::create("basic");
	load_quad();
}

void release_resources()
{
	std::cout << "Releasing resources" << std::endl;
	basic_shader.destroy();

	glDeleteVertexArrays(1, &quad_vao);
	glDeleteBuffers(1, &quad_vbo);
	glDeleteBuffers(1, &quad_ibo);
}

void check_events()
{
	swap_kbstates();
	glfwPollEvents();

	if (glfwWindowShouldClose(window))
	{
		running = false;
	}
}

void logic()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		running = false;
	}
}

void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(quad_vao);
	basic_shader.enable();
	glDrawElements(GL_TRIANGLES, sizeof(quad_indices) / sizeof(uint8_t), GL_UNSIGNED_BYTE, nullptr);
	glBindVertexArray(0);

	glfwSwapBuffers(window);
}

void main_loop()
{
	running = true;
	while (running)
	{
		g_clock.Update();
		std::cout << "g_clock.Time() = " << g_clock.Time() << std::endl << "g_clock.DeltaTime() = " << g_clock.DeltaTime() << std::endl;
		check_events();
		logic();
		render();
	}
}

int main(int argc, char* argv[])
{
	g_clock.Start();
	if (init_opengl())
	{
		std::cout << std::fixed;
		std::cout.precision(17);
		SetupKeyboard(window);
		load_resources();
		main_loop();
		release_resources();
		shutdown_opengl();
	}

	return 0;
}
