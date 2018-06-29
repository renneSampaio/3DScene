#ifndef _LIGHT_HEADER__
#define _LIGHT_HEADER__

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Light
{
    public:
	Light(int id);
	~Light();

	void Toogle() const;
	void TurnOn() const;
	void TurnOff() const;

	void Apply() const;

	glm::vec4 GetPosition() const;
	glm::vec4 GetDiffuseColor() const;
	glm::vec4 GetSpecularColor() const;
	glm::vec4 GetAmbientColor() const;

	void SetPosition(glm::vec4 newPosition);
	void SetDiffuseColor(glm::vec4 color);
	void SetSpecularColor(glm::vec4 color);
	void SetAmbientColor(glm::vec4 color);

    private:
	int id;

	glm::vec4 position;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	glm::vec4 ambientColor;
};

#endif
