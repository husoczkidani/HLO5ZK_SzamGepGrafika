#ifndef SKYBOX_H
#define SKYBOX_H

#include "utils.h"
#include "camera.h"

#include <obj/model.h>

/**
 * Skybox
 */
typedef struct Skybox
{
    GLuint skybox_right;
    GLuint skybox_left;
    GLuint skybox_top;
    GLuint skybox_bottom;
    GLuint skybox_back;
    GLuint skybox_front;
} Skybox;

int day_loaded;
int night_loaded;

/**
 * Initialize the skybox.
 */
void init_skybox(Skybox* skybox);

/**
 * Draw the skybox.
 */
void draw_skybox(Skybox* skybox);

/**
 * Kills the skybox.
 */
void kill_skybox();

void load_daybox(Skybox* skybox);

void load_nightbox(Skybox* skybox);
#endif /* SKYBOX_H */