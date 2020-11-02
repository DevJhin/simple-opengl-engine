#pragma once
#include "Window.h"

class Application
{	
public:
	Application();
	~Application();
	
	static Application* getInstance();

	Window* getWindow() const;
	
	void Run();

	void terminate();
	bool ShouldClose() const;
	
	void OnExitKeyPressAction();
private:
	static Application* instance;
	Window* window;
};

