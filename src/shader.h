#pragma once
#include <stdint.h>
#include <string>

class Shader final
{
	uint32_t m_program_id = 0;
public:
	static Shader create(const std::string& name);
	void enable();
	void destroy();
	bool is_valid();
};
