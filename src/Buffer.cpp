#include "Buffer.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>

Buffer Buffer::Create(BufferType type)
{
	Buffer buffer;
	buffer.m_type = type;

	glGenBuffers(1, &buffer.m_id);
	
	if (!buffer.IsValid())
	{
		std::cerr << "[ERROR] glGenBuffers returned 0" << std::endl;
	}

	std::cout << "Created Buffer " << buffer.m_id << "." << std::endl;

	return buffer;
}

void Buffer::Destroy()
{
	if (!IsValid())
	{
		std::cerr << "[ERROR] trying to destroy invalid buffer" << std::endl;
	}
	else
	{
		glDeleteBuffers(1, &m_id);
		std::cout << "Buffer " << m_id << " destroyed." << std::endl;
		m_id = 0;
	}
}

uint32_t ConvertBufferType(BufferType type)
{
	switch (type)
	{
		case BufferType::Array: return GL_ARRAY_BUFFER;
		case BufferType::Index: return GL_ELEMENT_ARRAY_BUFFER;
	}

	std::cerr << "Invalid BufferType" << std::endl;
	exit(EXIT_FAILURE);
}

void Buffer::Bind()
{
	if (!IsValid())
	{
		std::cerr << "[ERROR] Trying to bind invalid buffer" << std::endl;
	}
	else
	{
		glBindBuffer(ConvertBufferType(m_type), m_id);
	}
}

void Buffer::Unbind()
{
	glBindBuffer(ConvertBufferType(m_type), 0);
}

bool Buffer::IsValid()
{
	return m_id != 0;
}

