#include "Camera.h"
#include <iostream>
//Camera class is a modified version of Joey DeVries' implementation from his Cell Rendering Engine 
//https://github.com/JoeyDeVries/Cell

namespace Override
{
    void Camera::Update(float dt)
    {
        UpdateView();
    }

    void Camera::SetPerspective(float fov, float aspect, float near, float far)
    {
        Perspective = true;
        Projection = glm::perspective(fov, aspect, near, far);
        FOV = fov;
        Aspect = aspect;
        Near = near;
        Far = far;
    }


    void Camera::SetOrthographic(float left, float right, float top, float bottom, float near, float far)
    {
        Perspective = false;
        Projection = glm::ortho(left, right, top, bottom, near, far);
        Near = near;
        Far = far;
    }


    void Camera::UpdateView()
    {
        View = glm::lookAt(Position, Position + Forward, Up);
    }
}
