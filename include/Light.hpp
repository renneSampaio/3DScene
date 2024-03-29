#ifndef _LIGHT_HEADER__
#define _LIGHT_HEADER__

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Light
{
    public:
	Light(int id);

	void Toogle() const;
	void TurnOn() const;
	void TurnOff() const;

	void Apply() const;

	glm::vec4 GetPosition() const;
	glm::vec4 GetDiffuseColor() const;
	glm::vec4 GetSpecularColor() const;
	glm::vec4 GetAmbientColor() const;
	float GetConstantAttenuation() const;
	float GetLinearAttenuation() const;
	float GetQuadraticAttenuation() const;

	void SetPosition(glm::vec4 newPosition);
	void SetDiffuseColor(glm::vec4 color);
	void SetSpecularColor(glm::vec4 color);
	void SetAmbientColor(glm::vec4 color);
	void SetConstantAttenuation(float att);
	void SetLinearAttenuation(float att);
	void SetQuadraticAttenuation(float att);

    private:
	int id;

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

	glm::vec4 position;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	glm::vec4 ambientColor;
};

#endif
