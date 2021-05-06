#include "camera.h"
#include "scene.h"
#include "callbacks.h"

#include <GL/glut.h>

#include <math.h>
#define size 110
#define sensitivity 3


void init_camera(Camera* camera)
{
    camera->position.x = -103.0;
    camera->position.y = 108.0;
    camera->position.z = 1;
    
    camera->pose.x = 90;
	camera->pose.y = 0;
	camera->pose.z = -135;

    is_help_visible = TRUE;
}

void set_view(const Camera* camera)
{
    glRotatef(-(camera->pose.x), 1.0, 0, 0);
	glRotatef(-(camera->pose.z), 0, 0, 1.0);
	glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    double fallbackPoseOfX;

	// Vertical, with rollover protection
	if (camera->pose.x >= 0 && camera->pose.x <= 180)
	{
		fallbackPoseOfX = 180;
	}
	else
	{
		fallbackPoseOfX = 360;
	}

	if (camera->pose.x + vertical > 180 && camera->pose.x + vertical < 360)
	{
		camera->pose.x = fallbackPoseOfX;
	}
	else
	{
		camera->pose.x += vertical/sensitivity;
	}

	if (camera->pose.x > 180 && camera->pose.x < 360)
	{
		set_clear_camera_pose(camera);
	}

	// Horizontal
	camera->pose.z += horizontal/sensitivity;

	if (camera->pose.z < 0)
	{
		camera->pose.z += 360.0;
	}

	if (camera->pose.z > 360.0)
	{
		camera->pose.z -= 360.0;
	}

	if (camera->pose.x < 0)
	{
		camera->pose.x += 360.0;
	}

	if (camera->pose.x > 360.0)
	{
		camera->pose.x -= 360.0;
	}
}
void set_clear_camera_pose(struct Camera *camera)
{
	camera->pose.x = 0;
}

void move_camera_forward(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z+ 90.0);

	camera->position.x += cos(angle) * distance;
	camera->position.y += sin(angle) * distance;
    can_move(camera);
}

void move_camera_backward(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z+ 90.0);

	camera->position.x -= cos(angle) * distance;
	camera->position.y -= sin(angle) * distance;
    can_move(camera);
}

void step_camera_left(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.x -= cos(angle) * distance;
	camera->position.y -= sin(angle) * distance;
    can_move(camera);
}

void step_camera_right(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.x += cos(angle) * distance;
	camera->position.y += sin(angle) * distance;
    can_move(camera);
}
void camera_jump(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	
	if (camera->position.z <= 2)
		camera->position.z += distance;
}
void move_camera_up(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	if (camera->position.z < size)
		camera->position.z += distance;

}

void move_camera_down(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	if (camera->position.z > 1)
		camera->position.z -= distance;

}
