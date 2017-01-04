#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "visuals.h"

int main(int argc, char* argv[])
{
    // initialize GLUT library state
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
    // Define the main window size and initial position
    // ( upper left corner, boundaries included )
    glutInitWindowSize(830,830);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Solar_System");
    // Configure various properties of the OpenGL rendering context
    Setup();
    // The rendering function
    glutDisplayFunc(Render);
    glutReshapeFunc(Resize);
    loadObj("planet.obj");
    glutIdleFunc(Idle);
    glutKeyboardFunc(Keyboard);
    glutMainLoop();
    return 0;	
}  
