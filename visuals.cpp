#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <cstdlib>
#include <fstream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "visuals.h"   // Header file for our OpenGL functions
#include <iostream>
using namespace std;

float angle = 0.0f;
float glow = 1.0;
float u = 1.0;
GLuint planet;
float rot;
float xpos = 0, ypos = 0, zpos = 100.0, xrot = 0, yrot = 0, nrot = 0, mrot = 0;
static bool animate = true;
double posArray [600]; //for random positions

//gives random positions to posArray
void randPosition()
{
    for(int i=0;i<600;i=i+3){
        double x = (rand()%1080-590)*0.1;
        double y = (rand()%1080-590)*0.1;
        double z = (rand()%1500-1200)*0.1;
        posArray[i] = x;
        posArray[i+1] = y;
        posArray[i+2] = z;
    }
}

//creates 100 random stars
void random_star(){
    
    for(int i=0;i<600;i=i+3){
        glPushMatrix();
        glTranslatef(posArray[i], posArray[i+1],posArray[i+3]);
        glTranslatef(0.0, 0.0, -35.0);
        glScalef(0.02, 0.02, 0.02);     
        glColor4f(1.0, 1.0, 1.0, glow);
        glutSolidSphere( 10.0, 30, 24);   
        glColor3f(1.0, 1.0, 1.0);
        glutSolidSphere( 8.0, 30, 24);
        glPopMatrix();
    }
    
}

//Draws planet(1)
void drawPlanet()
{
    
    float x = sin(angle*2) * (25.0);
    float y= 0.0;
    float z = cos(angle*2) * (25.0);
    glPushMatrix();
    glTranslatef(x, y, z );
    glScalef(0.004,0.004,0.004);
    glRotatef(10*rot,0,1,0);
    glCallList(planet);
    glPopMatrix();
    
}
//Draws planet(2)
void drawPlanet1()
{
    
    float x = sin(angle) * (20.0);
    float y= cos(angle) * (20.0);
    float z = 0.0;
    glPushMatrix();
    glTranslatef(x, y, z );
    glScalef(0.01,0.01,0.01);
    glRotatef(rot,0,0,1);
    glCallList(planet);
    glPopMatrix();
    
}

void drawPlanet2()
{
    
    float x = 0.0;
    float y= cos(angle*5) * (50.0);
    float z = sin(angle*5) * (50.0);
    glPushMatrix();
    glTranslatef(x, y, z );
    glScalef(0.001,0.001,0.001);
    glRotatef(100*rot,0,1,0);
    glCallList(planet);
    glPopMatrix();
    
}

void drawPlanet3()
{
    
    float x = sin(angle*3) * (30.0);
    float y= cos(angle*3) * (30.0);
    float z = sin(angle*3) * (30.0);
    glPushMatrix();
    glTranslatef(x, y, z );
    glScalef(0.005,0.005,0.005);
    glRotatef(rot,1,0,0);
    glCallList(planet);
    glPopMatrix();
    
}

void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
    
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    
    glRotatef(nrot,0.0,nrot,1.0);  //rotate on the spot
    
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
    
}

//Renders our scene
void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    camera();
    
    glColor4f(0.9, 0.7, 0.0, 1.0);
    glutSolidSphere( 8.0, 30, 24);
    
    glColor4f(0.9, 0.7, 0.0, glow);
    glutSolidSphere( 10.0, 50, 35);
    
    glColor3f(0.0, 1.0, 0.0);
    drawPlanet();
    
    glColor3f(1.0, 0.0, 0.0);
    drawPlanet1();
    
    glColor3f(0.0, 0.0, 1.0);
    drawPlanet2();
    
    glColor3f(1.0, 0.5, 0.0);
    drawPlanet3();
    
    random_star();
    
    glutSwapBuffers();
}

//-----------------------------------------------------------

void Resize(int w, int h)
{
    // define the visible area of the window ( in pixels )
    if (h==0) h=1;
    glViewport(0,0,w,h);
    
    // Setup viewing volume
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(60.0, (float)w/(float)h, 1.0, 500.0);
}

void Idle()
{
    if(animate){
        if(angle == 6.283185307f)
            angle = 0.0f;    //for orbiting the planets
        angle = angle + 0.01;

        if(glow == 1.0)
            u=-u;
        else if(glow == 0.1 || glow < 0.1)
            u=-u;
        glow = glow + 0.01*u;    //for the sun and stars
        rot = rot+0.6;
        if(rot>360) rot = rot-360; //for rotating planets
    }
    
    glutPostRedisplay();
    
    
}

void Setup()
{
    //Parameter handling
    glShadeModel (GL_SMOOTH);
    
   
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
    glClearDepth(1);
    
     // polygon rendering mode
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    
    //Set up light source
    //GLfloat light_position[] = { 0.0, -500.0, -500.0, 0.0 };
    //glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    
    GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
    
	   
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    
    // BLENDING
   	glEnable(GL_BLEND);
    // incoming //  // stored //
   	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    randPosition();
    // Black background
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
}

void Keyboard(unsigned char key,int x,int y)
{
    float xrotrad, yrotrad;
    
    switch(key)
    {
        case 'q' : xrot -= 1;
            if (xrot < -360) xrot += 360;
            break;
        case 'z' :  xrot += 1;
            if (xrot >360) xrot -= 360;
            break;
        case 'e' : nrot -= 1;
            if (nrot <0) nrot += 360;
            break;
        case 'r' :  nrot += 1;
            if (nrot >360) nrot -= 360;
            break;
        case 'w' :
            yrotrad = (yrot / 180 * 3.141592654f);
            xrotrad = (xrot / 180 * 3.141592654f);
            xpos += float(sin(yrotrad)) ;
            zpos -= float(cos(yrotrad)) ;
            ypos -= float(sin(xrotrad)) ;
            break;
        case 's' :
            yrotrad = (yrot / 180 * 3.141592654f);
            xrotrad = (xrot / 180 * 3.141592654f);
            xpos -= float(sin(yrotrad));
            zpos += float(cos(yrotrad)) ;
            ypos += float(sin(xrotrad));
            break;
        case 'd' :
            yrotrad = (yrot / 180 * 3.141592654f);
            xpos += float(cos(yrotrad)) * 0.5;
            zpos += float(sin(yrotrad)) * 0.5;
            break;
        case 'a' :
            yrotrad = (yrot / 180 * 3.141592654f);
            xpos -= float(cos(yrotrad)) * 0.5;
            zpos -= float(sin(yrotrad)) * 0.5;
            break;
        case 'p' : animate = !animate;
            break;
        default : break;
    }
    
    glutPostRedisplay();
    
}

void loadObj(const char *fname)
{
    FILE *fp;
    int read;
    GLfloat x, y, z;
    char ch;
    planet=glGenLists(1);
    fp=fopen(fname,"r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glNewList(planet, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_POLYGON);
        while(!(feof(fp)))
        {
            read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
            if(read==4&&ch=='v')
            {
                glVertex3f(x,y,z);
            }
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fclose(fp);
}

