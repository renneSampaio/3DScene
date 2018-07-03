#include "Light.hpp"

#include <GL/freeglut.h>

Light::Light(int id)
    :id(id), constantAttenuation(1.0), linearAttenuation(0.0), quadraticAttenuation(0.0)
{}

void Light::Toogle() const
{
    if (glIsEnabled(GL_LIGHT0+id))
	TurnOff();
    else
	TurnOn();
}

void Light::TurnOn() const
{
    glEnable(GL_LIGHT0+id);
}

void Light::TurnOff() const
{
    glDisable(GL_LIGHT0+id);
}

glm::vec4 Light::GetPosition() const
{
    return position;
}

glm::vec4 Light::GetDiffuseColor() const
{
    return diffuseColor;
}

glm::vec4 Light::GetSpecularColor() const
{
    return specularColor;
}

glm::vec4 Light::GetAmbientColor() const
{
    return ambientColor;
}

float Light::GetConstantAttenuation() const
{
    return constantAttenuation;
}

float Light::GetLinearAttenuation() const
{
    return linearAttenuation;
}

float Light::GetQuadraticAttenuation() const
{
    return quadraticAttenuation;
}

void Light::SetPosition(glm::vec4 newPosition)
{
    position = newPosition;
}

void Light::SetDiffuseColor(glm::vec4 color)
{
    diffuseColor = color;
}

void Light::SetSpecularColor(glm::vec4 color)
{
    specularColor = color;
}

void Light::SetAmbientColor(glm::vec4 color)
{
    ambientColor = color;
}

void Light::SetConstantAttenuation(float att)
{
    constantAttenuation = att;
}

void Light::SetLinearAttenuation(float att)
{
    linearAttenuation = att;
}

void Light::SetQuadraticAttenuation(float att)
{
    quadraticAttenuation = att;
}

void Light::Apply() const
{
    if (!glIsEnabled(GL_LIGHT0+id))
	return;

    glLightfv(GL_LIGHT0+id, GL_POSITION, &position.x);
    glLightfv(GL_LIGHT0+id, GL_DIFFUSE, &diffuseColor.r); 
    glLightfv(GL_LIGHT0+id, GL_SPECULAR, &specularColor.r);
    glLightfv(GL_LIGHT0+id, GL_AMBIENT, &ambientColor.r);
    glLightf(GL_LIGHT0+id, GL_CONSTANT_ATTENUATION, constantAttenuation);
    glLightf(GL_LIGHT0+id, GL_LINEAR_ATTENUATION, linearAttenuation);
    glLightf(GL_LIGHT0+id, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
}
