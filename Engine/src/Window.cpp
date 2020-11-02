#include "Window.h"
#include <GLFW/glfw3.h>

int DEFAULT_SCREEN_WIDTH = 800;
int DEFAULT_SCREEN_HEIGHT = 800;

Vector2Int Window::screenSize;

class Window::Impl
{
public:
    bool shouldClose()
    {
        return glfwWindowShouldClose(glfwWindow);
    }

	void swapBuffers()
    {
        glfwSwapBuffers(glfwWindow);	    
    }

    void close()
    {
        glfwSetWindowShouldClose(glfwWindow, true);
    }

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);

    	screenSize.x = width;
    	screenSize.y = height;
    }


    Impl(int width, int height)
    {
        glfwWindow = glfwCreateWindow(width, height, "HW3", nullptr, nullptr);
        if (glfwWindow == nullptr)
        {
            //LOG_ERROR("Failed to create GLFW glfwWindow");
            glfwTerminate();
            return;
        }
    	screenSize.x = width;
    	screenSize.y = height;
        glfwMakeContextCurrent(glfwWindow);

        glfwSetWindowSizeCallback(glfwWindow, framebuffer_size_callback);
        glViewport(0, 0, width, height);
        Input::init(glfwWindow);
    }

	

	~Impl()
    {
        glfwDestroyWindow(glfwWindow);
    }
	
private:
    GLFWwindow* glfwWindow;
};

Window::Window(int width, int height) : pImpl(new Impl(width, height)){}

Window::~Window() = default;

bool Window::shouldClose()
{
	return pImpl->shouldClose();
}

void Window::close()
{
    return pImpl->close();
}

void Window::clear(float r, float g, float b, float a)
{
    glClearColor(0.1f, 0.1f, 0.13f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void Window::swapBuffers()
{
	pImpl->swapBuffers();
}

Vector2Int Window::getScreenSize()
{
	return screenSize;
}