#pragma once
#include "input/input.h"
#include "REndering/Camera.h"

class CameraControl
{
public:
	Camera& m_camera;
	float move_speed = 1;
	float zoom_speed = 100;
	float rotate_speed = 50;

	CameraControl(Camera& camera) : m_camera(camera) {

	}

	void ProcessInput(FP_LONG dt)
	{
		if (Input::keysDown[GLFW_KEY_UP])
			m_camera.moveForward(move_speed * dt);
		if (Input::keysDown[GLFW_KEY_DOWN])
			m_camera.moveForward(-move_speed * dt);
		if (Input::keysDown[GLFW_KEY_RIGHT])
			m_camera.moveRight(move_speed * dt);
		if (Input::keysDown[GLFW_KEY_LEFT])
			m_camera.moveRight(-move_speed * dt);
		if (Input::keysPressed[GLFW_KEY_SPACE])
		{
			m_camera.isLockedOn = !m_camera.isLockedOn;
		}
		m_camera.rotate(Input::mouseOffset.x * rotate_speed * dt, Input::mouseOffset.y * rotate_speed * dt);
		m_camera.zoom(Input::mouseScroll * -zoom_speed * dt);
		Input::Clear();
	}
};

