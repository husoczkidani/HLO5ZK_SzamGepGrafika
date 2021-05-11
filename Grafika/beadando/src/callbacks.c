#include "callbacks.h"
#include "help.h"
#include "camera.h"
#include "horse.h"
#include "skybox.h"

#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 50.0
#define size 110

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
    if(is_player_on_the_horse == TRUE)
    {
     rotate_horse(&(scene.horse),-horizontal);
    }
    
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
    case 'c':
        action.walk = TRUE;
        break;
    case 'e':
        if(is_player_on_the_horse == FALSE)
        {
            action.get_on_the_horse = TRUE;
        }else
        {
            action.get_on_the_horse = FALSE;
        }
           
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
    case 'c':
        action.walk = FALSE;
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

    if(action.walk == TRUE)
    {
        distance = elapsed_time * CAMERA_SPEED * speed /2;
    }
    if(action.walk == FALSE)
    {
        distance = elapsed_time * CAMERA_SPEED * speed;
    }
    if(action.sprint == TRUE)
    {
        distance = elapsed_time * CAMERA_SPEED * speed * 1.5;
    }
    if(action.sprint == FALSE && action.walk == FALSE)
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
        if(is_player_on_the_horse == TRUE)
        {
         move_horse_forward(&(scene.horse), distance);
        }
        
	}

	if (action.move_backward == TRUE)
	{
		move_camera_backward(camera, distance);
        if(is_player_on_the_horse == TRUE)
        {
         move_horse_backward(&(scene.horse), distance);
        }
	}

	if (action.step_left == TRUE)
	{
        if(is_player_on_the_horse == FALSE)
        {
         step_camera_left(camera, distance);
        }
	}

	if (action.step_right == TRUE)
	{
        if(is_player_on_the_horse == FALSE)
        {
         step_camera_right(camera, distance);
        }
	}
    
    if(action.get_on_the_horse == TRUE)
    {
        if(is_player_on_the_horse == FALSE)
        {
           get_on_the_horse(camera);
        }
    }

    if(action.get_on_the_horse == FALSE)
    {
        if(is_player_on_the_horse == TRUE)
        {
            camera->position.x = camera->position.x + 1;
            camera->position.y = camera->position.y+ 1;
            camera->position.z = 1;
            is_player_on_the_horse = FALSE;
        }
        
    }

    if(action.increase_light == TRUE)
    {
        if (scene.light < 0.5)
        {
		    scene.light += 0.05;
        }
        if(scene.light > 0.1 && day_loaded == FALSE)
        {
            day_loaded = TRUE;
            night_loaded = FALSE;
            load_daybox(&(scene.skybox));
        }
    }

    if(action.decrease_light == TRUE)
    {
        if (scene.light > 0.05)
        {
		    scene.light -= 0.05;
        }
        if(scene.light < 0.1 && night_loaded == FALSE)
        {
            day_loaded = FALSE;
            night_loaded = TRUE;
            load_nightbox(&(scene.skybox));
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

void can_move(struct Camera* camera)
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
    int i;
    float x[2],y[2];
    float width = 0.3;
    for(i=0;i<150;i++)
    {
        x[0] = scene.positions[i].x + width;
        x[1] = scene.positions[i].x - width;
        y[0] = (scene.positions[i].y* (-1)) + width;
        y[1] = (scene.positions[i].y* (-1)) - width;
        if((camera->position.x < x[0]) && (camera ->position.x > x[1]) && (camera->position.y < y[0]) && (camera->position.y > y[1]))
        {
             camera->position = camera->prev_position;
        }
    }   
}
void get_on_the_horse(struct Camera* camera)
{
    double horsey = -scene.horse.position.y;
    if((camera->position.x > scene.horse.position.x-1 && camera->position.x < scene.horse.position.x+1) && (camera->position.y > horsey-1 && camera->position.y < horsey+1))
    {
        is_player_on_the_horse = TRUE;
        camera->position.x = scene.horse.position.x;
        camera->position.y = -scene.horse.position.y;
        camera->position.z = 2;
        camera->pose.z = scene.horse.pose.z*(-1);
    }else
    {
        action.get_on_the_horse = FALSE;
    }
}

void can_horse_move(struct Horse* horse)
{
    if(horse->position.x>size || horse->position.x<-size || horse->position.y<-size || horse->position.y>size)
	{
		horse->position = horse->prev_position;
	}
	if(horse->position.x<10 && horse->position.x>-10 && horse->position.y<10 && horse->position.y>-10)
	{
		horse->position = horse->prev_position;
	}
	if(horse->position.x<-105 && horse->position.y > 106 && horse->position.y < 106.5)
	{
		horse->position = horse->prev_position;
	}
	if((horse->position.x <-104.5 && horse->position.x > -105) && ((horse->position.y > 106 && horse->position.y < 107.5) || horse->position.y > 108))
	{
		horse->position = horse->prev_position;
	}
    int i;
    float x[2],y[2];
    float width = 0.3;
    for(i=0;i<150;i++)
    {
        x[0] = scene.positions[i].x + width;
        x[1] = scene.positions[i].x - width;
        y[0] = (scene.positions[i].y) + width;
        y[1] = (scene.positions[i].y) - width;
        if((horse->position.x < x[0]) && (horse ->position.x > x[1]) && (horse->position.y < y[0]) && (horse->position.y > y[1]))
        {
             horse->position = horse->prev_position;
        }
    }   
}