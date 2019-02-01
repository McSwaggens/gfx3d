#include <iostream>
#include "Engine.h"

const Vector g_triangle[] =
{
	Vector(-1, -1, 0, 1),
	Vector(0, 1, 0, 1),
	Vector(1, -1, 0, 1),
};

class TestApp : public Application
{
private:
public:

	Buffer m_buffer;
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
				sizeof(g_triangle),
				&g_triangle,
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
		glDrawArrays(
				GL_TRIANGLES,
				0,
				3);
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

