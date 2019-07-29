#include "main.h"
#include "Timer.h"

Timer::Timer()
{
	currentTime = TIME_MAX;
	use = false;

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		digit[i];
	}

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i] = new Digit(i);
	}
}


Timer::~Timer()
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		delete time[i];
	}
}

void Timer::Update()
{
	if (use)
	{
		currentTime--;
		currentTime = max(currentTime, 0);
	}

	digit[0] = (currentTime / 60) % 10;
	digit[1] = (currentTime / 600) % 10;

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i]->Update(digit[i]);
	}
}

void Timer::Draw()
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i]->Draw();
	}
}

void Timer::Start()
{
	use = true;
}

void Timer::Stop()
{
	use = false;
}

DWORD Timer::Check()
{
	return currentTime;
}