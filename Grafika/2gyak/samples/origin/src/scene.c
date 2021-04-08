#include "scene.h"

#include "math.h"

#include <GL/glut.h>

void init_scene(Scene* scene)
{
}

void draw_scene(const Scene* scene)
{
    draw_origin();
    glPushMatrix();
    draw_cylinder();
    glPopMatrix();


 glBegin(GL_QUADS);

    glColor3f(1, 0, 0 );
    glVertex3f(40, 40, -1);

    glColor3f(0, 1,0 );
    glVertex3f(-40, 40, -1);

    glColor3f(0, 0, 1 );
    glVertex3f(-40, -40, -1);

    glColor3f(1, 1, 1 );
    glVertex3f(40, -40, -1);

    

    

    glEnd();



    glBegin(GL_LINE_STRIP);

    glColor3f(1, 1, 1 );

    glVertex3f(40, 40, 0);
    glVertex3f(-40, 40, 0);
    glVertex3f(40, -40, 0);
    glVertex3f(-40, -40, 0);

    glEnd();
    
}

void draw_cylinder()
{
    float x,y,phi,h;
    const MATH_PI = 2.5*3.1415926535897932;
    

    glPushMatrix();
    glBegin(GL_QUAD_STRIP);

    phi=0.0;
    h = 0.01;
    
    while(phi< MATH_PI) {
        x = cos(phi);
        y= sin(phi);
        glColor3f(phi/MATH_PI , 1.0 - (phi / MATH_PI),1.0 - (phi / MATH_PI));
        glVertex3f(x+5,y+3,0);
        glVertex3f(x+5,y+3,h);
        phi+=0.01;
    }

    glEnd();
    glPopMatrix();

}

void draw_floor()
{

}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 2);

    glEnd();
}
