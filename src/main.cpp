#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>
#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ModelLoader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Light.hpp"

void draw();
void reshape(int width, int height);

std::vector<std::string> objetos {
    "models/chao.obj",         
    "models/sofa.obj",
    "models/mesa.obj",
    "models/escultura_base.obj",
    "models/escultura.obj", 
    "models/icoesfera.obj",
    "models/tv_mesa.obj",
    "models/tv.obj",
    "models/tv_tela.obj"
};

std::vector<Mesh*> meshes;

Camera camera;
Light light0 {0};
Light light1 {1};

float rotation = 0;
float rotationStep = 1;

void initializeMeshes()
{
    for (auto obj : objetos)
    {
	Mesh* mesh = ModelLoader::LoadMeshFromOBJ(obj.c_str());
	mesh->UpdateBuffers();
	meshes.push_back(mesh);
    }
}

void InitializeLights()
{
    light0.SetPosition(glm::vec4(0.0, 10.0, 0.0, 1.0));
    light0.SetDiffuseColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
    light0.SetAmbientColor(glm::vec4(.01, .01, .01, 1.0));
    light0.SetSpecularColor(glm::vec4(1, 1, 1, 1.0));
    light0.SetQuadraticAttenuation(.03);

    light1.SetPosition(glm::vec4(0.0, 0.0, 10.0, 1.0));
    light1.SetDiffuseColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
    light1.SetAmbientColor(glm::vec4(.2, .2, .2, 1.0));
    light1.SetSpecularColor(glm::vec4(1, 1, 1, 1.0));
    light1.SetQuadraticAttenuation(.02);

    float lmodel_ambient[] = {0.1, 0.1, 0.1, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glShadeModel(GL_SMOOTH);

    light0.TurnOn();
    light1.TurnOn();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Cena 3D");

    glewInit();

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);

    initializeMeshes();
    InitializeLights();

    camera.SetPosition(glm::vec3(0.0, 7.0, -15.0));
    camera.SetCenter(glm::vec3(0.0));

    glClearColor(.1, .1, .1, 1);
    
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glutMainLoop();
    
    return 0;
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    light0.Apply();
    light1.Apply();

    glPushMatrix();
	glRotatef(rotation, 0.0, 1.0, 0.0);
        rotation += rotationStep;

        for (auto it = meshes.begin(); it != meshes.end(); it++)
        {
	    (*it)->Render();
        }
    glPopMatrix();

    camera.Apply();

    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    camera.SetAspectRatio(width/(float) height);
}

