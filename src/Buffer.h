#pragma once
#include <cstdint>

enum BufferType
{
	Array,
	Index
};

struct Buffer
{
	uint32_t m_id = 0;
	BufferType m_type = BufferType::Array;

	Buffer() = default;
	Buffer(uint32_t id, BufferType type = BufferType::Array)
		: m_id(id), m_type(type) { }

	static Buffer Create(BufferType type = BufferType::Array);

	void Destroy();
	void Bind();
	void Unbind();
	bool IsValid();
};

