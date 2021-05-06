#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "camera.h"
#include "scene.h"
#include "help.h"

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

void specialFunc(int key, int x, int y);

void update_camera_position(struct Camera* camera, double elapsed_time);

/**
 * Call when there is no other event.
 */
void idle();

double calc_elapsed_time();

void can_move(struct Camera* camera);

#endif /* CALLBACKS_H */
