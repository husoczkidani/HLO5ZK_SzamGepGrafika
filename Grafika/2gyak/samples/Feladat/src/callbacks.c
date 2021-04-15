#include "callbacks.h"
#include "scene.h"
#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

int increase = 0;
int decrease = 0;

struct {
    int x;
    int y;
} mouse_position;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

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
    button = button;
    state = state;
}

void motion(int x, int y)
{
    rotate_camera(&camera, mouse_position.x - x, mouse_position.y - y);
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
        set_camera_speed(&camera, 3.5);
        break;
    case 's':
        set_camera_speed(&camera, -2);
        break;
    case 'a':
        set_camera_side_speed(&camera, 2);
        break;
    case 'd':
        set_camera_side_speed(&camera, -2);
        break;
	case 'q':
        set_camera_vertical_speed(&camera, -2);
        break;
    case 'e':
        set_camera_vertical_speed(&camera, 2);
        break;
	case '+':
		if (scene.light < 1.0){
		scene.light += 0.1;}			
        break;
	case '-':
		if (scene.light > 0.2){
		scene.light -= 0.1;}
        break;
	case 'i':
		    set_csigusz_speed(&(scene.person),4);
        break;
	case 'k':
            set_csigusz_speed(&(scene.person),-4);
        break;
    case 'l':
        rotate_csigusz(&(scene.person), -25);
        break;
    case 'j':
        rotate_csigusz(&(scene.person), 25);
        break;
        x = x;
        y = y;
    case 'h' :
        if (is_help_visible) {
        is_help_visible = 0;
    }
    else is_help_visible = 1;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
	case 'q':
    case 'e':
        set_camera_vertical_speed(&camera, 0.0);
        break;
        x = x;
        y = y;
    case 'i':
    case 'k':
        set_csigusz_speed(&(scene.person), 0.0);
        break;
    }
    
    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);
    move_csigusz(&(scene.person),elapsed_time);
    rotate_csigusz(&(scene.fan),3);

    glutPostRedisplay();
}
