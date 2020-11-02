#include "Time.h"

double Time::currentTime;
double Time::deltaTime;

double Time::lastTime;

double Time::timeScale;

int Time::frameCount;

void Time::update(double ct)
{
	lastTime = currentTime;
	currentTime = ct;
	deltaTime = (currentTime - lastTime) * timeScale;
	frameCount+=1;
}

float Time::getCurrentTime()
{
	return float(currentTime);
}

float Time::getDeltaTime()
{
	return float(deltaTime);
}

float Time::setTimeScale()
{
	return float(timeScale);
}

int Time::getFrameCount()
{
	return frameCount;
}

void Time::init(double t)
{
	currentTime = t;
	deltaTime = 0;
	lastTime = t;

	timeScale = 1;
	frameCount = 0;
}
