#pragma once

#include "Camera.h"
#include "globals.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/compatibility.hpp>

/*

  Derivation of the base camera with support for fly-through motions. Think of WASD forward/right
  type of movement, combined with strafing and free yaw/pitch camera rotation.

*/

//Camera class is a modified version of Joey DeVries' implementation from his Cell Rendering Engine 
//https://github.com/JoeyDeVries/Cell

namespace Override
{

	class FlyCamera : public Camera
	{
	private:
		glm::vec3 m_TargetPosition;
		glm::vec3 m_WorldUp;
		float m_TargetYaw;
		float m_TargetPitch;

	public:
		float Yaw;
		float Pitch;

		float MovementSpeed = 5.0f;
		float MouseSensitivty = 0.1f;
		float Damping = 5.0f;


		float lastX = Globals::SCR_WIDTH / 2.0f;
		float lastY = Globals::SCR_HEIGHT / 2.0f;
		bool firstMouse = true;


		FlyCamera(glm::vec3 position, glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

		virtual void Update(float dt);


		//Abstract Input funcs, meant to be defined by the derived camera class
		virtual void InputKey(float dt, CAMERA_MOVEMENT direction);
		virtual void InputMouse(double xposIn, double yposIn);

	};

}

