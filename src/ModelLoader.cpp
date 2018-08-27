#include "ModelLoader.hpp"

#include "Material.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace ModelLoader {

Material* loadMTL(const std::string& filename, const std::string materialName)
{
    auto name = std::string("models/") + filename;
    std::cout << "Opening " << name << std::endl;
    std::ifstream mtl{name};
    std::string line;
    std::string dataType;
    std::istringstream iss;

    Material* mat = new Material();
    while(std::getline(mtl, line))
    {
	iss.str(line);
	iss.clear();
	iss >> dataType;
	if (dataType.compare("newmtl") == 0)
	{
	    iss >> dataType;
	    if (dataType.compare(materialName) == 0)
	    {
		std::cout << "Material " << dataType << " found." << std::endl;
		break;
	    }
	}
    }

    std::cout << "Loading shininess..." << std::endl;
    std::getline(mtl, line);
    iss.str(line);
    iss >> dataType;
    float ns;
    iss >> ns;
    mat->SetShininess(ns/1000.0);
    iss.clear();

    std::cout << "Loading shininess..." << std::endl;
    std::getline(mtl, line);
    iss.str(line);
    iss >> dataType;
    glm::vec3 ambientColor;
    iss >> ambientColor.r >> ambientColor.g >> ambientColor.b;
    mat->SetAmbientColor(glm::vec4(ambientColor, 1.0));
    iss.clear();

    std::cout << "Loading diffuse..." << std::endl;
    std::getline(mtl, line);
    iss.str(line);
    iss >> dataType;
    glm::vec3 diffuseColor;
    iss >> diffuseColor.r >> diffuseColor.g >> diffuseColor.b;
    mat->SetDiffuseColor(glm::vec4(diffuseColor, 1.0));
    iss.clear();
    
    std::cout << "Loading specular..." << std::endl;
    std::getline(mtl, line);
    iss.str(line);
    iss >> dataType;
    glm::vec3 specularColor;
    iss >> specularColor.r >> specularColor.g >> specularColor.b;
    mat->SetSpecularColor(glm::vec4(specularColor, 1.0));
    iss.clear();
    
    std::cout << "Loading emission..." << std::endl;
    std::getline(mtl, line);
    iss.str(line);
    iss >> dataType;
    glm::vec3 emissionColor;
    iss >> emissionColor.r >> emissionColor.g >> emissionColor.b;
    mat->SetEmissionColor(glm::vec4(emissionColor, 1.0));
    iss.clear();

    std::cout << "Finished loading material" << std::endl;
    return mat;
}

Mesh* loadMesh(std::ifstream& obj, const std::string& mtlFilename)
{
    Mesh* mesh = new Mesh();
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
	else if (dataType.compare("usemtl") == 0)
	{
	    std::string materialName;
	    iss >> materialName;
	    std::cout << "Loading material: " << materialName << std::endl;
	    Material* mat = loadMTL(mtlFilename, materialName);
	    mesh->UpdateMaterial(*(mat));
	    delete mat;
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
		verts.push_back(tempVerts[vertIndex[i] -1 ]);
		texCoords.push_back(tempTexCoords[texIndex[i] - 1]);
		normals.push_back(tempNormals[normalIndex[i] - 1]);
	    }
	}
    }

    mesh->UpdateVerts(verts);
    mesh->UpdateNormals(normals);
    mesh->UpdateTexCoords(texCoords);

    std::cout << "Mesh constructed" << std::endl;
    return mesh;
}

Mesh* LoadMeshFromOBJ(const char* filename)
{
    Mesh* mesh;

    std::ifstream obj {filename};

    std::string mtlFilename;

    std::string line;
    while (std::getline(obj, line)) 
    {
	std::istringstream iss(line);
	std::string data;

	iss >> data;
	if (data.compare("mtllib") == 0)
	{
	    iss >> mtlFilename; 
	    std::cout << "MTL lib name: " << mtlFilename << std::endl;
	}
	else if (data.compare("o") == 0)
	{
	    std::cout << "Loading mesh..." << std::endl;
	    mesh = loadMesh(obj, mtlFilename);
	}
    }

    obj.close();

    return mesh;
}

}
