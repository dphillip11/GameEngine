#include "PCH/pch.h"
#include "GUI/GUI.h"
#include "Scene/scene.h"

void GUI::Init(GLFWwindow* window)
{
	m_window = window;
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::GetIO().WantCaptureMouse = true;
}

void GUI::Render() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();

	if (demo_window)
		DisplayDemoWindow();
	if (system_window)
		DisplaySystemWindow();
	if (hierarchy_window)
		DisplayHierarchy();
	if (inspector_window)
		DisplayInspectorWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void GUI::DisplayHierarchy() {
	ImGui::SetNextWindowPos(ImVec2(0, 200));
	ImGui::SetNextWindowSize(ImVec2(450, -1));
	ImGui::Begin("Hierarchy", &hierarchy_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	ImGui::SetWindowFontScale(1.5f);
	DisplaySpawnButton();
	ImGui::End();
}

void GUI::DisplayGameObject(int id)
{

}

void GUI::DisplaySpawnButton()
{


}

void GUI::DisplayDemoWindow()
{
	ImGui::ShowDemoWindow(&demo_window);
}

void GUI::DisplaySystemWindow()
{

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("System Window", &system_window);
	ImGui::SetWindowFontScale(1.5f);
	ImGui::DragFloat3("Camera Position", reinterpret_cast<float*>(&Scene::Get()->camera._position));
	ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
	ImGui::End();
}

void GUI::DisplayInspectorWindow()
{

}

void GUI::DisplayTransformInfo()
{


}

void GUI::DisplayTransform(int id)
{

}

void GUI::DisplayBoxCollider(int id)
{

}

void GUI::DisplayRigidBody(int id)
{

}

void GUI::Close()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}