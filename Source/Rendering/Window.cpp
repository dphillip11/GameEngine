#include "PCH/pch.h"
#include "Rendering/Window.h"
#include "Input/input.h"

Window::Window(const unsigned int width, const unsigned int height, const char* name)
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, Input::KeyCallback);
	glfwSetMouseButtonCallback(window, Input::MouseButtonCallback);
	glfwSetCursorPosCallback(window, Input::CursorPositionCallback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << ("Failed to initialize GLAD") << std::endl;
	}

	// Set the projection matrix with adjusted clipping planes
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1000, 1000, -1000, 1000, -1000, 1000);  // Adjust the parameters as needed
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


bool Window::closed() {
	return glfwWindowShouldClose(window);
}

void Window::update()
{
	glfwSwapBuffers(window);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();
}

void Window::terminate()
{
	glfwTerminate();
}