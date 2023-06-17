#pragma once

class Window {
public:
	Vector3 clearColor = 1;
	GLFWwindow* window;
	Window(const unsigned int width, const unsigned int height, const char* name);
	bool closed();
	void update();
	void terminate();
	~Window() { terminate(); }
private:
	void captureInput();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};



