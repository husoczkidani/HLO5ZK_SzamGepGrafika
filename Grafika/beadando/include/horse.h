#ifndef HORSE_H
#define HORSE_H

#include "utils.h"

#include <obj/model.h>
#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Horse
 */
typedef struct Horse
{
	Model model;
	GLuint texture;
    vec3 position;
    vec3 prev_position;
    vec3 pose;
} Horse;

int is_player_on_the_horse;

/**
 * Initialize the horse
 */
void init_horse(Horse *horse);

/**
 * Draw the horse
 */
void draw_horse( Horse *horse);

/**
 * Sets the rotation of the horse
 */
void rotate_horse(Horse* horse, double horizontal);

/**
 * Moves the horse forward
 */
void move_horse_forward(Horse* horse, double distance);

/**
 * Moves the horse backwards
 */
void move_horse_backward(Horse* horse, double distance);

#endif /* HORSE_H */