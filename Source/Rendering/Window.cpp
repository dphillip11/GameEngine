#include "PCH/pch.h"
#include "Rendering/Window.h"

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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

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

void Window::framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT)
{
	glViewport(0, 0, WIDTH, HEIGHT);
}

void Window::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	/*input->mouseX = (float)xpos;
	input->mouseY = (float)ypos;*/
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//input->scrollOffset -= (float)yoffset;
}


void Window::captureInput()
{
	/*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		input->LogKey(KEYS::UP);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		input->LogKey(KEYS::DOWN);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		input->LogKey(KEYS::LEFT);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		input->LogKey(KEYS::RIGHT);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		input->LogKey(KEYS::W);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		input->LogKey(KEYS::A);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		input->LogKey(KEYS::S);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		input->LogKey(KEYS::D);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		input->LogKey(KEYS::SPACE);
	}*/

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
	captureInput();
}

void Window::terminate()
{
	glfwTerminate();
}