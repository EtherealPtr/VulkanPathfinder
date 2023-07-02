#include "Timer.h"
#include <glfw3.h>

Timer::Timer() : 
	m_PrevTime(glfwGetTime())
{}

double Timer::GetDeltaTime()
{
	const double currentTime = glfwGetTime();
	const double dt = currentTime - m_PrevTime;
	m_PrevTime = currentTime;
	return dt;
}
