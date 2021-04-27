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
    init_lists(scene);
    init_textures(scene);
    set_position(scene);
    set_rotation(scene);
    scene->light = 0.5f;

    
    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 0.7;
    scene->material.diffuse.green = 0.7;
    scene->material.diffuse.blue = 0.7;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
}
void init_models(Scene* scene)
{
    load_model(&(scene->hills), "models/hills.obj");
    load_model(&(scene->cottage), "models/cottages.obj");
    load_model(&(scene->campfire), "models/campfire.obj");
    load_model(&(scene->cactus1[0]), "models/cactus01.obj");
    load_model(&(scene->cactus2[0]), "models/cactus02.obj");
    load_model(&(scene->cactus3[0]), "models/cactus03.obj");

}
void init_lists(Scene* scene)
{
    scene->staticobject_display_list_id[0] = glGenLists(1);
    glNewList(scene->staticobject_display_list_id[0],GL_COMPILE);
    draw_model(&(scene->cactus1[0]));
    glEndList();

    scene->staticobject_display_list_id[1] = glGenLists(1);
    glNewList(scene->staticobject_display_list_id[1],GL_COMPILE);
    draw_model(&(scene->cactus2[0]));
    glEndList();

    scene->staticobject_display_list_id[2] = glGenLists(1);
    glNewList(scene->staticobject_display_list_id[2],GL_COMPILE);
    draw_model(&(scene->cactus3[0]));
    glEndList();
}
void init_textures(Scene* scene)
{
    scene->texture_id[0] = load_texture("textures/polydesert_atlas.png"); 
    scene->texture_id[1] = load_texture("textures/floor.png");
    scene->texture_id[2] = load_texture("textures/ceiling.png");
    scene->texture_id[3] = load_texture("textures/guide.png");
    scene->texture_id[4] = load_texture("textures/fa.png");
    scene->texture_id[5] = load_texture("textures/campfire.png");


}
void set_lighting(Scene* scene)
{
    float ambient_light[4];
	float diffuse_light[4];
	float specular_light[4];

	ambient_light[0] = scene->light;
	ambient_light[1] = scene->light;
	ambient_light[2] = scene->light-0.05;
	ambient_light[3] = 1.0f;

	diffuse_light[0] = scene->light;
	diffuse_light[1] = scene->light;
	diffuse_light[2] = scene->light-0.05;
	diffuse_light[3] = 1.0f;

	specular_light[0] = scene->light;
	specular_light[1] = scene->light;
	specular_light[2] = scene->light-0.05;
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

void set_rotation(Scene* scene)
{
    int rotationz;
    int i;

    srand(time(NULL));
    for(i = 0; i<40;i++)
    {
        rotationz = rand() % (1 - 180) + 180;
        scene->cactus1[i].rotation = rotationz;
    }
    for(i = 0; i<60;i++)
    {
        rotationz = rand() % (1 - 180) + 180;
        scene->cactus2[i].rotation = rotationz;
    }
    for(i = 0; i<40;i++)
    {
        rotationz = rand() % (1 - 180) + 180;
        scene->cactus3[i].rotation = rotationz;
    }

}
void set_position(Scene* scene)
{
    int xy[2];
    int i,j;

    srand(time(NULL));
    for(i = 0; i<40;i++)
    {
        for( j = 0; j<2; j++)
        {
            xy[j] = rand() % (106 - (-105)) -105;
        }
        scene->cactus1[i].position.x = xy[0];
        scene->cactus1[i].position.y = xy[1];
    }
    for(i = 0; i<60;i++)
    {
        for( j = 0; j<2; j++)
        {
            xy[j] = rand() % (106 - (-105)) -105;
        }
        scene->cactus2[i].position.x = xy[0];
        scene->cactus2[i].position.y = xy[1];
    }
    for(i = 0; i<40;i++)
    {
        for( j = 0; j<2; j++)
        {
            xy[j] = rand() % (106 - (-105)) -105;
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

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[4]);
    draw_model(&(scene->cottage));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[5]);
    draw_model(&(scene->campfire));
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
    for (i=0;i<40;i++)
    {
        glPushMatrix();
        glTranslatef(scene->cactus1[i].position.x,0,scene->cactus1[i].position.y);
        glRotatef(scene->cactus1[i].rotation,0,1,0);
        glCallList(scene->staticobject_display_list_id[0]);
        glPopMatrix();
    }
    
    for (i=0;i<60;i++)
    {
        glPushMatrix();
        glTranslatef(scene->cactus2[i].position.x,0,scene->cactus2[i].position.y);
        glRotatef(scene->cactus2[i].rotation,0,1,0);
        glCallList(scene->staticobject_display_list_id[1]);
        glPopMatrix();
    }
    for (i=0;i<40;i++)
    {
        glPushMatrix();
        glTranslatef(scene->cactus3[i].position.x,0,scene->cactus3[i].position.y);
        glRotatef(scene->cactus3[i].rotation,0,1,0);
        glCallList(scene->staticobject_display_list_id[2]);
        glPopMatrix();
    }
    
}
