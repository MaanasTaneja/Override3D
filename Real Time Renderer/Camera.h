#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Camera class is a modified version of Joey DeVries' implementation from his Cell Rendering Engine 
//https://github.com/JoeyDeVries/Cell

namespace Override
{
    // defines several possible options for camera movement. Used as abstraction to stay away from 
    // window-system specific input methods.
    enum CAMERA_MOVEMENT {
        CAMERA_FORWARD,
        CAMERA_BACK,
        CAMERA_LEFT,
        CAMERA_RIGHT,
        CAMERA_UP,
        CAMERA_DOWN,
    };

    /*

      Basic root camera. Only does relevant camera calculations with manual forced direction
      setters. This camera should only be used in code and not respond to user input; the
      derived cameras are for user/player interaction.

    */

    class Camera
    {
    private:
        void UpdateView();
    public:
        glm::mat4 Projection;
        glm::mat4 View;

        glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 Forward = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);

        float FOV;
        float Aspect;
        float Near;
        float Far;
        bool  Perspective;

        Camera() {}
        Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up) :Position{ position }, Forward{ forward }, Up{ up } {  }

        virtual void Update(float dt);

        void SetPerspective(float fov, float aspect, float near, float far);
        void SetOrthographic(float left, float right, float top, float bottom, float near, float far);

        //Functions that can be overridden, if I just give Scene a Camera Class, it wont do anything as there is nothing to do!
        virtual void InputKey(float dt, CAMERA_MOVEMENT direction) {}
        virtual void InputMouse(double xposIn, double yposIn) {}
    };
}

