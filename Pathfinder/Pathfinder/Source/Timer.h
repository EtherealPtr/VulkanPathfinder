#pragma once

class Timer
{
public:
	Timer();

	double GetDeltaTime();

private:
	double m_PrevTime;
};

