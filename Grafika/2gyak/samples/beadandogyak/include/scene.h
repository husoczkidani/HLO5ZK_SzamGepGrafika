#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Object
{
	Model model;
	vec3 position;
	vec3 speed;
	vec3 rotation;
	vec3 prev_position;
} Object;

typedef struct Scene
{
    Object hills;
    Object rock1;
    Object rock2;
    Object rock3;
    Object aloe;
    Object cactus1;
    Object bush1;
    Material material;
    GLuint texture_id[5];
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

void init_models(Scene* scene);

void init_textures(Scene* scene);

void draw_ground(Scene* scene);
#endif /* SCENE_H */
