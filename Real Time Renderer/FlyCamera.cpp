#include "FlyCamera.h"

//Camera class is a modified version of Joey DeVries' implementation from his Cell Rendering Engine 
//https://github.com/JoeyDeVries/Cell

namespace Override
{

    FlyCamera::FlyCamera(glm::vec3 position, glm::vec3 forward, glm::vec3 up) : Camera(position, forward, up)
    {
        Yaw = -90.0f;

        Forward = forward;  //apparently this is Camera class' Forward, Obviously because this class inherits from Camera
        m_WorldUp = Up;
        m_TargetPosition = position;
    }



    void FlyCamera::Update(float dt)
    {
        //I equate target position and position in the update function here, Instead of doing currentpos = targetpos, i do some lerping here to make the camera smoother 

        // slowly interpolate to target position each frame given some damping factor.
        // this gives smooth camera movement that fades out the closer we are to our target.
        Position = glm::lerp(Position, m_TargetPosition, (dt * Damping));
        Yaw = glm::lerp(Yaw, m_TargetYaw, (dt * Damping * 2.0f));
        Pitch = glm::lerp(Pitch, m_TargetPitch, (dt * Damping * 2.0f));

        // calculate new cartesian basis vectors from yaw/pitch pair:
        glm::vec3 newForward;
        newForward.x = cos(0.0174533 * Pitch) * cos(0.0174533 * Yaw);
        newForward.y = sin(0.0174533 * Pitch);
        newForward.z = cos(0.0174533 * Pitch) * sin(0.0174533 * Yaw);
        Forward = glm::normalize(newForward);
        Right = glm::normalize(glm::cross(Forward, m_WorldUp));
        Up = glm::cross(Right, Forward);

        // calculate the new view matrix
        Camera::Update(dt);
    }


    void FlyCamera::InputKey(float dt, CAMERA_MOVEMENT direction)
    {

        float speed = MovementSpeed * dt;


        if (direction == CAMERA_FORWARD)
            m_TargetPosition = m_TargetPosition + Forward * speed;
        else if (direction == CAMERA_BACK)
            m_TargetPosition = m_TargetPosition - Forward * speed;
        else if (direction == CAMERA_LEFT)
            m_TargetPosition = m_TargetPosition - Right * speed;
        else if (direction == CAMERA_RIGHT)
            m_TargetPosition = m_TargetPosition + Right * speed;
        else if (direction == CAMERA_UP)
            m_TargetPosition = m_TargetPosition + m_WorldUp * speed;
        else if (direction == CAMERA_DOWN)
            m_TargetPosition = m_TargetPosition - m_WorldUp * speed;


    }


    void FlyCamera::InputMouse(double xposIn, double yposIn)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        float xmovement = xoffset * MouseSensitivty;
        float ymovement = yoffset * MouseSensitivty;

        m_TargetYaw += xmovement;
        m_TargetPitch += ymovement;

        // prevents calculating the length of the null vector
        if (m_TargetYaw == 0.0f) m_TargetYaw = 0.01f;
        if (m_TargetPitch == 0.0f) m_TargetPitch = 0.01f;

        // it's not allowed to move the pitch above or below 90 degrees asctime the current 
        // world-up vector would break our LookAt calculation.
        if (m_TargetPitch > 89.0f)  m_TargetPitch = 89.0f;
        if (m_TargetPitch < -89.0f) m_TargetPitch = -89.0f;

        Pitch = m_TargetPitch;
        Yaw = m_TargetYaw;
    }
}
