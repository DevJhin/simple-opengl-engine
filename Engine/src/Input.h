#pragma once
#include <functional>
#include <GLFW/glfw3.h>
#include <map>

#include "CoreTypes.h"

enum class KeyCode
{
	LEFT = GLFW_KEY_LEFT,
	RIGHT = GLFW_KEY_RIGHT,
	UP = GLFW_KEY_UP,
	DOWN = GLFW_KEY_DOWN,
	ESC = GLFW_KEY_ESCAPE,
	W = GLFW_KEY_W,
	A = GLFW_KEY_A,
	S = GLFW_KEY_S,
	D = GLFW_KEY_D,
	R = GLFW_KEY_R,
	SPACE= GLFW_KEY_SPACE
};

enum class ActionState
{
	PRESS = GLFW_PRESS,
	REPEAT = GLFW_REPEAT,
	RELEASE = GLFW_RELEASE
};


using OnKeyPressAction = std::function<void()>;
using OnMouseButtonPressAction = std::function<void()>;
using OnMouseButtonRepeatAction = std::function<void()>;
using OnMouseButtonReleaseAction = std::function<void()>;

class Input
{
private:
	static std::map<KeyCode, std::vector<OnKeyPressAction>> keyPressActionMap;

	
	static List<OnMouseButtonPressAction> mouseButtonPressActions;
	static List<OnMouseButtonRepeatAction> mouseButtonRepeatActions;
	static List<OnMouseButtonReleaseAction> mouseButtonReleaseActions;
	
	static bool isMouseButtonRepeating;

	/*
	 * Internal Callbacks;
	 */
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scanCode, int actionCode, int mods);
	static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static void mouseCallback(GLFWwindow* window, int button, int actionCode, int mods);
	static void cursorPosCallback(GLFWwindow* window, double x, double y);

	
public:

	static void init(GLFWwindow* window);
	static void update();
	static void addOnKeyPressAction(KeyCode keyCode, const OnKeyPressAction& keyDownDelegate);

	static Vector2 getMousePosition();

	static Vector2 getAxis()
	{
		Vector2 input(0,0);

		bool isD = getKey(KeyCode::D);
		bool isA = getKey(KeyCode::A);

		if(isD && isA) input.x = 0;
		else if(isD) input.x = 1;
		else if(isA) input.x = -1;

		bool isW = getKey(KeyCode::W);
		bool isS = getKey(KeyCode::S);

		if(isW && isS) input.y = 0;
		else if (isW) input.y = 1;
		else if (isS) input.y = -1;
		
		return input;
	}

	/*
	 * Callbacks;
	 */
	static void addOnMousePressAction(const OnMouseButtonPressAction& Delegate);
	static void addOnMouseRepeatAction(const OnMouseButtonRepeatAction& Delegate);
	static void addOnMouseReleaseAction(const OnMouseButtonReleaseAction& Delegate);

	/*
	 * boolean ;
	 */
	static bool getKeyDown(KeyCode keyCode);
	static bool getKey(KeyCode keyCode);
	static bool getKeyUp(KeyCode keyCode);
	
	static bool getMouseButtonDown(int mouseButton);
	static bool getMouseButton(int mouseButton);
	static bool getMouseButtonUp(int mouseButton);

	static Vector2 mouseScrollDelta();
	
};

