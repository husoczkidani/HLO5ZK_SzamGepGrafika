#include "callbacks.h"
#include "init.h"

#include <GL/glut.h>

#include <stdio.h>
/**
 * Teendők:
 * callback refactor
 * történet írás a játékhoz
 * játékbeli fuunkciók
 * meglovagolható állat
 * sasok random mozgása az égen
 * objektumok külön fájlokba rendezése
 */



/**
 * Set the callbacks for GLUT.
 */
void set_callbacks()
{
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(specialFunc);
    glutIdleFunc(idle);
}

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    int window;

    glutInit(&argc, argv);

    glutInitWindowSize(1600, 900);     
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    window = glutCreateWindow("Husoczki Daniel HLO5ZK Grafika beadando 2021");
    glutSetWindow(window);

    init_opengl();
    init_scene(&scene);
    init_camera(&camera);
    set_callbacks();

    glutMainLoop();

    return 0;
}
