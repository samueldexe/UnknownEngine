
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Abstract away specific library input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values if not specified 
const float YAW = -90.f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// An camera class that processes input and calculates the correct view matrix for OpenGL
class Camera
{
public:
    // Camera attributes
    glm::vec3 Position {};
    glm::vec3 Front {};
    glm::vec3 Up {};
    glm::vec3 Right {};
    glm::vec3 WorldUp {};

    // Euler angles
    float Yaw {};
    float Pitch {};

    // Camera options
    float MovementSpeed {};
    float MouseSensitivity {};
    float Zoom {};

    // Constructor with glm::vec3
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = worldUp;
        Yaw = yaw;
        Pitch = pitch;
        
        UpdateCameraVectors();
    }

    ~Camera() {}

    // Returns the view matrix for OpenGL
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // Process input received from keyboard
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // Process input received from mouse
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // We make sure that the pitch can not go out of bounds
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        UpdateCameraVectors();
    }

    // Process input received from a mouse scroll wheel
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        
        // Restrain zoom
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // Function to update the cameras direction vectors
    void UpdateCameraVectors()
    {
        // Calculate front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        // Calculate Right and Up direction vectors
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif