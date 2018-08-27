#include "Camera.hpp"

#include <GL/freeglut.h>

Camera::Camera()
    :position(glm::vec3(0.0, 0.0, 0.0)), up(glm::vec3(0.0, 1.0, 0.0)), fovy(60.0), aspectRatio(1.0), zNear(1.0), zFar(100)
{}

glm::vec3 Camera::GetPosition() const
{
    return position;
}

glm::vec3 Camera::GetCenter() const
{
    return center;
}

float Camera::GetFovy() const
{
    return fovy;
}

float Camera::GetAspectRatio() const
{
    return aspectRatio;
}

void Camera::SetPosition(glm::vec3 newPos)
{
    position = newPos;
}

void Camera::SetCenter(glm::vec3 newCenter)
{
    center = newCenter;
}

void Camera::Translate(glm::vec3 amount)
{
    position = position + amount; 
}

void Camera::SetFovy(float newFovy)
{
    fovy = newFovy;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspectRatio, zNear, zFar);
}

void Camera::SetAspectRatio(float newAspectRatio)
{
    aspectRatio = newAspectRatio;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspectRatio, zNear, zFar);
}

void Camera::Apply()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
	    position.x, position.y, position.z,
	    center.x, center.y, center.z,
	    up.x, up.y, up.z );
}

