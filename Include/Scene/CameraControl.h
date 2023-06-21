#pragma once
#include "input/input.h"
#include "REndering/Camera.h"

class CameraControl
{
public:
	Camera m_camera;
	float cam_move_speed = 1.0f;

	void RegisterCallbacks() {
		Input::RegisterKeyCallback("w", std::bind(&CameraControl::W_Callback, this, std::placeholders::_1, std::placeholders::_2));
		Input::RegisterKeyCallback("a", std::bind(&CameraControl::A_Callback, this, std::placeholders::_1, std::placeholders::_2));
		Input::RegisterKeyCallback("s", std::bind(&CameraControl::S_Callback, this, std::placeholders::_1, std::placeholders::_2));
		Input::RegisterKeyCallback("d", std::bind(&CameraControl::D_Callback, this, std::placeholders::_1, std::placeholders::_2));
	}

	void W_Callback(int A, int B) {
		m_camera.moveForward(cam_move_speed);
	}

	void A_Callback(int A, int B) {
		m_camera.moveRight(-cam_move_speed);
	};

	void S_Callback(int A, int B) {
		m_camera.moveForward(-cam_move_speed);
	};

	void D_Callback(int A, int B) {
		m_camera.moveRight(cam_move_speed);
	};
};
