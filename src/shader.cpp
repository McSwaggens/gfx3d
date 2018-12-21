#include "shader.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <fstream>
#include <iostream>

// TODO: Make loading a resource file easier
char* load_shader_file(const std::string& file_name)
{
	std::ifstream fs("../src/shaders/" + file_name, std::ios::binary);
	
	if (!fs.good() || fs.bad() || !fs.is_open())
	{
		std::cout << "Unable to open file " << file_name << std::endl;
		return nullptr;
	}

	// Go to the end of the file
	fs.seekg(0, std::ios::end);
	
	// Get the size of the file
	size_t file_size = fs.tellg();
	std::cout << file_name << " is " << file_size << " bytes long" << std::endl;

	char* buffer = new char[file_size + 1];
	fs.seekg(0, std::ios::beg);
	fs.read(buffer, file_size);
	buffer[file_size] = 0x0;

	// Cleanup
	fs.close();

	return buffer;
}

uint32_t compile_sub_shader(char* src, int type)
{
	uint32_t id = glCreateShader(type);
	std::cout << "New shader with id " << id << std::endl;
	// std::cout << "Source code: " << std::endl;
	// printf("%s\n", src);

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int compile_status; // TODO: Check this
	int log_length;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);

	if (log_length > 0)
	{
		char* log_str = new char[log_length + 1];
		glGetShaderInfoLog(id, log_length, nullptr, log_str);
		log_str[log_length] = 0x0;
		std::cout << "++++ Shader Compile Log ++++" << std::endl;
		printf("%s\n", log_str);
		std::cout << "---- Shader Compile Log ----" << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

void Shader::enable()
{
	glUseProgram(m_program_id);
}

// Is this really needed?
bool Shader::is_valid()
{
	return m_program_id;
}

void Shader::destroy()
{
	if (is_valid())
	{
		glDeleteProgram(m_program_id);
		m_program_id = 0;
	}
}

Shader Shader::create(const std::string& name)
{
	char* vert_src = load_shader_file(name + ".vert");
	char* frag_src = load_shader_file(name + ".frag");

	Shader shader;

	uint32_t vert_id = compile_sub_shader(vert_src, GL_VERTEX_SHADER);
	uint32_t frag_id = compile_sub_shader(frag_src, GL_FRAGMENT_SHADER);

	delete vert_src;
	delete frag_src;

	// FIXME: vert won't be destroyed if frag is invalid
	if (!vert_id)
	{
		std::cout << "Failed to compile vertex shader" << std::endl;
		return shader;
	}

	if (!frag_id)
	{
		std::cout << "Failed to compile fragment shader" << std::endl;
		return shader;
	}

	shader.m_program_id = glCreateProgram();
	glAttachShader(shader.m_program_id, vert_id);
	glAttachShader(shader.m_program_id, frag_id);
	glLinkProgram(shader.m_program_id);

	int link_status; // TODO: Check this
	int log_length;
	glGetProgramiv(shader.m_program_id, GL_LINK_STATUS, &link_status);
	glGetProgramiv(shader.m_program_id, GL_INFO_LOG_LENGTH, &log_length);

	if (log_length > 0)
	{
		char* log_str = new char[log_length + 1];
		glGetProgramInfoLog(shader.m_program_id, log_length, nullptr, log_str);
		log_str[log_length] = 0x0;
		std::cout << "++++ Program Link Log ++++" << std::endl;
		printf("%s\n", log_str);
		std::cout << "---- Program Link Log ----" << std::endl;

		glDeleteProgram(shader.m_program_id);
		shader.m_program_id = 0;
	}

	// FIXME: There is something wrong around here, I just can't see it yet...
	if (shader.is_valid())
	{
		glDetachShader(shader.m_program_id, vert_id);
		glDetachShader(shader.m_program_id, frag_id);
	}

	glDeleteShader(vert_id);
	glDeleteShader(frag_id);

	return shader;
}

