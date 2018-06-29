#include <algorithm>
#include <iostream>

#include "Mesh.hpp"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

std::vector<glm::vec3> Mesh::GetVerts() const
{
    return verts;
}

std::vector<glm::vec3> Mesh::GetNormals() const
{
    return normals;
}

std::vector<glm::vec2> Mesh::GetTexCoords() const
{
    return texCoords;
}

std::vector<glm::vec3> Mesh::GetFaces() const
{
    return faces;
}

void Mesh::UpdateVerts(const std::vector<glm::vec3>& newVerts)
{
    verts = newVerts;
}

void Mesh::UpdateNormals(const std::vector<glm::vec3>& newNormals)
{
    normals = newNormals;
}

void Mesh::UpdateTexCoords(const std::vector<glm::vec2>& newTexCoords)
{
    texCoords = newTexCoords;
}

void Mesh::UpdateFaces(const std::vector<glm::vec3>& newFaces)
{
    faces = newFaces;
}

void Mesh::UpdateBuffers()
{
    if (!glIsBuffer(vertexBuffer))
	glGenBuffers(3, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3), verts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);
}

void Mesh::Render()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glNormalPointer(GL_FLOAT, 0, 0);
    glEnableClientState(GL_NORMAL_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glDrawArrays(GL_TRIANGLES, 0, verts.size());
}

