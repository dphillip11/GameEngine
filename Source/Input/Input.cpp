#include "PCH/pch.h"
#include "input/input.h"

std::unordered_map<int, bool>  Input::keysPressed;
std::unordered_map<int, bool>  Input::keysDown;
std::unordered_map<int, bool>  Input::keysReleased;

std::unordered_map<int, bool> Input::mousePressed;
std::unordered_map<int, bool> Input::mouseDown;
std::unordered_map<int, bool> Input::mouseReleased;

double Input::mouseScroll;
glm::vec2 Input::mouseOffset;

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS) {
		keysPressed[key] = true;
		keysDown[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		keysReleased[key] = true;
		keysDown[key] = false;
		keysPressed[key] = false;
	}
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		mousePressed[button] = true;
		mouseDown[button] = true;
	}
	else if (action == GLFW_RELEASE) {
		mouseReleased[button] = true;
		mouseDown[button] = false;
		mousePressed[button] = false;
	}
}

void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	static glm::vec2 mousePos;
	mouseOffset += glm::vec2(xpos, ypos) - mousePos;
	mousePos = glm::vec2(xpos, ypos);
}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	mouseScroll += yoffset;
}

void Input::Clear()
{
	mouseScroll = 0;
	mouseOffset = glm::vec2(0, 0);

	mousePressed.clear();
	mouseReleased.clear();

	keysPressed.clear();
	keysReleased.clear();
}
