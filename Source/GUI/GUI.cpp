#include "PCH/pch.h"
#include "GUI/GUI.h"
#include "Scene/scene.h"
std::unique_ptr<int> uniquePtr = std::make_unique<int>();

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
	DisplayEntities();
	ImGui::End();
}

void GUI::DisplayEntities()
{
	auto& entities = Scene::Get()->entityRegistry->getHashMap();
	for (auto& entity : entities)
	{
		ImGui::Text(("Entity " + std::to_string(entity.first)).c_str());
		ImGui::PushID(entity.first);
		if (ImGui::Button("Inspect"))
		{
			std::cout << entity.first << std::endl;
			inspectorID = entity.first;
			inspector_window = true;
		}
		ImGui::PopID();
	}
}

void GUI::DisplayParticle(EntityRef entityRef)
{
	auto& entity = entityRef.getEntity();
	auto particle_positions = entity.GetComponents<Particle_Position>();
	auto particle_radii = entity.GetComponents<Particle_Radius>();
	auto particle_iMass = entity.GetComponents<Particle_InverseMass>();
	for (int i = 0; i < particle_positions.size(); i++)
	{
		ImGui::DragFloat3("Position", &particle_positions[i].get().value.x);
		ImGui::DragFloat("Radius", &particle_radii[i].get().value);
		ImGui::DragFloat("Inverse Mass", &particle_iMass[i].get().value);
	}

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
	if (ImGui::Button("Pause"))
	{
		Scene::Get()->isPaused = !Scene::Get()->isPaused;
	}
	ImGui::DragFloat3("Camera Position", reinterpret_cast<float*>(&Scene::Get()->camera._position));
	ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
	ImGui::End();
}

void GUI::DisplayInspectorWindow()
{
	ImGui::Begin("Inspector Window", &inspector_window);
	if (Scene::Get()->entityRegistry->is_valid_key(inspectorID))
	{
		auto entity = Scene::Get()->entityRegistry->GetRef(inspectorID);
		if (entity.getEntity().hasComponent<Particle_Position>())
			DisplayParticle(entity);
		if (entity.getEntity().hasComponent<SpringForce>() || entity.getEntity().hasComponent<GravityForce>())
			DisplayForces(entity);
	}
	ImGui::End();
}

void GUI::DisplayForces(EntityRef entityRef)
{
	auto& entity = entityRef.getEntity();
	auto spring_forces = entity.GetComponents<SpringForce>();
	auto gravity_forces = entity.GetComponents<GravityForce>();
	int index = 0;
	for (auto& spring_force : spring_forces)
	{
		ImGui::PushID(index);
		ImGui::DragFloat("Spring constant", &spring_force.get().m_springConstant);
		ImGui::DragFloat("rest length", &spring_force.get().m_restLength);
		ImGui::DragInt("other particle", &spring_force.get().m_other.m_entityID);
		ImGui::PopID();
		index++;
	}

	if (ImGui::Selectable("Add SpringForce"))
	{
		SpringForce s;
		s.m_other = Scene::Get()->entityRegistry->GetRef(2);
		s.entity = entityRef;
		entity.AddComponent(s);
	}
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