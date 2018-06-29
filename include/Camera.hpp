#ifndef _CAMERA_HEADER__
#define _CAMERA_HEADER__

#include <glm/vec3.hpp>

class Camera
{
    public:
	Camera();

	void Apply();

	glm::vec3 GetPosition() const;
	float GetFovy() const;
	float GetAspectRatio() const;

	void SetPosition(glm::vec3 newPos);
	void Translate(glm::vec3 amount);
	void SetFovy(float newFovy);
	void SetAspectRatio(float newAspectRatio);

    private:
	glm::vec3 position;
	glm::vec3 up;

	float fovy;
	float aspectRatio;
	float zNear;
	float zFar;
};

#endif
