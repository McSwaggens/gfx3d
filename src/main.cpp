#include <iostream>
#include "Engine.h"
#include "Matrix.h"
#include "Quaternion.h"


const uint8_t g_indices[] =
{
	// Front Face //
	0, 3, 1,
	3, 2, 1,

	// Back Face //
	7, 4, 6,
	4, 5, 6,

	// Top Face //
	1, 2, 5,
	2, 6, 5,

	// Bottom Face //
	4, 7, 0,
	7, 3, 0,

	// Left Face //
	4, 0, 5,
	0, 1, 5,

	// Right Face //
	3, 7, 2,
	7, 6, 2,

};

const Vector g_cube_colors[] =
{
	Vector(0, 0, 1, 1),
	Vector(1, 0, 0, 1),
	Vector(1, 1, 0, 1),
	Vector(1, 0, 1, 1),
	Vector(0, 1, 0, 1),
	Vector(0, 1, 1, 1),
	Vector(0.5, 0.2, 0.7, 1),
	Vector(0.8, 0.2, 0.4, 1),
};

const Vector g_cube[] =
{
	// Front Face //
	Vector(-1, -1,  1,  1),   // 0: Front Bottom Left
	Vector(-1,  1,  1,  1),   // 1: Front Top Left
	Vector( 1,  1,  1,  1),   // 2: Front Top Right
	Vector( 1, -1,  1,  1),   // 3: Front Bottom Right

	// Back Face //
	Vector(-1, -1, -1,  1),   // 4: Back Bottom Right
	Vector(-1,  1, -1,  1),   // 5: Back Top Right
	Vector( 1,  1, -1,  1),   // 6: Back Top Left
	Vector( 1, -1, -1,  1),   // 7: Back Bottom Left
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
	uint32_t m_mvp_loc;
	Matrix<4, 4> m_mvp;
	Matrix<4, 4> m_proj_mat;
	Matrix<4, 4> m_model_mat;
	Matrix<4, 4> m_view_mat;
	Vector m_cam_pos;
	Quaternion m_cam_rot = { 0, 0, 1, 0 };

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
		m_mvp_loc = glGetUniformLocation(m_shader.GetProgramID(), "u_mvp");

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

	}

	void Update()
	{
		float speed = 10;
		if (IsKeyDown(Key::A))				m_cam_pos.x -= speed * g_engine->m_clock.DeltaTime();
		if (IsKeyDown(Key::D))				m_cam_pos.x += speed * g_engine->m_clock.DeltaTime();
		if (IsKeyDown(Key::W))				m_cam_pos.z -= speed * g_engine->m_clock.DeltaTime();
		if (IsKeyDown(Key::S))				m_cam_pos.z += speed * g_engine->m_clock.DeltaTime();
		if (IsKeyDown(Key::Space))			m_cam_pos.y += speed * g_engine->m_clock.DeltaTime();
		if (IsKeyDown(Key::F))				m_cam_pos.y -= speed * g_engine->m_clock.DeltaTime();

		Quaternion q = { 1, 0, 0, 0 };
		if (IsKeyDown(Key::E))				q = Quaternion::CreateRotation(M_PI * g_engine->m_clock.DeltaTime(), 0, 0, 1);
		if (IsKeyDown(Key::Q))				q = Quaternion::CreateRotation(-M_PI * g_engine->m_clock.DeltaTime(), 0, 0, 1);

		m_cam_rot = q * m_cam_rot * q.Conjugate();

		// std::cout << m_cam_pos << std::endl;

		float t = sinf(g_engine->m_clock.Time());
		float htw = g_engine->GetWindow()->HeightInWidth();

		m_proj_mat =
		{
		//  X    Y    Z    W
			htw, 0,   0,   0,  // X
			0,   1,   0,   0,  // Y
			0,   0,   1,   1, // Z
			0,   0,  -1,   0   // W
		};

		m_view_mat =
		{
		//  X    Y    Z    W
			1,   0,   0,   -m_cam_pos.x,  // X
			0,   1,   0,   -m_cam_pos.y,  // Y
			0,   0,   1,   -m_cam_pos.z,  // Z
			0,   0,   0,   1   // W
		};

		Vector pos = { 0, 0, 0, 0 };
		Vector scale = 1;
		m_model_mat =
		{
		//  X									Y						Z								W
			(float)m_cam_rot.j,					0,	 					-(float)m_cam_rot.i,			pos.x,	// X
			0,									scale.y,				0,								pos.y,	// Y
			(float)m_cam_rot.i,					0,						(float)m_cam_rot.j,				pos.z,	// Z
			0,									0,						0,								1		// W
		};

		m_mvp = m_proj_mat * m_view_mat * m_model_mat;
	}

	void Render()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
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
		glUniformMatrix4fv(m_mvp_loc, 1, GL_TRUE, m_mvp.a);
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

