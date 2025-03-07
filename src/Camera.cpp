#include "Camera.hpp"

Camera::Camera()
{
    setPosition(glm::vec3(0.0f, 0.0f, 50.0f));
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
    }
    if (ofGetKeyPressed(OF_KEY_LEFT))
    {
        movement -= getSideDir() * speed; // Gauche
    }
    if (ofGetKeyPressed(OF_KEY_RIGHT))
    {
        movement += getSideDir() * speed; // Droite
    }

    move(movement);
}
