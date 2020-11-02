#pragma once
#include <memory>

#include "CoreTypes.h"

class Window
{	
public:
	Window(int width, int height);
	~Window();

	bool shouldClose();
	void close();
	void clear(float r, float g, float b, float a);
	void swapBuffers();

	static Vector2Int getScreenSize();
private:
	static Vector2Int screenSize;
	class Impl; std::unique_ptr<Impl> pImpl;
	
};

