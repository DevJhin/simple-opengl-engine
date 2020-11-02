#include "Input.h"

std::map<KeyCode, std::vector<OnKeyPressAction>> Input::keyPressActionMap;

std::vector<OnMouseButtonPressAction> Input::mouseButtonPressActions;
std::vector<OnMouseButtonRepeatAction> Input::mouseButtonRepeatActions;
std::vector<OnMouseButtonReleaseAction> Input::mouseButtonReleaseActions;


Vector2 mousePosition;
Vector2 scrollDelta;

GLFWwindow* glfwWindow;

bool Input::isMouseButtonRepeating;



void Input::init(GLFWwindow* window)
{
	glfwWindow = window;
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetScrollCallback(glfwWindow, scrollCallback);
}

//ActionState lastMouseButtonState;

void Input::update()
{
	scrollDelta = Vector2(0, 0);
	glfwPollEvents();
	
	if (isMouseButtonRepeating) {
		for (auto& action : mouseButtonRepeatActions)
		{
			action();
		}
	}
	
}

/*
 *GLFW callbacks.
 *
 */

void Input::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	scrollDelta.x = xOffset;
	scrollDelta.y = yOffset;
}

void Input::mouseCallback(GLFWwindow* window, int button, int actionCode, int mods)
{
	if (static_cast<ActionState>(actionCode) == ActionState::PRESS) {
		if(!isMouseButtonRepeating){
			for (auto& action : mouseButtonPressActions)
			{
				action();
			}
			isMouseButtonRepeating = true;
		}
	}
	else if (static_cast<ActionState>(actionCode) == ActionState::RELEASE) {
		for (auto& action : mouseButtonReleaseActions)
		{
			action();
		}
		isMouseButtonRepeating = false;
	}
}

void Input::cursorPosCallback(GLFWwindow* window, double x, double y)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	mousePosition.x = (static_cast<float>(x) / static_cast<float>(width)) * 2.0f -1.0f;
	mousePosition.y = (static_cast<float>(y) / static_cast<float>(height)) * -2.0f + 1.0f;

	
}

Dictionary<KeyCode,ActionState> keyState;

void Input::keyCallback(GLFWwindow* window, int key, int scanCode, int actionCode, int mods)
{
	if(static_cast<ActionState>(actionCode) == ActionState::PRESS){
		auto pressActions = keyPressActionMap[static_cast<KeyCode>(key)];

		for (auto& action : pressActions)
		{
			action();
		}
		
	}
	else
	{
		
	}
}

/*
 * Action adders.
 */

void Input::addOnKeyPressAction(KeyCode keyCode, const OnKeyPressAction& keyDownDelegate)
{
	keyPressActionMap[keyCode].push_back(keyDownDelegate);
}

Vector2 Input::getMousePosition()
{
	return mousePosition;
}


void Input::addOnMousePressAction(const OnMouseButtonPressAction& Delegate)
{
	mouseButtonPressActions.push_back(Delegate);
}

void Input::addOnMouseRepeatAction(const OnMouseButtonRepeatAction& Delegate)
{
	mouseButtonRepeatActions.push_back(Delegate);
}

void Input::addOnMouseReleaseAction(const OnMouseButtonReleaseAction& Delegate)
{
	mouseButtonReleaseActions.push_back(Delegate);
}

bool Input::getKey(KeyCode keyCode)
{
	return static_cast<ActionState>(glfwGetKey(glfwWindow, (int)keyCode)) == ActionState::PRESS;
}


bool Input::getMouseButtonDown(int mouseButton)
{
	auto state = ActionState(glfwGetMouseButton(glfwWindow, mouseButton));

	if(state == ActionState::PRESS)
	{
		
	}
	return false;
}

bool Input::getMouseButton(int mouseButton)
{
	return glfwGetMouseButton(glfwWindow,mouseButton) == int(ActionState::PRESS);
}

bool Input::getMouseButtonUp(int mouseButton)
{
	return false;
}

Vector2 Input::mouseScrollDelta()
{
	return scrollDelta;
}


/**
 * \brief // Resize viewport on 'glfwSetFramebufferSizeCallback'.
 */
void Input::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new glfwWindow dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

}