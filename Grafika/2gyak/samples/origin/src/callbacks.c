#include "callbacks.h"

#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 50.0

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    set_view(&camera);
    draw_scene(&scene);

    glPopMatrix();
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
    gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
}

void motion(int x, int y)
{
    //rotate_camera(&camera, x, y);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    float position;
    const float speed = 10.0;
    const float rotation_speed = 30.0;
    switch (key) {
    case 'w':
        set_camera_speed(&camera, speed);
        break;
    case 's':
        set_camera_speed(&camera, -speed);
        break;
    case 'a':
        set_camera_side_speed(&camera, speed);
        break;
    case 'd':
        set_camera_side_speed(&camera, -speed);
        break;
    case 'q':
        set_camera_horizontal_rotation_speed(&camera, rotation_speed);
        break;
    case 'e':
        set_camera_horizontal_rotation_speed(&camera, -rotation_speed);
        break;
    case 'r':
        set_camera_vertical_speed(&camera, speed);
        break;
    case 'f':
        set_camera_vertical_speed(&camera, -speed);
        break;
    case 't':
        set_camera_vertical_rotation_speed(&camera, rotation_speed);
        break;
    case 'g':
        set_camera_vertical_rotation_speed(&camera, -rotation_speed);
        break;

    }  

    glutPostRedisplay();
}

void extra_keyboard( int x, int y){
    float position;
    const float speed = 10.0;

    switch ( glutGetModifiers()){
        case GLUT_ACTIVE_CTRL:
            set_camera_vertical_speed(&camera, -speed);
            break;
        case GLUT_ACTIVE_SHIFT:
            set_camera_vertical_speed(&camera, speed);
            break;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    float position;

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
        set_camera_horizontal_rotation_speed(&camera, 0.0);
        break;
    case 'r':
    case 'f':
        set_camera_vertical_speed(&camera, 0.0);
        break;
    case 't':
    case 'g':
        set_camera_vertical_rotation_speed(&camera, 0.0);
        break;
    }

    
    glutPostRedisplay();
}

void extra_keyboard_up(int x, int y){
    float position;

    switch ( glutGetModifiers()){
        case GLUT_ACTIVE_CTRL:
        case GLUT_ACTIVE_SHIFT:
            set_camera_vertical_speed(&camera, 0.0);
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

    glutPostRedisplay();
}

