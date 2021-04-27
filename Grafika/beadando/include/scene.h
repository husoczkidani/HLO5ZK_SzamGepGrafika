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

// Non movable objects
typedef struct StaticObject
{
    Model model;
    vec3 position;
    float rotation;
} StaticObject;

typedef struct Scene
{
    GLuint staticobject_display_list_id[4];

    StaticObject hills;
    StaticObject cottage;
    StaticObject campfire;
    StaticObject aloe[20];
    StaticObject cactus1[40];
    StaticObject cactus2[60];
    StaticObject cactus3[40];
    Material material;
    GLuint texture_id[10];
    float light;
} Scene;


/**
 * Initialize the scene
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Load models
 */ 
void init_models(Scene* scene);

/**
 * Load textures
 */
void init_textures(Scene* scene);

/**
 * Create Display Lists
 */
void init_lists(Scene* scene);

/**
 * Make and draw the ground
 */
void draw_ground(Scene* scene);

/**
 * Make and draw the sky
 */
void draw_sky(Scene* scene);

/**
 * Draw the cactuses
 */
void draw_cactus(Scene* scene);

/**
 * Set the objects position
 */
void set_position(Scene* scene);

/**
 * Set the object rotation
 */
void set_rotation(Scene* scene);

#endif /* SCENE_H */
