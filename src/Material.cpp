#include "Material.hpp"

#include <GL/freeglut.h>

void Material::Apply()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, &ambientColor.r);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuseColor.r);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &specularColor.r);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
}

glm::vec4 Material::GetAmbientColor() const
{
    return ambientColor;
}

glm::vec4 Material::GetDiffuseColor() const
{
    return diffuseColor;
}

glm::vec4 Material::GetSpecularColor() const
{
    return specularColor;
}

float Material::GetShininess() const
{
    return shininess;
}

void Material::SetAmbientColor(glm::vec4 color)
{
    ambientColor = color;
}

void Material::SetDiffuseColor(glm::vec4 color)
{
   diffuseColor  = color;
}

void Material::SetSpecularColor(glm::vec4 color)
{
    specularColor = color;
}

void Material::SetShininess(float s)
{
    shininess = s;
}
