#include "camera.h"
#include <GL/glut.h>
#include <math.h>
#include "scene.h"
#define size 10

void can_move(Camera* camera)
{
    if(camera->position.x>size || camera->position.x<-size || camera->position.y<-size || camera->position.y>size)
	{
		camera->prev_position = camera->position;
	}		
}

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 0.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
    is_help_visible = FALSE;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;
    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

	if (!(camera->position.x>size - 1 || camera->position.x<-size + 1 || camera->position.y<-size + 1 || camera->position.y>size - 1 || camera->position.z>size/2 - 1 || camera->position.z<-size/2 + 1))
	{
		camera->prev_position = camera->position;
		camera->position.x += cos(angle) * camera->speed.y * time;
		camera->position.y += sin(angle) * camera->speed.y * time;
		camera->position.x += cos(side_angle) * camera->speed.x * time;
		camera->position.y += sin(side_angle) * camera->speed.x * time;
		camera->position.z += camera->speed.z * time;
	} else {
		camera->position = camera->prev_position;
	}
    
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
	
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < -80.0) {
		camera->rotation.x = -80.0;
    }

    if (camera->rotation.x > 80.0) {
		camera->rotation.x = 80.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;

}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x  = speed;
}

void set_camera_vertical_speed(Camera* camera, double speed)
{
    camera->speed.z  = speed;
}

void show_help(struct Scene* scene)
{
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D,  scene->texture_id[11]);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

}


void move_csigusz(struct Object* object, double time)
{
    double angle;
    double side_angle;
    angle = degree_to_radian(object->rotation.z);
    side_angle = degree_to_radian(object->rotation.z + 90.0);

	if (!(object->position.x>size - 1 || object->position.x<-size + 1 || object->position.y<-size + 1 || object->position.y>size - 1))
	{
		object->prev_position = object->position;
		object->position.x += cos(angle) * object->speed.y * time;
		object->position.y += sin(angle) * object->speed.y * time;
		object->position.x += cos(side_angle) * object->speed.x * time;
		object->position.y += sin(side_angle) * object->speed.x * time;
	} else {
		object->position = object->prev_position;
	}
    
}

void rotate_csigusz(struct Object* object, double horizontal)
{
    object->rotation.z += horizontal;
    if (object->rotation.z < 0) {
        object->rotation.z += 360.0;
    }

    if (object->rotation.z > 360.0) {
        object->rotation.z -= 360.0;
    }
}

void set_csigusz_speed(struct Object* object, double speed)
{
    object->speed.y = speed;
}

void set_csigusz_side_speed(struct Object* object, double speed)
{
    object->speed.x  = speed;
}
