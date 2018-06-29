#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Mesh.hpp"
#include "Camera.hpp"

void draw();
void reshape(int width, int height);

std::vector<glm::vec3> verts {
    glm::vec3( 0.5f, -0.5f, 2.0f),
    glm::vec3(-0.5f, -0.5f, 2.0f),
    glm::vec3( 0.0f,  0.5f, 2.0f)
};

std::vector<glm::vec3> colors {
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(0.0, 1.0, 0.0),
    glm::vec3(0.0, 0.0, 1.0),
};

Mesh* mesh;

Camera camera;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Cena 3D");

    glewInit();

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);

    mesh = new Mesh();
    mesh->UpdateVerts(verts);
    mesh->UpdateNormals(colors);
    //mesh->UpdateBuffers();

    camera.SetPosition(glm::vec3(0.0, 0.0, -5.0));

    glClearColor(.1, .1, .1, 1);
    
    //LIGHTNING AND MATERIAL
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat lightPosition[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat whiteLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lmodel_ambient[] = {.1, .1, .1, 1.0};
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    
    return 0;
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.Apply();

    //mesh->Render();
    
    glutSolidSphere(1, 50, 50);

    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    camera.SetAspectRatio(width/(float) height);
}

