#include "ModelLoader.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace ModelLoader {

Mesh loadMesh(std::ifstream& obj)
{
    Mesh mesh;
    std::vector<glm::vec3> tempVerts;
    std::vector<glm::vec3> tempNormals;
    std::vector<glm::vec2> tempTexCoords;

    std::vector<glm::vec3> verts;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;

    std::string line;
    std::string dataType;

    while (std::getline(obj, line))
    {
        std::istringstream iss(line);
        iss >> dataType;
	if (dataType.compare("v") == 0)
	{
	    glm::vec3 vert;
	    iss >> vert.x >> vert.y >> vert.z;
	    tempVerts.push_back(vert);
	}
	else if (dataType.compare("vt") == 0)
	{
	    glm::vec2 texCoord;
	    iss >> texCoord.x >> texCoord.y;
	    tempTexCoords.push_back(texCoord);
	}
	else if (dataType.compare("vn") == 0)
	{
	    glm::vec3 normal;
	    iss >> normal.x >> normal.y >> normal.z;
	    tempNormals.push_back(normal);
	}
	else if (dataType.compare("f") == 0)
	{
	    int vertIndex[3];
	    int texIndex[3];
	    int normalIndex[3];
	    char bar;

	    for (int i = 0; i < 3; i++)
	    {
		iss >> vertIndex[i] >> bar >> texIndex[i] >> bar >> normalIndex[i];
		verts.push_back(tempVerts[vertIndex[i] - 1]);
		texCoords.push_back(tempTexCoords[texIndex[i] -1]);
		normals.push_back(tempNormals[normalIndex[i] - 1]);
	    }

	}
    }

    mesh.UpdateVerts(verts);
    mesh.UpdateNormals(normals);
    mesh.UpdateTexCoords(texCoords);

    return mesh;

}

std::vector<Mesh> LoadMeshesFromOBJ(const char* filename)
{
    std::vector<Mesh> meshes;

    std::ifstream obj {filename};

    std::string mtlFile;

    std::string line;
    while (std::getline(obj, line)) 
    {
	std::istringstream iss(line);
	std::string data;

	iss >> data;
	if (data.compare("#") == 0)
	{
	    continue;
	}
	else if (data.compare("mtl") == 0)
	{
	    mtlFile = data;
	}
	else if (data.compare("o") == 0)
	{
	    meshes.push_back(loadMesh(obj));
	}

	std::cout << line << std::endl;
    }

    obj.close();

    return meshes;
}

}
