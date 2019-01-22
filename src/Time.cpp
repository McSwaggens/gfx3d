#include "Time.h"
#include <ctime>
#include <iostream>

uint64_t GetTimeNano()
{
	timespec ts;
	clock_gettime(CLOCK_BOOTTIME, &ts);
	uint64_t ns = ts.tv_sec * g_second_ns + ts.tv_nsec;
	return ns;
}

uint64_t GetTimeMicro()
{
	return GetTimeNano() * 1000;
}

Clock::Clock()
{
}

void Clock::Start()
{
	m_start_ns = GetTimeNano();
}

void Clock::Update()
{
	if (!m_start_ns)
	{
		Start();
		return;
	}

	m_last_ns = m_curr_ns;
	m_curr_ns = GetTimeNano() - m_start_ns;

	uint64_t delta_ns = m_curr_ns - m_last_ns;

	// FIXME: Converting uint64_t to long double incorrectly
	long double delta_hr = (long double)delta_ns / (long double)g_second_ns;
	long double ftime_hr = (long double)m_curr_ns / (long double)g_second_ns;

	m_delta = (float)(double)delta_hr;
	m_ftime = (float)(double)ftime_hr;
}

