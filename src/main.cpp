#include <iostream>
#include "Vector.h"
#include "Engine.h"

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
	// g_basic_shader = Shader::create("basic");
	LoadQuad();
}

void ReleaseResources()
{
	std::cout << "Releasing resources" << std::endl;
	// g_basic_shader.destroy();

	glDeleteVertexArrays(1, &g_quad_vao);
	glDeleteBuffers(1, &g_quad_vbo);
	glDeleteBuffers(1, &g_quad_ibo);
}

class TestApp : public Application
{
private:
public:

	TestApp() = default;

	void Init()
	{
	}

	void Update()
	{
	}

	void Destroy()
	{
	}
};

int main(int argc, char* argv[])
{
	Application* app = new TestApp();
	g_engine->Start(app);
	return 0;
}

