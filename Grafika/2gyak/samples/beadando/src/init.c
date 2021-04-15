
#include <GL/glut.h>

#include "callbacks.h"
#include "init.h"

GLfloat light_position[] = {5000, 5000, 2500, 1000};
GLfloat light_ambient[] = {0.6, 0.6, 0.5, 0.6};
GLfloat light_diffuse[] = {0.6, 0.6, 0.6, 0.6};
GLfloat light_specular[] = {0.0, 0.0, 0.0, 0.0};

void init()
{
    set_callbacks();

    init_camera(&camera);
    init_entities(&world);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);

    glEnable(GL_LIGHT1);
}
