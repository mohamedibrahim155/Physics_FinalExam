#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"

#include <vector>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


const float SPEED = 0.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera
{
public:
    
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

        // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) 
    {
       // Position = position;
      //  WorldUp = up;
       // Yaw = yaw;
       // Pitch = pitch;


        //Initial Values
        transform.SetPosition(glm::vec3(0, 0.0f, 0));
        transform.SetOrientationFromDirections(glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
        transform.SetRotation(glm::vec3(0.0f, 180, 0.0f));


    }
        

        // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) 
    {
       // Position = glm::vec3(posX, posY, posZ);
       // WorldUp = glm::vec3(upX, upY, upZ);
       // Yaw = yaw;
       // Pitch = pitch;

        //Initial Values
        transform.SetPosition(glm::vec3(3.0f, 0.0f, -33.0f));
        transform.SetOrientationFromDirections(glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
        transform.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));


    }


    Transform transform;

        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 GetViewMatrix();
  

        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void ProcessKeyboard(Camera_Movement direction, float deltaTime);


        // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

        // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void ProcessMouseScroll(float yoffset);
   
        void updateCameraVectors();


        Transform* GetTransform();

        void SetTargetPosition(const glm::vec3& targetPos) {
            targetPosition = targetPos;
        }

        // Update camera position using lerp
        void UpdateCameraPosition(float deltaTime) {
            //Position = glm::mix(Position, targetPosition, lerpSpeed * deltaTime);         


            updateCameraVectors();

        }

       
        

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
   // void updateCameraVectors();


    glm::vec3 targetPosition;

    // Lerp speed for smooth interpolation
    float lerpSpeed = 2.0f;  // Adju
   
};
#endif