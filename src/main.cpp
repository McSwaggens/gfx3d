#include <iostream>
#include "Engine.h"

const Vector g_cube[] =
{
	// Front Face //
	Vector(-1, -1, 1, 1) * 0.5,  // 0: Front Bottom Left
	Vector(-1, 1, 1, 1) * 0.5,   // 1: Front Top Left
	Vector(1, 1, 1, 1) * 0.5,    // 2: Front Top Right
	Vector(1, -1, 1, 1) * 0.5,   // 3: Front Bottom Right

	// Back Face //
	Vector(-1, -1, -1, 1) * 0.5, // 4: Back Bottom Right
	Vector(-1, 1, -1, 1) * 0.5,  // 5: Back Top Right
	Vector(1, 1, -1, 1) * 0.5,   // 6: Back Top Left
	Vector(1, -1, -1, 1) * 0.5,  // 7: Back Bottom Left
};

const uint8_t g_indices[] =
{
	// Front Face //
	0, 1, 3,
	1, 2, 3,

	// Back Face //
	7, 6, 4,
	6, 5, 4,

	// Top Face //
	1, 5, 2,
	5, 6, 2,

	// Bottom Face //
	5, 0, 7,
	0, 3, 7,

	// Left Face //
	4, 5, 0,
	5, 1, 0,

	// Right Face //
	3, 2, 7,
	2, 6, 7,

};

class TestApp : public Application
{
private:
public:

	Buffer m_buffer;
	Buffer m_index_buffer;
	uint32_t m_vao;
	Shader m_shader;

	TestApp() = default;

	void Init()
	{
		m_buffer = Buffer::Create(BufferType::Array);
		m_buffer.Bind();
		glEnableVertexAttribArray(0);
		glBufferData(
				GL_ARRAY_BUFFER,
				sizeof(g_cube),
				&g_cube,
				GL_STATIC_DRAW);

		m_index_buffer = Buffer::Create(BufferType::Index);
		m_index_buffer.Bind();
		glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				sizeof(g_indices),
				&g_indices,
				GL_STATIC_DRAW);

		m_shader = Shader::create("basic");

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
	}

	void Update()
	{
	}

	void Render()
	{
		glEnable(GL_DEPTH_TEST);

		m_buffer.Bind();
		m_shader.enable();
		glVertexAttribPointer(
				0,
				4,
				GL_FLOAT,
				GL_FALSE,
				0,
				nullptr);
		glEnableVertexAttribArray(0);
		m_index_buffer.Bind();
		glDrawElements(
				GL_TRIANGLES,
				sizeof(g_indices),
				GL_UNSIGNED_BYTE,
				nullptr);
	}

	void Destroy()
	{
		m_buffer.Destroy();
		m_shader.destroy();
	}
};

int main(int argc, char* argv[])
{
	Application* app = new TestApp();
	g_engine->Start(app);
	return 0;
}

