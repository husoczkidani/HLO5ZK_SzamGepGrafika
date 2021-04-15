#include "texture.h"
#include <SOIL/SOIL.h>
#include <GL/glut.h>
#include "room.h"

void init_room()
{
    roombox[ROOM_LEFT] = load_texture("Textures/wall.jpg");
    roombox[ROOM_BACK] = load_texture("Textures/wall.jpg");
    roombox[ROOM_RIGHT] = load_texture("Textures/wall.jpg");
    roombox[ROOM_FRONT] = load_texture("Textures/wall.jpg");
    roombox[ROOM_TOP] = load_texture("Textures/plafon.jpg");
    roombox[ROOM_BOTTOM] = load_texture("Textures/floor.jpg");
}

void room_draw(struct Scene* scene, double size)
{
    /*turn off lighting, when making the roombox
    turn off depth texting
    and turn on texturing*/
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(scene->light, scene->light, scene->light);

    /*use the texture we want and draw it
    top face*/
    glBindTexture(GL_TEXTURE_2D, roombox[ROOM_TOP]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);                     /*use the correct texture coordinate*/
    glVertex3f(size , size , size / 2);   /*and a vertex*/
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-size , size , size / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-size , -size, size / 2);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(size , -size , size / 2);
    glEnd();
    /*right face*/
    glBindTexture(GL_TEXTURE_2D, roombox[ROOM_RIGHT]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-size , size, size / 2);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-size , size , -size / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-size , -size , -size / 2);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size , -size , size / 2);
    glEnd();
    /*bottom face*/
    glBindTexture(GL_TEXTURE_2D, roombox[ROOM_BOTTOM]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(size , size , -size / 2);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-size , size , -size / 2);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size , -size , -size / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(size , -size , -size / 2);
    glEnd();
    /*left face*/
    glBindTexture(GL_TEXTURE_2D, roombox[ROOM_LEFT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(size , size , -size / 2);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(size , size , size / 2);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(size , -size , size / 2);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(size , -size , -size / 2);
    glEnd();
    /*front face*/
    glBindTexture(GL_TEXTURE_2D, roombox[ROOM_FRONT]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(size , size , size / 2);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size , size , size / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-size , size , -size / 2);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(size , size , -size / 2);
    glEnd();
    /*back face*/
    glBindTexture(GL_TEXTURE_2D, roombox[ROOM_BACK]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(size , -size , size / 2);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-size , -size , size / 2);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-size , -size , -size / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(size , -size, -size / 2);
    glEnd();

    /*turn back what has been disabled*/
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
}
