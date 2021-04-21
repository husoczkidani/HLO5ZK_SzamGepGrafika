#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_scene(Scene* scene)
{
    init_models(scene);
    init_textures(scene);
    set_position(scene);
    scene->light = 0.5f;

    
    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
}
void init_models(Scene* scene)
{
     load_model(&(scene->hills), "models/hill.obj");
     int i;
     for(i = 0; i<20;i++)
     {
         load_model(&(scene->cactus1[i]), "models/cactus01.obj");
     }
     for(i = 0; i<20;i++)
     {
         load_model(&(scene->cactus2[i]), "models/cactus02.obj");
     }
     for(i = 0; i<20;i++)
     {
         load_model(&(scene->cactus3[i]), "models/cactus03.obj");
     }
}
void init_textures(Scene* scene)
{
    scene->texture_id[0] = load_texture("textures/polydesert_atlas.png"); 
    scene->texture_id[1] = load_texture("textures/floor.png");
    scene->texture_id[2] = load_texture("textures/ceiling.png");
    scene->texture_id[3] = load_texture("textures/guide.png");

}
void set_lighting(Scene* scene)
{
    float ambient_light[4];
	float diffuse_light[4];
	float specular_light[4];

	ambient_light[0] = scene->light;
	ambient_light[1] = scene->light;
	ambient_light[2] = scene->light;
	ambient_light[3] = 1.0f;

	diffuse_light[0] = scene->light;
	diffuse_light[1] = scene->light;
	diffuse_light[2] = scene->light;
	diffuse_light[3] = 1.0f;

	specular_light[0] = scene->light;
	specular_light[1] = scene->light;
	specular_light[2] = scene->light;
	specular_light[3] = 1.0f;

    float position[] = { 0.0f, 0.0f, 50.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void set_position(Scene* scene)
{
    int xy[2];
    int i,j;
    for(i = 0; i<20;i++)
    {
        for( j = 0; j<2; j++)
        {
            xy[j] = rand() % (81 - (-80)) -80;
        }
        scene->cactus1[i].position.x = xy[0];
        scene->cactus1[i].position.y = xy[1];
    }
    srand(time(NULL));
    for(i = 0; i<20;i++)
    {
        for( j = 0; j<2; j++)
        {
            xy[j] = rand() % (81 - (-80)) -80;
        }
        scene->cactus2[i].position.x = xy[0];
        scene->cactus2[i].position.y = xy[1];
    }
    for(i = 0; i<20;i++)
    {
        for( j = 0; j<2; j++)
        {
            xy[j] = rand() % (81 - (-80)) -80;
        }
        scene->cactus3[i].position.x = xy[0];
        scene->cactus3[i].position.y = xy[1];
    }

}
void draw_scene(const Scene* scene)
{
    glEnable(GL_TEXTURE_2D);
    set_material(&(scene->material));
    set_lighting(scene);
    glRotatef(90,1,0,0);

    draw_sky(scene);
    draw_ground(scene);
    draw_cactus(scene);
    

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[0]);
    draw_model(&(scene->hills));
    glPopMatrix();

    
    glDisable(GL_TEXTURE_2D);
}
void draw_sky(Scene* scene)
{
    float m, w;
    m = 50;
    w = 2000;
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[2]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(w, m, w);
	glTexCoord2f(1, 0);
	glVertex3f(w, m, -w);
	glTexCoord2f(0, 0);
	glVertex3f(-w, m, -w);
	glTexCoord2f(0, 1);
	glVertex3f(-w, m, w);
	glEnd();
    glPopMatrix();
}
void draw_ground(Scene* scene)
{
	glBindTexture(GL_TEXTURE_2D, scene->texture_id[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	int x, z,y;
	for (x = -210; x < 210; x += 3)
	{
		for (z = -210; z <210; z += 3)
		{
            y=0;
            glTexCoord2f(0.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, y, z);
			glTexCoord2f(1.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 3, y, z);
			glTexCoord2f(1.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 3, y, z + 3);
			glTexCoord2f(0.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, y, z + 3);   

			
		}
	}
	glEnd();
}
void draw_cactus(Scene* scene)
{   
    int i;
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[0]);
    for (i=0;i<20;i++)
    {
        glPushMatrix();
        glTranslatef(scene->cactus1[i].position.x,0,scene->cactus1[i].position.y);
        draw_model(&(scene->cactus1[i]));
        glPopMatrix();
    }
    
    for (i=0;i<20;i++)
    {
        glPushMatrix();
        glTranslatef(scene->cactus2[i].position.x,0,scene->cactus2[i].position.y);
        draw_model(&(scene->cactus2[i]));
        glPopMatrix();
    }
    for (i=0;i<20;i++)
    {
        glPushMatrix();
        glTranslatef(scene->cactus3[i].position.x,0,scene->cactus3[i].position.y);
        draw_model(&(scene->cactus3[i]));
        glPopMatrix();
    }
    
}
