#include "horse.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>

#include <obj/load.h>
#include <obj/draw.h>

#include <stdio.h>
#define sensitivity 3

void init_horse(Horse* horse)
{
    horse->texture = load_texture("textures/horse.jpg");
    load_model(&(horse->model), "models/horse.obj");

    horse->position.x = -100;
    horse->position.y = -100;
    horse->position.z = 0;

    horse->pose.x = 0;
	horse->pose.y = 0;
	horse->pose.z = 45;

    is_player_on_the_horse == FALSE;
}
void draw_horse( Horse* horse)
{
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, horse->texture);
    glTranslatef(horse->position.x,horse->position.z,horse->position.y);
    glRotatef(-(horse->pose.z), 0, 1.0, 0);
    draw_model(&(horse->model));

    glPopMatrix();
}
void rotate_horse(Horse* horse, double horizontal)
{
	// Horizontal
	horse->pose.z += horizontal/sensitivity;

	if (horse->pose.z < 0)
	{
		horse->pose.z -= 360.0;
	}

	if (horse->pose.z > 360.0)
	{
		horse->pose.z += 360.0;
	}

}
void move_horse_forward(Horse* horse, double distance)
{
	horse->prev_position = horse->position;
	double angle = degree_to_radian(horse->pose.z+90);

	horse->position.x -= cos(angle) * distance;
	horse->position.y -= sin(angle) * distance;
}
void move_horse_backward(Horse* horse, double distance)
{
	horse->prev_position = horse->position;
	double angle = degree_to_radian(horse->pose.z+90);

	horse->position.x += cos(angle) * distance;
	horse->position.y += sin(angle) * distance;
}