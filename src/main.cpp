#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "vector.h"

GLFWwindow* window = nullptr;
Shader basic_shader;
bool running = false;

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

uint32_t circle_vao;
uint32_t circle_vbo;
// (center vertex) + (vert per quadrant) * (quadrants in a circle) + (reset)
const uint32_t circle_vertex_count = 1 + 5 * 4 + 1;
Vector circle_vertices[circle_vertex_count];

void load_circle()
{
	circle_vertices[0] = Vector(0.0f);

	for (int i = 0; i < circle_vertex_count - 1; i++)
	{
		float theta = ((float)i / ((float)circle_vertex_count - 2)) * (2 * M_PI);
		circle_vertices[i + 1] = Vector(cos(theta), sin(theta));
	}

	glGenBuffers(1, &circle_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle_vertices), &circle_vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &circle_vao);
	glBindVertexArray(circle_vao);
	glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
}

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ibo);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void load_resources()
{
	std::cout << "Loading resources" << std::endl;
	basic_shader = Shader::create("basic");

	load_circle();


}

void release_resources()
{
	std::cout << "Releasing resources" << std::endl;
	basic_shader.destroy();

	glDeleteVertexArrays(1, &quad_vao);
	glDeleteBuffers(1, &quad_vbo);
	glDeleteBuffers(1, &quad_ibo);

	glDeleteVertexArrays(1, &circle_vao);
	glDeleteBuffers(1, &circle_vbo);

}

void check_events()
{
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

	// Draw quad
	glBindVertexArray(circle_vao);
	basic_shader.enable();
	glDrawArrays(GL_TRIANGLE_FAN, 0, circle_vertex_count);
	glBindVertexArray(0);

	glfwSwapBuffers(window);
}

void main_loop()
{
	running = true;
	while (running)
	{
		check_events();
		logic();
		render();
	}
}

int main(int argc, char* argv[])
{
	if (init_opengl())
	{
		load_resources();
		main_loop();
		release_resources();
		shutdown_opengl();
	}

	return 0;
}

