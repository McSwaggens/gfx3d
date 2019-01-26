#pragma once
#include <cstdint>

enum BufferType
{
	Array,
	Index
};

class Buffer
{
private:
	uint32_t m_id = 0;
	const BufferType m_type;
public:
	Buffer(BufferType type = BufferType::Array);

	void Destroy();
	void Bind();
	void Unbind();
	bool IsValid();
};

