#ifndef _MESH_HEADER__
#define _MESH_HEADER__

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

class Mesh
{
    public:
	Mesh();
	~Mesh();

	std::vector<glm::vec3> GetVerts() const;
	std::vector<glm::vec3> GetNormals() const;
	std::vector<glm::vec2> GetTexCoords() const;
	std::vector<glm::vec3> GetFaces() const;

	void UpdateVerts(const std::vector<glm::vec3>& newVerts);
	void UpdateNormals(const std::vector<glm::vec3>& newNormals);
	void UpdateTexCoords(const std::vector<glm::vec2>& newTexCoords);
	void UpdateFaces(const std::vector<glm::vec3>& newFaces);

	void UpdateBuffers();

	void Render();
    private:
	GLuint vertexBuffer;
	GLuint normalBuffer;
	GLuint texCoordBuffer;

	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> faces;

};

#endif

