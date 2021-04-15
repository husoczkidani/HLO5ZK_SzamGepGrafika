#include <GL/glut.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "scene.h"
#include "camera.h"
#include "room.h"

void init_models(Scene* scene)
{
	load_model(&(scene->bosschair.model), "models/bosschair.obj");	
	load_model(&(scene->desk.model), "models/desk.obj");
	load_model(&(scene->chair.model), "models/chair.obj");
	load_model(&(scene->sofa.model), "models/sarokulo.obj");
	load_model(&(scene->szekreny.model), "models/szekreny.obj");
	load_model(&(scene->szekreny_2.model), "models/szekreny_2.obj");
	load_model(&(scene->door.model), "models/door.obj");
	load_model(&(scene->flowerpot.model), "models/flowerpot.obj");
	load_model(&(scene->plant.model), "models/plant.obj");
	load_model(&(scene->fan.model), "models/fan.obj");
	load_model(&(scene->fan_holder.model), "models/fan_holder.obj");
	load_model(&(scene->person.model), "models/person.obj");

}

void set_position(Scene* scene)
{
	scene->bosschair.position.x = -8;
	scene->bosschair.position.y = 8;
	scene->bosschair.position.z = -5;

	scene->desk.position.x = -5;
	scene->desk.position.y = 5;
	scene->desk.position.z = -5;

	scene->chair.position.x = -3;
	scene->chair.position.y = 3;
	scene->chair.position.z = -5;

	scene->sofa.position.x = 7;
	scene->sofa.position.y = -5.5;
	scene->sofa.position.z = -5;

	scene->szekreny.position.x = 2;
	scene->szekreny.position.y = 9.5;
	scene->szekreny.position.z = 2;

	scene->szekreny_2.position.x = -5;
	scene->szekreny_2.position.y = -9;
	scene->szekreny_2.position.z = -0.5;

	scene->door.position.x = -10;
	scene->door.position.y = -3;
	scene->door.position.z = -5;

	scene->flowerpot.position.x = 7;
	scene->flowerpot.position.y = 7;
	scene->flowerpot.position.z = -5;

	scene->plant.position.x = 7;
	scene->plant.position.y = 7;
	scene->plant.position.z = -4;

	scene->fan.position.x = 0;
	scene->fan.position.y = 0;
	scene->fan.position.z = 3.5;

	scene->person.position.x = 0;
	scene->person.position.y = 0;
	scene->person.position.z = -5;
}

void init_textures(Scene* scene)
{	
	scene->texture_id[0] = load_texture("Textures/bosschair.jpg"); 		
 	scene->texture_id[1] = load_texture("Textures/chair.jpg"); 	
	scene->texture_id[2] = load_texture("Textures/chair_.jpg"); 	
	scene->texture_id[3] = load_texture("Textures/sofa.jpg"); 	
	scene->texture_id[4] = load_texture("Textures/chair.jpg"); 	
	scene->texture_id[5] = load_texture("Textures/szekreny.jpg"); 	
	scene->texture_id[6] = load_texture("Textures/szekreny.jpg"); 	
	scene->texture_id[7] = load_texture("Textures/szekreny.jpg"); 	
	scene->texture_id[8] = load_texture("Textures/cactus.jpg"); 
	scene->texture_id[9] = load_texture("Textures/szekreny.jpg"); 
	scene->texture_id[10] = load_texture("Textures/snail.jpg"); 
	scene->texture_id[11] = load_texture("Textures/help.jpg"); 
}


void init_scene(Scene* scene)
{
	init_models(scene);
	set_position(scene);
	init_textures(scene);
	scene->light=0.7f;
}

void set_lighting(Scene* scene)
{
	float ambient_light[4];
	float diffuse_light[4];
	float specular_light[4];
	float position[4];

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

	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 10.0f;
	position[3] = 0.0f;

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void draw_scene(Scene* scene)
{
	room_draw(scene, 10.0f);
	glEnable(GL_TEXTURE_2D);
	set_lighting(scene);
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_id[0]);
	glPushMatrix();
	glTranslatef(scene->bosschair.position.x, scene->bosschair.position.y, scene->bosschair.position.z);
	glRotatef(90, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
	glScalef(1.5f, 1.5f, 1.5f);
	draw_model(&(scene->bosschair.model));
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,  scene->texture_id[1]);
	glPushMatrix();
    glTranslatef(scene->desk.position.x,scene->desk.position.y,scene->desk.position.z);
    glRotatef(90, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
	glScalef(0.09f, 0.09f, 0.09f);
    draw_model(&(scene->desk.model));
    glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,  scene->texture_id[2]);
	glPushMatrix();
    glTranslatef(scene->chair.position.x,scene->chair.position.y,scene->chair.position.z);
    glRotatef(90, 1, 0, 0);
	glRotatef(-135, 0, 1, 0);
	glScalef(0.035f, 0.035f, 0.035f);
    draw_model(&(scene->chair.model));
    glPopMatrix();
		
	glBindTexture(GL_TEXTURE_2D, scene->texture_id[3]);
	glPushMatrix();
    glTranslatef(scene->sofa.position.x,scene->sofa.position.y,scene->sofa.position.z);
    glRotatef(90, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.07f, 0.07f, 0.07f);
    draw_model(&(scene->sofa.model));
    glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,  scene->texture_id[4]);
	glPushMatrix();
    glTranslatef(scene->szekreny.position.x,scene->szekreny.position.y,scene->szekreny.position.z);
    glRotatef(90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.004f, 0.004f, 0.004f);
    draw_model(&(scene->szekreny.model));
    glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,  scene->texture_id[5]);
	glPushMatrix();
    glTranslatef(scene->szekreny_2.position.x,scene->szekreny_2.position.y,scene->szekreny_2.position.z);
    glRotatef(-90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glScalef(2.0f, 5.0f, 5.0f);
    draw_model(&(scene->szekreny_2.model));
    glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_id[6]);
	glPushMatrix();
    glTranslatef(scene->door.position.x,scene->door.position.y,scene->door.position.z);
    glRotatef(-90, 0, 0, 1);
	glScalef(0.04f, 0.04f, 0.035f);
    draw_model(&(scene->door.model));
    glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,  scene->texture_id[7]);
	glPushMatrix();
    glTranslatef(scene->flowerpot.position.x,scene->flowerpot.position.y,scene->flowerpot.position.z);
    glRotatef(90, 1, 0, 0);
	glScalef(0.2f, 0.2f, 0.2f);
    draw_model(&(scene->flowerpot.model));
    glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,  scene->texture_id[8]);
	glPushMatrix();
    glTranslatef(scene->plant.position.x,scene->plant.position.y,scene->plant.position.z);
	glRotatef(90, 0, 0, 1);
	glScalef(0.02f, 0.02f, 0.02f);
    draw_model(&(scene->plant.model));
    glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,  scene->texture_id[9]);
	glPushMatrix();
    glTranslatef(scene->fan.position.x,scene->fan.position.y,scene->fan.position.z);
	glRotatef(90, 1, 0, 0);
	glScalef(0.2f, 0.2f, 0.2f);
	draw_model(&(scene->fan_holder.model));
	glRotatef(scene->fan.rotation.z, 0, 1, 0);
    draw_model(&(scene->fan.model));
    glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,  scene->texture_id[10]);
	glPushMatrix();
    glTranslatef(scene->person.position.x,scene->person.position.y,scene->person.position.z);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(scene->person.rotation.z, 0, 1, 0);
	glScalef(0.2f, 0.2f, 0.2f);
    draw_model(&(scene->person.model));
    glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
}