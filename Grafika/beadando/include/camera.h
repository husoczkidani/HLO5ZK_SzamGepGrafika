#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "scene.h"

#define CAMERA_SPEED 3.0
/**
 * Camera, as a moving point with direction
 */
typedef struct Camera
{
    vec3 position;
    vec3 prev_position;
    vec3 pose;
} Camera;

/**
 * Is the texture preview visible?
 */
int is_help_visible;

/**
 * Initialize the camera to the start position.
 */
void init_camera(Camera* camera);

/**
 * Update the position of the camera.
 */

/**
 * Apply the camera settings to the view transformation.
 */
void set_view(const Camera* camera);

/**
 * Set the horizontal and vertical rotation of the view angle.
 */
void rotate_camera(Camera* camera, double horizontal, double vertical);

/**
 * Resets the vertical pose of the camera.
 */
void set_clear_camera_pose(struct Camera* camera);

/**
 * Move the camera forward.
 */
void move_camera_forward(struct Camera* camera, double distance);

/**
 * Move the camera backward.
 */
void move_camera_backward(struct Camera* camera, double distance);

/**
 * Step the camera left.
 */
void step_camera_left(struct Camera* camera, double distance);

/**
 * Step the camera right.
 */
void step_camera_right(struct Camera* camera, double distance);

/**
 * Move the camera up.
 */
void move_camera_up(struct Camera* camera, double distance);

/**
 * Move the camera down.
 */
void move_camera_down(struct Camera* camera, double distance);

/**
 * Move the camera up and down, simulates jump
 */ 
void camera_jump(Camera* camera, double speed);

#endif /* CAMERA_H */
