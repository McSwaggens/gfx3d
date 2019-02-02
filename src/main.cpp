#include <iostream>
#include "Engine.h"
#include "Matrix.h"

const Vector g_cube[] =
{
	// Front Face //
	Vector(-1, -1,  0,  0) * 0.25 + Vector(0.5, 0.5, -0.25, 1),   // 0: Front Bottom Left
	Vector(-1,  1,  0,  0) * 0.25 + Vector(0.5, 0.5, -0.25, 1),   // 1: Front Top Left
	Vector( 1,  1,  0,  0) * 0.25 + Vector(0.5, 0.5, -0.25, 1),   // 2: Front Top Right
	Vector( 1, -1,  0,  0) * 0.25 + Vector(0.5, 0.5, -0.25, 1),   // 3: Front Bottom Right

	// Back Face //
	Vector(-1, -1, 0,  0) * 0.25 + Vector(0.5, 0.5, -0.5, 1),   // 4: Back Bottom Right
	Vector(-1,  1, 0,  0) * 0.25 + Vector(0.5, 0.5, -0.5, 1),   // 5: Back Top Right
	Vector( 1,  1, 0,  0) * 0.25 + Vector(0.5, 0.5, -0.5, 1),   // 6: Back Top Left
	Vector( 1, -1, 0,  0) * 0.25 + Vector(0.5, 0.5, -0.5, 1),   // 7: Back Bottom Left
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
	4, 0, 7,
	0, 3, 7,

	// Left Face //
	4, 5, 0,
	5, 1, 0,

	// Right Face //
	3, 2, 7,
	2, 6, 7,

};

const Vector g_cube_colors[] =
{
	Vector(0, 0, 1, 1),

	Vector(1, 0, 0, 1),

	Vector(1, 1, 0, 1),

	Vector(1, 0, 1, 1),

	Vector(0, 1, 0, 1),

	Vector(0, 1, 1, 1),
};

const Matrix<4, 4> g_proj_mat =
{
//  X    Y    Z    W
	1,   0,   0,   0,  // X
	0,   1,   0,   0,  // Y
	0,   0,  -1,   0,  // Z
	0,   0,  -1,   1   // W
};

class TestApp : public Application
{
private:
public:

	Buffer m_buffer;
	Buffer m_index_buffer;
	Buffer m_color_buffer;
	uint32_t m_vao;
	Shader m_shader;
	uint32_t m_proj_loc;

	TestApp() = default;

	void Init()
	{
		m_buffer = Buffer::Create(BufferType::Array);
		m_buffer.Bind();
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

		m_color_buffer = Buffer::Create(BufferType::Array);
		m_color_buffer.Bind();
		glBufferData(
				GL_ARRAY_BUFFER,
				sizeof(g_cube_colors),
				&g_cube_colors,
				GL_STATIC_DRAW);

		m_shader = Shader::create("basic");
		m_shader.enable();
		m_proj_loc = glGetUniformLocation(m_shader.GetProgramID(), "u_proj");

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

	}

	void Update()
	{
	}

	void Render()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_BUFFER_BIT);
		// glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);

		m_shader.enable();

		m_buffer.Bind();
		glVertexAttribPointer(
				0,
				4,
				GL_FLOAT,
				GL_FALSE,
				0,
				nullptr);
		glEnableVertexAttribArray(0);

		m_color_buffer.Bind();
		glVertexAttribPointer(
				1,
				4,
				GL_FLOAT,
				GL_FALSE,
				0,
				nullptr);
		glEnableVertexAttribArray(1);

		m_index_buffer.Bind();
		glUniformMatrix4fv(m_proj_loc, 1, GL_TRUE, g_proj_mat.a);
		glDrawElements(
				GL_TRIANGLES,
				sizeof(g_indices),
				GL_UNSIGNED_BYTE,
				nullptr);
	}

	void Destroy()
	{
		m_color_buffer.Destroy();
		m_index_buffer.Destroy();
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

