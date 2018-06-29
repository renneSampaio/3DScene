#ifndef _MATERIAL_HEADER__
#define _MATERIAL_HEADER__

#include <glm/vec4.hpp>

class Material
{
    public:
	void Apply();

	glm::vec4 GetAmbientColor() const;
	glm::vec4 GetDiffuseColor() const;
	glm::vec4 GetSpecularColor() const;
	glm::vec4 GetEmissionColor() const;
	float GetShininess() const;

	void SetAmbientColor(glm::vec4 color);
	void SetDiffuseColor(glm::vec4 color);
	void SetSpecularColor(glm::vec4 color);
	void SetEmissionColor(glm::vec4 color);
	void SetShininess(float s);

    private:
	glm::vec4 ambientColor;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	glm::vec4 emissionColor;
	float shininess;
	
};

#endif
