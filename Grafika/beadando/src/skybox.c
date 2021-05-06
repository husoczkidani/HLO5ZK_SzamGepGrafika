#include "scene.h"
#include "skybox.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_skybox(Skybox* skybox)
{
    skybox->skybox_right = load_texture("textures/right.png");
    skybox->skybox_left = load_texture("textures/left.png");
    skybox->skybox_top = load_texture("textures/top.png");
    skybox->skybox_back = load_texture("textures/back.png");
    skybox->skybox_front = load_texture("textures/front.png");
}

void kill_skybox()
{
    
}

void draw_skybox(Skybox* skybox)
{


    glBindTexture(GL_TEXTURE_2D, skybox->skybox_right);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex3f(-300.0f, -300.0f, -300.0f); 

        glTexCoord2f(1,0);
        glVertex3f(-300.0f, -300.0f, 300.0f); 

        glTexCoord2f(0,0);
        glVertex3f(300.0f, -300.0f, +300.0f); 

        glTexCoord2f(0,1);
        glVertex3f(300.0f, -300.0f, -300.0f); 
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox->skybox_left);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex3f(300.0f, 300.0f, -300.0f); 

        glTexCoord2f(1,0);
        glVertex3f(300.0f, 300.0f, 300.0f); 

        glTexCoord2f(0,0);
        glVertex3f(-300.0f, 300.0f, +300.0f); 

        glTexCoord2f(0,1);
        glVertex3f(-300.0f, 300.0f, -300.0f); 
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox->skybox_top);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-300.0f, 300.0f, 300.0f); 

        glTexCoord2f(0,1);
        glVertex3f(300.0f, 300.0f, 300.0f); 

        glTexCoord2f(1,1);
        glVertex3f(300.0f, -300.0f, 300.0f); 

        glTexCoord2f(1,0);
        glVertex3f(-300.0f, -300.0f, 300.0f); 
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox->skybox_back);
    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(-300.0f, -300.0f, -300.0f); 

        glTexCoord2f(0,0);
        glVertex3f(-300.0f, -300.0f, 300.0f); 

        glTexCoord2f(1,0);
        glVertex3f(-300.0f, 300.0f, +300.0f); 

        glTexCoord2f(1,1);
        glVertex3f(-300.0f, 300.0f, -300.0f); 
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox->skybox_front);
    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(300.0f, 300.0f, -300.0f); 

        glTexCoord2f(0,0);
        glVertex3f(300.0f, 300.0f, 300.0f); 

        glTexCoord2f(1,0);
        glVertex3f(300.0f, -300.0f, +300.0f); 

        glTexCoord2f(1,1);
        glVertex3f(300.0f, -300.0f, -300.0f); 
    glEnd();
}
