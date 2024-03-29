#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "camera.h"
#include "scene.h"
#include "help.h"
#include "horse.h"

#include <GL/glut.h>

/**
 * Scene
 */
struct Scene scene;

/**
 * Camera
 */
struct Camera camera;


struct Action
{
	int jump;
	int sprint;
	int walk;
	int move_forward;
	int move_backward;
	int step_left;
	int step_right;
	int move_up;
	int move_down;
	int increase_light;
	int decrease_light;
	int get_on_the_horse;
	
};
struct Action action;

/**
 * Call when need to display the graphical content.
 */
void display();

/**
 * Call after windows resizing.
 */
void reshape(GLsizei width, GLsizei height);

/**
 * Call after mouse button event.
 */
void mouse(int button, int state, int x, int y);

/**
 * Call after mouse event.
 */
void motion(int x, int y);

/**
 * Call after keyboard event.
 */
void keyboard(unsigned char key, int x, int y);

/**
 * Call after keyboard release event.
 */
void keyboard_up(unsigned char key, int x, int y);

/**
 * Call after special key was pressed down
 */
void specialFunc(int key, int x, int y);

/**
 * Updates the positions after the pressed key
 */
void update_camera_position(struct Camera* camera, double elapsed_time);

/**
 * Call when there is no other event.
 */
void idle();

/**
 * Calculates elapsed time after an event
 */
double calc_elapsed_time();

/**
 * Bounding box for camera
 */
void can_move(struct Camera* camera);

/**
 * Checks if the player is close enough to the horse, sets the right angle and position 
 */
void get_on_the_horse(struct Camera* camera);

/**
 * Bounding box for horse
 */
void can_horse_move(struct Horse* horse);

#endif /* CALLBACKS_H */
