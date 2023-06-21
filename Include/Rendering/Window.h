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
};



