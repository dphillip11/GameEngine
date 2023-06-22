#include "GLFW3.h"


#pragma once
class GUI {
public:
	void Init(GLFWwindow* window);

	void Render();

	void Close();

private:

	void DisplayHierarchy();

	void DisplaySpawnButton();

	void DisplayDemoWindow();

	void DisplaySystemWindow();

	void DisplayInspectorWindow();

	void DisplayGameObject(int id);

	void DisplayTransform(int id);

	void DisplayTransformInfo();

	void DisplayRigidBody(int id);

	void DisplayBoxCollider(int id);

	bool hierarchy_window = true;
	bool system_window = true;
	bool demo_window = false;
	bool inspector_window = true;
	int inspectorID = -1;
	std::string inspectorNamestring = "";
	const char* glsl_version = "#version 130";
	GLFWwindow* m_window;
	ImGuiIO* io;
};