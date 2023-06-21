#include <glfw3.h>
#include <functional>
#include <unordered_map>
#include <string>

class Input {
public:

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);


	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	static void Clear();


	static std::unordered_map<int, bool> keysPressed;
	static std::unordered_map<int, bool> keysDown;
	static std::unordered_map<int, bool> keysReleased;

	static std::unordered_map<int, bool> mousePressed;
	static std::unordered_map<int, bool> mouseDown;
	static std::unordered_map<int, bool> mouseReleased;

	static double mouseScroll;
	static glm::vec2 mouseOffset;
};

