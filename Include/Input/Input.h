#include <glfw3.h>
#include <functional>
#include <unordered_map>
#include <string>

class Input {
public:
	using KeyEventCallback = std::function<void(int, int)>;
	using MouseButtonEventCallback = std::function<void(int, int)>;
	using CursorPositionEventCallback = std::function<void(double, double)>;

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		for (const auto& callback : keyCallbacks) {
			callback.second(key, action);
		}
	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		for (const auto& callback : mouseButtonCallbacks) {
			callback.second(button, action);
		}
	}

	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
		for (const auto& callback : cursorPositionCallbacks) {
			callback.second(xpos, ypos);
		}
	}

	static void RegisterKeyCallback(const std::string& name, const KeyEventCallback& callback) {
		keyCallbacks[name] = callback;
	}

	static void RegisterMouseButtonCallback(const std::string& name, const MouseButtonEventCallback& callback) {
		mouseButtonCallbacks[name] = callback;
	}

	static void RegisterCursorPositionCallback(const std::string& name, const CursorPositionEventCallback& callback) {
		cursorPositionCallbacks[name] = callback;
	}

private:
	static std::unordered_map<std::string, KeyEventCallback> keyCallbacks;
	static std::unordered_map<std::string, MouseButtonEventCallback> mouseButtonCallbacks;
	static std::unordered_map<std::string, CursorPositionEventCallback> cursorPositionCallbacks;
};

