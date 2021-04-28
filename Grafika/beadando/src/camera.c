#include "camera.h"
#include "scene.h"

#include <GL/glut.h>

#include <math.h>
#define size 110
#define sensitivity 3

void can_move(Camera* camera, struct Scene* scene)
{
    if(camera->position.x>size || camera->position.x<-size || camera->position.y<-size || camera->position.y>size)
	{
		camera->position = camera->prev_position;
	}
	if(camera->position.x<10 && camera->position.x>-10 && camera->position.y<10 && camera->position.y>-10)
	{
		camera->position = camera->prev_position;
	}
	if(camera->position.x<-105 && camera->position.y > 106 && camera->position.y < 106.5)
	{
		camera->position = camera->prev_position;
	}
	if((camera->position.x <-104.5 && camera->position.x > -105) && ((camera->position.y > 106 && camera->position.y < 107.5) || camera->position.y > 108))
	{
		camera->position = camera->prev_position;
	}
	int i = 0;
	while(i<150)
	{
		if(camera->position.x == scene->positions[i].x && camera->position.y == scene->positions[i].y)
		{
			camera->position = camera->prev_position;
		}
		printf("%d", scene->positions[i].x);
		i++;
	}
}

void init_camera(Camera* camera)
{
    camera->position.x = -103.0;
    camera->position.y = 108.0;
    camera->position.z = 1;
    
    camera->pose.x = 90;
	camera->pose.y = 0;
	camera->pose.z = -135;

    is_help_visible = FALSE;
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
	can_move(camera,&scene);
}

void move_camera_backward(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z+ 90.0);

	camera->position.x -= cos(angle) * distance;
	camera->position.y -= sin(angle) * distance;
	can_move(camera,&scene);
}

void step_camera_left(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.x -= cos(angle) * distance;
	camera->position.y -= sin(angle) * distance;
	can_move(camera,&scene);
}

void step_camera_right(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.x += cos(angle) * distance;
	camera->position.y += sin(angle) * distance;
	can_move(camera,&scene);
}
void camera_jump(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	
	if (camera->position.z <= 2)
		camera->position.z += distance;
	can_move(camera,&scene);
}
void move_camera_up(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	if (camera->position.z < size)
		camera->position.z += distance;
	can_move(camera,&scene);
}

void move_camera_down(struct Camera *camera, double distance)
{
	camera->prev_position = camera->position;
	if (camera->position.z > 1)
		camera->position.z -= distance;
	can_move(camera,&scene);
}

