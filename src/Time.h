#pragma once
#include <cstdint>

using Time = float;
using NanoSeconds = uint64_t;

constexpr uint64_t g_second_ms = 1000;
constexpr uint64_t g_second_us = g_second_ms * 1000;
constexpr uint64_t g_second_ns = g_second_us * 1000;

uint64_t GetTimeNano();
uint64_t GetTimeMicro();

class Clock
{
private:
protected:

	uint64_t m_start_ns;
	uint64_t m_last_ns;
	uint64_t m_curr_ns;
	float m_delta;
	float m_ftime;

public:

	Clock();

	void Start();
	void Update();

	float Time() const
	{
		return m_ftime;
	}

	float DeltaTime() const
	{
		return m_delta;
	}
};

