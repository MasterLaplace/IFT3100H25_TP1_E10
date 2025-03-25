#include "Camera.hpp"

Camera::Camera()
{
    setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    setFov(90.0f);
    setAspectRatio(ofGetWidth() / ofGetHeight());
    setNearClip(0.1f);
    setFarClip(10000.0f);
    setVFlip(true);
}

void Camera::toggleProjection()
{
    isOrthographic = !isOrthographic;

    if (isOrthographic)
    {
        setScale(0.5f);
        enableOrtho();
    }
    else
    {
        disableOrtho();
    }
}

void Camera::update()
{
    float speed = 5.0;
    glm::vec3 movement(0.0);

    if (isOrthographic)
    {
        if (ofGetKeyPressed(OF_KEY_UP))
        {
            movement -= glm::vec3(0.0f, speed, 0.0f); // Monter
        }
        if (ofGetKeyPressed(OF_KEY_DOWN))
        {
            movement += glm::vec3(0.0f, speed, 0.0f); // Descendre
        }
    }
    else
    {
        if (ofGetKeyPressed(OF_KEY_UP))
        {
            movement += getLookAtDir() * speed; // Avancer
        }
        if (ofGetKeyPressed(OF_KEY_DOWN))
        {
            movement -= getLookAtDir() * speed; // Reculer
        }
        
        // When a is pressed, the camera will rotate to the left
        if (ofGetKeyPressed('a'))
        {
            glm::vec3 newLookAtDir = glm::rotate(getLookAtDir(), glm::radians(speed), getUpDir());
            lookAt(getPosition() + newLookAtDir);
        }
        
        // When d is pressed, the camera will rotate to the right
        if (ofGetKeyPressed('d'))
        {
            glm::vec3 newLookAtDir = glm::rotate(getLookAtDir(), glm::radians(-speed), getUpDir());
            lookAt(getPosition() + newLookAtDir);
        }
    }
    if (ofGetKeyPressed(OF_KEY_LEFT))
    {
        movement -= getSideDir() * speed; // Gauche
    }
    if (ofGetKeyPressed(OF_KEY_RIGHT))
    {
        movement += getSideDir() * speed; // Droite
    }

    if (ofGetKeyPressed('1'))
    {
        setPosition(glm::vec3(0.0f, 0.0f, 50.0f)); // Front view
        lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    if (ofGetKeyPressed('2'))
    {
        setPosition(glm::vec3(50.0f, 0.0f, 0.0f)); // Right view
        lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    if (ofGetKeyPressed('3'))
    {
        setPosition(glm::vec3(-50.0f, 0.0f, 0.0f)); // Left view
        lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    if (ofGetKeyPressed('4'))
    {
        setPosition(glm::vec3(0.0f, 50.0f, 0.0f)); // Top view
        lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    if (ofGetKeyPressed('5'))
    {
        setPosition(glm::vec3(0.0f, -50.0f, 0.0f)); // Bottom view
        lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    }

    move(movement);
}
