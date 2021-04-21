#include "help.h"
#include "scene.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_help(struct Scene* scene)
{
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[3]);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-2, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(2, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(2, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-2, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
}