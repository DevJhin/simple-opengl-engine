#pragma once
class Time
{
public:
	static void update(double ct);

	static float getCurrentTime();

	static float getDeltaTime();

	static float setTimeScale();
	static int getFrameCount();

	static void init(double t);

private:
    static double currentTime;
    static double deltaTime;

	static double lastTime;

	static int frameCount;
	
	static double timeScale;

};

