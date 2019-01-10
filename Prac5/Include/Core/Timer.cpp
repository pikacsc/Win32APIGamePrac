#include "Timer.h"

DEFINITION_SINGLE(Timer)


Timer::Timer()
	:m_fTimeScale(1.f)
{
}

Timer::~Timer()
{
}

bool Timer::Init()
{
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTime);

	m_fDeltaTime = 0.f;
	m_fFPS = 0.f;
	m_fFPSTime = 0.f;
	m_iFrameMax = 60;
	m_iFrame = 0;

	return true;
}

void Timer::Update()
{
	LARGE_INTEGER tTime;
	QueryPerformanceCounter(&tTime);
	m_fDeltaTime = (tTime.QuadPart - m_tTime.QuadPart) / static_cast<float>(m_tSecond.QuadPart);
	m_tTime = tTime;
}
