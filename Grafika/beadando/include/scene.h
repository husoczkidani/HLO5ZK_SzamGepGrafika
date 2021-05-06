#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

//for the future(movable objects)
typedef struct Object
{
	Model model;
	vec3 position;
	vec3 speed;
	vec3 rotation;
	vec3 prev_position;
} Object;

typedef struct Cactuses
{
    vec3 position;
    float rotation;
} Cactuses;

typedef struct Scene
{
    GLuint staticobject_display_list_id[4];
    GLuint texture_id[10];
    Model models[10];

    Model hills;
    Model cottage;
    Model campfire;
    Model cactus1_model;
    Model cactus2_model;
    Model cactus3_model;

    Object eagle;

    Cactuses cactus1[40];
    Cactuses cactus2[70];
    Cactuses cactus3[40];

    vec3 positions[150];

    Material material;
    
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

double calc_elapsed_scenetime();

#endif /* SCENE_H */
