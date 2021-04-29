#include "callbacks.h"
#include "help.h"
#include "camera.h"

#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 50.0

struct {
    int x;
    int y;
} mouse_position;

void display()
{
    double elapsed_time = calc_elapsed_time();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    update_camera_position(&camera, elapsed_time);

    glPushMatrix();
    set_view(&camera);
    draw_scene(&scene);
    glPopMatrix();

    if (is_help_visible) {
        show_help(&scene);
    }

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }
    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
   
}

void mouse(int button, int state, int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
}

void motion(int x, int y)
{
    double horizontal, vertical;

    horizontal = mouse_position.x - x;
    vertical = mouse_position.y - y;

    rotate_camera(&camera, horizontal, vertical);
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if(camera.position.z >=2)
			action.jump = FALSE;

    switch (key) {
    case 'w':
        action.move_forward = TRUE;
        break;
    case 's':
        action.move_backward = TRUE;
        break;
    case 'a':
        action.step_left = TRUE;
        break;
    case 'd':
        action.step_right = TRUE;
        break;
    case 'q':
        action.sprint = TRUE;
        break;
    case '+':
        action.increase_light = TRUE;
        break;
    case '-':
        action.decrease_light = TRUE;
        break;
    case 32 :
        if(camera.position.z <=1)
			action.jump = TRUE;
        break;
    case 27:
        exit(0);
    }

    glutPostRedisplay();
}

void specialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		if (is_help_visible) {
            is_help_visible = FALSE;
        }
        else {
            is_help_visible = TRUE;
        }
        break;
	}
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
        action.move_forward = FALSE;
        break;
    case 's':
        action.move_backward = FALSE;
        break;
    case 'a':
        action.step_left = FALSE;
        break;
    case 'd':
        action.step_right = FALSE;
        break;
    case 'q':
        action.sprint = FALSE;
        break;
    case '+':
        action.increase_light = FALSE;
        break;
    case '-':
        action.decrease_light = FALSE;
        break;
    case 32 :
        action.jump = FALSE;
        break;
    }

    glutPostRedisplay();
}

void update_camera_position(struct Camera* camera, double elapsed_time)
{
    float speed = 3;
    float jumpspeed = 1.8;
    double distance;
    double jumpdistance;

    distance = elapsed_time * CAMERA_SPEED * speed;
    jumpdistance = elapsed_time * CAMERA_SPEED * jumpspeed;

    if(action.sprint == TRUE)
    {
        distance = elapsed_time * CAMERA_SPEED * speed*1.5;
    }
    if(action.sprint == FALSE)
    {
        distance = elapsed_time * CAMERA_SPEED * speed;
    }
    if(action.jump == TRUE)
	{
		camera_jump(camera,jumpdistance);
	}
	if(action.jump == FALSE)
	{
		move_camera_down(camera,jumpdistance);
	}

	if (action.move_forward == TRUE)
	{
		move_camera_forward(camera, distance);
	}

	if (action.move_backward == TRUE)
	{
		move_camera_backward(camera, distance);
	}

	if (action.step_left == TRUE)
	{
		step_camera_left(camera, distance);
	}

	if (action.step_right == TRUE)
	{
		step_camera_right(camera, distance);
	}

    if(action.increase_light == TRUE)
    {
        if (scene.light < 0.5)
        {
		    scene.light += 0.05;
        }
    }

    if(action.decrease_light == TRUE)
    {
        if (scene.light > 0.05)
        {
		    scene.light -= 0.05;
        }
    }
}
void idle()
{
    glutPostRedisplay();
}

double calc_elapsed_time()
{
	static int last_frame_time = 0;
	int current_time;
	double elapsed_time;

	current_time = glutGet(GLUT_ELAPSED_TIME);
	elapsed_time = (double)(current_time - last_frame_time) / 1000.0;
	last_frame_time = current_time;

	return elapsed_time;
}