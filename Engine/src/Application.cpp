
//Note that GL should be included first than GLEW.
#include <GL/glew.h>

#include "Application.h"

#include "World.h"

#include "LogMacros.h"

#include "Time.h"
#include "GL.h"

Application* Application:: instance;

Application::Application()
{
    // Initialize GLFW.
    glfwInit();

    // Allow GLEW features.
	
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

	
	window = new Window(800, 800);

    glewExperimental = GL_TRUE;

	glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    GL::EnableStencilTest();
	
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize GLEW.
    if (glewInit() != GLEW_OK)
    {
        LOG_ERROR("GLEW initialization failed!");
        terminate();
        return;
    }

    Input::addOnKeyPressAction(KeyCode::ESC,std::bind(&Application::OnExitKeyPressAction, this));
}

void Application::OnExitKeyPressAction()
{
	window->close();
}

Window* Application::getWindow() const
{
	return window;
}

void Application::Run()
{
	Time::init(glfwGetTime());

	World::GetInstance()->Init();
	
	while(!ShouldClose())
    {
		//Update time.
		
        window->clear(0.0f, 0.0f, 0.0f, 1.0f);
		
        Time::update(glfwGetTime());
		World::GetInstance()->Update();

		window->swapBuffers();
	}

	terminate();
}


Application* Application::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Application();
    }
    return instance;
}

void Application::terminate()
{
	delete World::GetInstance();
	delete window;
	glfwTerminate();
}

Application::~Application()
{
    terminate();
}

bool Application::ShouldClose() const
{
	return window->shouldClose();
}



