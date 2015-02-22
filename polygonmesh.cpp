//*************************************************************
// A. Pahlavan Tafti & L. Zhang
// *************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h> // (or others, depending on the system in use)
#include <iostream>


//Declaring StructS
typedef struct {
	float x;
	float y;
	float z;
}FLTVECT;

typedef struct {
	int a;
	int b;
	int c;
}INT3VECT;


typedef struct {
	int nv;
	int nf;
	FLTVECT *vertex;
	INT3VECT *face;
}SurFacemesh;

// Rotation variables
float xrot = 0.0f;
float yrot = 0.0f;

// Translation variables
float xt=0.0f;
float yt=0.0f;
float zt=0.0f;

//Scaling variables
float sx=0.5f;

float xdiff = 0.0f;
float ydiff = 0.0f;
char KEY='t';

static int menuExit;
static int Polygonmode;
static int val = 1;
int num,n,m;
int a,b,c,d,e;
float x,y,z;
bool fullscreen = false;
bool mouseDown = false;


// Function for reading OFF format (file)
SurFacemesh* readPolygon()
{
	float v1[3] , v2[3], v3[3];
	GLfloat v12[3], v23[3], v13[3];
	SurFacemesh *surfmesh;
	char line[256];
	FILE *fin;
	if ((fin=fopen("c:/users/ahmad/sample_polygon.off", "r"))==NULL){
		printf("read error...\n");
		exit(0);
	};
	/* OFF format */
	while (fgets(line,256,fin) != NULL) {
		if (line[0]=='O' && line[1]=='F' && line[2]=='F')
			break;
	}
	fscanf(fin,"%d %d %d\n",&m,&n,&num);
	surfmesh = (SurFacemesh*)malloc(sizeof(SurFacemesh));
	surfmesh->nv = m;
	surfmesh->nf = n;
	surfmesh->vertex = (FLTVECT *)malloc(sizeof(FLTVECT)*surfmesh->nv);
	surfmesh->face = (INT3VECT *)malloc(sizeof(INT3VECT)*surfmesh->nf);
	for (n = 0; n < surfmesh->nv; n++) 
	{
		fscanf(fin,"%f %f %f\n",&x,&y,&z);
		surfmesh->vertex[n].x = x;
		surfmesh->vertex[n].y = y;
		surfmesh->vertex[n].z = z;
	}
	for (n = 0; n < surfmesh->nf; n++) 
	{
		fscanf(fin,"%d %d %d %d\n",&a,&b,&c,&d);
		surfmesh->face[n].a = b;
		surfmesh->face[n].b = c;
		surfmesh->face[n].c = d;
		if(a != 3)
			printf("Errors: reading surfmesh .... \n");
	}
	fclose(fin);
	return surfmesh;
}


// Surface mesh obtained from OFF file
  SurFacemesh* surfmesh = readPolygon();


// Drawing Polygon Based on Menu Selection
 void draw()
{

	if (val==1) //Depends on Menu -> Point 
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
		for (n=0;n<surfmesh->nv;n++)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(surfmesh->vertex[n].x, surfmesh->vertex[n].y, surfmesh->vertex[n].z);
			glEnd();
		}
	}
	
	else if (val==2) //Depends on Menu -> Line
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		for (n=0;n<surfmesh->nf;n++)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_TRIANGLES);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].a].x, surfmesh->vertex[surfmesh->face[n].a].y, surfmesh->vertex[surfmesh->face[n].a].z);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].b].x, surfmesh->vertex[surfmesh->face[n].b].y, surfmesh->vertex[surfmesh->face[n].b].z);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].c].x, surfmesh->vertex[surfmesh->face[n].c].y, surfmesh->vertex[surfmesh->face[n].c].z);
			glEnd();
		}
  	}
	
	else if (val==3) //Depends on Menu -> Fill
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		for (n=0;n<surfmesh->nf;n++)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].a].x, surfmesh->vertex[surfmesh->face[n].a].y, surfmesh->vertex[surfmesh->face[n].a].z);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].b].x, surfmesh->vertex[surfmesh->face[n].b].y, surfmesh->vertex[surfmesh->face[n].b].z);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].c].x, surfmesh->vertex[surfmesh->face[n].c].y, surfmesh->vertex[surfmesh->face[n].c].z);
			glEnd();
		}
	}
	
	else if (val==4) //Depends on Menu -> Both (Line and Fill)
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		for (n=0;n<surfmesh->nf;n++)
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_TRIANGLES);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].a].x, surfmesh->vertex[surfmesh->face[n].a].y, surfmesh->vertex[surfmesh->face[n].a].z);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].b].x, surfmesh->vertex[surfmesh->face[n].b].y, surfmesh->vertex[surfmesh->face[n].b].z);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].c].x, surfmesh->vertex[surfmesh->face[n].c].y, surfmesh->vertex[surfmesh->face[n].c].z);
			glEnd();
		}

		glEnable (GL_POLYGON_OFFSET_FILL); 
		glPolygonOffset (1.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		for (n=0;n<surfmesh->nf;n++)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_TRIANGLES);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].a].x, surfmesh->vertex[surfmesh->face[n].a].y, surfmesh->vertex[surfmesh->face[n].a].z);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].b].x, surfmesh->vertex[surfmesh->face[n].b].y, surfmesh->vertex[surfmesh->face[n].b].z);
			glVertex3f(surfmesh->vertex[surfmesh->face[n].c].x, surfmesh->vertex[surfmesh->face[n].c].y, surfmesh->vertex[surfmesh->face[n].c].z);
			glEnd();
		}
	}
	
 glDisable (GL_POLYGON_OFFSET_FILL);
}
	
	
 //Initialization Function 	
 bool init()
  {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	return true;
 }


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// Viewing Point
	gluLookAt(
		20.0f, 30.0f, 60.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glTranslatef(xt, -yt, 1.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glScalef(sx, sx, sx); 
	draw();
	glFlush();
	glutSwapBuffers();
}


void resize(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(70.0f, 1.0f * w / h, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{

	if (!mouseDown && KEY=='r')
	{
		xrot += 0.3f;
		yrot += 0.4f;
	}

	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27 : 
		exit(1); break;
	case 114 :
		KEY='r'; break;
	case 115 :
		KEY='s'; break;
	case 116 :
		KEY='t'; break;
	}
}


void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && KEY=='r')
	{
		mouseDown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && KEY=='t')
	{
		mouseDown=true;
		xdiff=x-xt;
		ydiff=y-yt;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && KEY=='s')
	{
		mouseDown=true;
		xdiff=x-xt;
		ydiff=y-yt;
	}
	else
		mouseDown = false;
}



void mouseMotion(int x, int y)
{
	if (mouseDown && KEY=='r')
	{
		yrot = x - xdiff;
		xrot = y + ydiff;
	}

	else if (mouseDown && KEY=='t')
	{
		xt = x - xdiff;
		yt = y - ydiff;
	}

	else if (mouseDown && KEY=='s')
	{
		sx= float(sqrt ((x-xdiff)*(x-xdiff)+(y-ydiff)*(y-ydiff))/100);
	}

	glutPostRedisplay();
}


void specialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_F1){
		fullscreen = !fullscreen;
		if (fullscreen) glutFullScreen();
		else{
			glutReshapeWindow(800, 600);
			glutPositionWindow(100, 100);
		}
	}
}


//Main block
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("CS 459- Project 3: 3D Interactive Polygon Viewing");
	createMenu();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(resize);
	if (!init())
		return 1;
	glutMainLoop();
	return 0;
}

//Menu and Sub Menus
void createMenu(void){
	//////////
	// MENU //
	//////////
	Polygonmode = glutCreateMenu(menu);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Fill", 3);
	glutAddMenuEntry("Both", 4);
	menuExit = glutCreateMenu(menu);
	// Create an entry
	glutAddSubMenu("Polygon Mode", Polygonmode);
	glutAddMenuEntry("Exit", 0);

	// Let the menu respond on the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);	
}

void menu(int value){
	if(value == 0){
		exit(0);
	}
	else
	{
		val=value;
	}

	glutPostRedisplay();
}
