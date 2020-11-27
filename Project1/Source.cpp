/*
*		This Code Was Created By Jeff Molofee 2000
*		A HUGE Thanks To Fredric Echols For Cleaning Up
*		And Optimizing This Code, Making It More Flexible!
*		If You've Found This Code Useful, Please Let Me Know.
*		Visit My Site At nehe.gamedev.net
*/

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <glaux.h>		// Header File For The Glaux Library
//#include <gl/glaux.h>
//#include <glut.h>
#include <cmath>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "gltexture.h"
#include "Model_3DS.h"
#include "Camera.h"
#include "Car.h"
#include "Engine.h"
#include "wheel.h"
#include "GUI.h"
#include <string>
#include <msclr\marshal_cppstd.h>
#include <irrKlang.h>
// include console I/O methods (conio.h for windows, our wrapper in linux)
#if defined(WIN32)
#include <conio.h>
#else
#include "../common/conio.h"
#endif
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll


HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

//Yassarooooooooooo

float Light_Ambient[] = { 0.3,0.3,0.3,1 };
float Light_Diffuse[] = { 1.0,1.0,1.0,1 };
float Light_Specular[] = { 1.0,1.0,1.0,1 };
float Light_Position[] = { 0,20,300,1 };
float Light_Spot_direction[] = { 0, -20, -500 };
float Light_CutOff = 10;

float Light_Ambient2[] = { 1.0,1.0,1.0,1.0,1 };
float Light_Diffuse2[] = { 1.0,1.0,1.0,1 };
float Light_Specular2[] = { 1.0,1.0,0.1,1 };
float Light_Position2[] = { -1,3.2,0,1 };
float Light_Spot_direction2[] = { 0.0, -5.0, 0 };
float Light_CutOff2 = 20;

float Light_Ambient1[] = { 1.0,1.0,1.0,1.0,1 };
float Light_Diffuse1[] = { 1.0,1.0,1.0,1 };
float Light_Specular1[] = { 1.0,1.0,0.1,1 };
float Light_Position1[] = { 0, 7, 0, 1 };
float Light_Spot_direction1[] = { 0.0, -100.0, 0 };
float Light_CutOff1 = 700;

float Cone_Ambient[] = { 0.1,0.1,0.1,1 };
float Cone_Diffuse[] = { 0.2,0.1,0.9,1 };
float Cone_Specular[] = { 1,1,1,1 };
float Cone_Shininess = 100;

GLfloat asp_Specular[] = { 1.0,1.0,1.0,1.0 };
GLfloat asp_Shininess[] = { 90.0 };

GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat mat_amb_diff_color_red[] = { 1.0, 0.5, 0.0, 0.5 };
GLfloat mat_amb_diff_color_green[] = { 0.0, 1.0, 0.0, 0.5 };


// defining Sphere properties
float Sphere_Ambient[] = { 0.2,0.2,0.1,1 };
float Sphere_Diffuse[] = { 0.2,0.3,1,1 };
float Sphere_Specular[] = { 1,1,1,1 };
float Sphere_Shininess = 120;

float asphalt_Ambient[] = { 0,0,0,1 };
float asphalt_Diffuse[] = { 0,0,0,1 };
float asphalt_Specular[] = { 1,1,1,1 };
float asphalt_Shininess = 120;

UINT texture[50];
UINT skybox1[6];
UINT skybox2[6];
bool day = true;
static int night = 0;

float angle = 0;
float angle2 = 0.6;
float angle3 = 2;
#define PI	3.14f

int num_texture = -1; //Counter to keep track of the last loaded texture

int LoadTexture(char *filename, int alpha)
{
	int i, j = 0; //Index variables
	FILE *l_file; //File pointer
	unsigned char *l_texture; //The pointer to the memory zone in which we will load the texture

							  // windows.h gives us these types to work with the Bitmap files
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	num_texture++; // The counter of the current texture is increased

	if ((l_file = fopen(filename, "rb")) == NULL) return (-1); // Open the file for reading

	fread(&fileheader, sizeof(fileheader), 1, l_file); // Read the fileheader

	fseek(l_file, sizeof(fileheader), SEEK_SET); // Jump the fileheader
	fread(&infoheader, sizeof(infoheader), 1, l_file); // and read the infoheader

													   // Now we need to allocate the memory for our image (width * height * color deep)
	l_texture = (byte *)malloc(infoheader.biWidth * infoheader.biHeight * 4);
	// And fill it with zeros
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

	// At this point we can read every pixel of the image
	for (i = 0; i < infoheader.biWidth*infoheader.biHeight; i++)
	{
		// We load an RGB value from the file
		fread(&rgb, sizeof(rgb), 1, l_file);

		// And store it
		l_texture[j + 0] = rgb.rgbtRed; // Red component
		l_texture[j + 1] = rgb.rgbtGreen; // Green component
		l_texture[j + 2] = rgb.rgbtBlue; // Blue component
		l_texture[j + 3] = alpha; // Alpha value
		j += 4; // Go to the next position
	}

	fclose(l_file); // Closes the file stream

	glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

											   // The next commands sets the texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //The minifying function

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECR);

	// Finally we define the 2d texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	// And create 2d mipmaps for the minifying function
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	free(l_texture); // Free the memory we used to load the texture

	return (num_texture); // Returns the current texture OpenGL ID
}
//Yassaroooooooooooo

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

Model_3DS *model;

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	model = new Model_3DS();
	model->Load("ShelbyWD.3DS");
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
	{
		return 0; // error starting up the engine
	}

	engine->play2D("skybox/en.ogg", true);


	//Yassarooooooooo
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//load the texture
	skybox1[3] = LoadTexture("sky/Front.bmp", 256);
	skybox1[2] = LoadTexture("sky/Back.bmp", 256);
	skybox1[0] = LoadTexture("sky/Left.bmp", 256);
	skybox1[1] = LoadTexture("sky/Right.bmp", 256);
	skybox1[4] = LoadTexture("sky/Bottom.bmp", 256);
	skybox1[5] = LoadTexture("sky/Top.bmp", 256);

	skybox2[3] = LoadTexture("skynight/Front.bmp", 256);
	skybox2[2] = LoadTexture("skynight/Back.bmp", 256);
	skybox2[0] = LoadTexture("skynight/Left.bmp", 256);
	skybox2[1] = LoadTexture("skynight/Right.bmp", 256);
	skybox2[4] = LoadTexture("skynight/Bottom.bmp", 256);
	skybox2[5] = LoadTexture("skynight/Top.bmp", 256);

	texture[6] = LoadTexture("skybox/asp.bmp", 256);
	texture[7] = LoadTexture("skybox/grass.bmp", 256);
	texture[8] = LoadTexture("skybox/mall.bmp", 256);
	texture[9] = LoadTexture("skybox/RoadSides.bmp", 256);
	texture[10] = LoadTexture("skybox/building.bmp", 256);
	texture[11] = LoadTexture("skybox/building2.bmp", 256);
	texture[12] = LoadTexture("skybox/building4.bmp", 256);
	texture[13] = LoadTexture("skybox/building5.bmp", 256);
	texture[14] = LoadTexture("skybox/building6.bmp", 256);
	/*
	texture[15] = LoadTexture("skybox/clock.bmp", 256);
	texture[16] = LoadTexture("skybox/bricks.bmp", 256);
	texture[17] = LoadTexture("skybox/rolldoor.bmp", 256);
	texture[18] = LoadTexture("skybox/wall1.bmp", 256);
	texture[19] = LoadTexture("skybox/wood1.bmp", 256);
	texture[20] = LoadTexture("skybox/metal1.bmp", 256);
	texture[21] = LoadTexture("skybox/parking.bmp", 256);
	texture[22] = LoadTexture("skybox/ceramic.bmp", 256);
	texture[23] = LoadTexture("skybox/glassface1.bmp", 256);
	texture[24] = LoadTexture("skybox/glassface2.bmp", 256);
	texture[25] = LoadTexture("skybox/rightglass.bmp", 256);
	texture[26] = LoadTexture("skybox/floor2.bmp", 256);
	texture[27] = LoadTexture("skybox/pizza.bmp", 256);
	texture[28] = LoadTexture("skybox/bar.bmp", 256);
	texture[29] = LoadTexture("skybox/parksign.bmp", 256);
	texture[30] = LoadTexture("skybox/shop1.bmp", 256);
	texture[31] = LoadTexture("skybox/shop2.bmp", 256);
	texture[32] = LoadTexture("skybox/shop3.bmp", 256);
	texture[33] = LoadTexture("skybox/shop4.bmp", 256);
	texture[34] = LoadTexture("skybox/shop5.bmp", 256);
	texture[35] = LoadTexture("skybox/arrow.bmp", 256);
	texture[36] = LoadTexture("skybox/name.bmp", 256);
	*/
	//Yassaroooooooo

	return TRUE;										// Initialization Went OK
}

//Yassaroooooooooo
void skybox(void) {
	float x = 0;
	float y = 0;
	float z = 0;
	float width = 2000;
	float height = 700;
	float length = 2000;
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	// Center the skybox
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;
	if (!day) {
		glBindTexture(GL_TEXTURE_2D, skybox2[0]);
	}
	else if (day) {
		glBindTexture(GL_TEXTURE_2D, skybox1[0]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	if (!day) {
		glBindTexture(GL_TEXTURE_2D, skybox2[1]);
	}
	else if (day) {
		glBindTexture(GL_TEXTURE_2D, skybox1[1]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	if (!day) {
		glBindTexture(GL_TEXTURE_2D, skybox2[4]);
	}
	else if (day) {
		glBindTexture(GL_TEXTURE_2D, skybox1[4]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, -20, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, -20, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, -20, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, -20, z);
	glEnd();

	/*if (!day) {
		glBindTexture(GL_TEXTURE_2D, skybox2[5]);
	}*/
	/*else if (day) {
		glBindTexture(GL_TEXTURE_2D, skybox1[5]);
	}*/
	/*glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();*/

	/*if (!day) {
		glBindTexture(GL_TEXTURE_2D, skybox2[2]);
	}
	else if (day) {
		glBindTexture(GL_TEXTURE_2D, skybox1[2]);
	}*/
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	if (!day) {
		glBindTexture(GL_TEXTURE_2D, skybox2[3]);
	}
	else if (day) {
		glBindTexture(GL_TEXTURE_2D, skybox1[3]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}
void draw_sphere(float x, float y, float z, float r) {
	glEnable(GL_POINT_SMOOTH);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (float theta = 0; theta <= 2 * PI; theta += 0.2)
	{
		for (float alpha = -PI; alpha <= PI; alpha += 0.3)
		{
			glVertex3f(x + (r*cos(alpha))*cos(theta),
				y + (r*cos(alpha))*sin(theta),
				z + r*sin(alpha));
		}
	}
	glEnd();
	glDisable(GL_POINT_SMOOTH);
}
void draw_tree() {
	GLUquadric *qobj;
	qobj = gluNewQuadric();

	glPushMatrix();
	glColor3f(0.1, 0.3, 0);
	glTranslated(0, 4, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 2.0, 0, 3, 32, 70);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 3.0, 0, 4, 32, 70);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -1, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 1.0, 1, 2, 32, 70);
	glPopMatrix();
}
void draw_light() {

	GLUquadric *qobj;
	qobj = gluNewQuadric();
	glPushMatrix();
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.1, 0.1, 0.1);
	gluCylinder(qobj, 0.3, 0.3, 10, 32, 70);
	glPopMatrix();
	glTranslatef(0, 10, 0);
	glColor3f(1, 1, 1);

	if (night == 1) {
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, Light_Specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Light_Spot_direction1);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, Light_CutOff1);

		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT0);
	}
	else if (night == 0) {
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);
	}

	draw_sphere(0, 0, 0, 0.7);

	glPopMatrix();
}
void draw_traffic_signal() {
	GLUquadric *qobj;
	qobj = gluNewQuadric();
	glPushMatrix();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.1, 0.1, 0.1);
	gluCylinder(qobj, 0.3, 0.3, 10, 32, 70);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 10, 0);
	glRotatef(90, 0, 1, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobj, 0.3, 0.3, 6, 32, 70);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 10.5, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(qobj, 0.3, 0.3, 2, 32, 70);

	glColor3f(1, 0, 0);
	glTranslatef(0, -0.3, 0.3);
	gluSphere(qobj, 0.25, 32, 70);

	glColor3f(1, 0.35, 0);
	glTranslatef(0, 0, 0.6);
	gluSphere(qobj, 0.25, 32, 70);

	glColor3f(0, 1, 0);
	glTranslatef(0, 0, 0.6);
	gluSphere(qobj, 0.25, 32, 70);

	glPopMatrix();

	if (night == 1) {


		glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, Light_Specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Light_Spot_direction1);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, Light_CutOff1);

		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT0);
	}
	else if (night == 0) {
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);
	}


	glPopMatrix();
}
void draw_road(float width, float dis) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTranslated(0, -3, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, 0, dis);
	glTexCoord2f(1.0f, 3.0f); glVertex3f(width, 0, -dis);
	glTexCoord2f(0.0f, 3.0f); glVertex3f(-width, 0, -dis);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, 0, dis);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void draw_floor2(float width, float dis) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTranslated(0, -3, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, texture[26]);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(40.0f, 0.0f); glVertex3f(width, 0, dis);
	glTexCoord2f(40.0f, 60.0f); glVertex3f(width, 0, -dis);
	glTexCoord2f(0.0f, 60.0f); glVertex3f(-width, 0, -dis);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, 0, dis);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void draw_grass() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTranslated(10, -3, 0);
	glColor3f(1, 1, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	glTexCoord2f(25.0f, 0.0f); glVertex3f(1000, 0, 1000);
	glTexCoord2f(25.0f, 25.0f); glVertex3f(1000, 0, -1000);
	glTexCoord2f(0.0f, 25.0f); glVertex3f(0, 0, -1000);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 1000);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void draw_floor() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTranslated(-10, -3, 0);
	glColor3f(1, 1, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glBegin(GL_QUADS);
	glTexCoord2f(30.0f, 0.0f); glVertex3f(-1000, 0, 1000);
	glTexCoord2f(30.0f, 35.0f); glVertex3f(-1000, 0, -1000);
	glTexCoord2f(0.0f, 35.0f); glVertex3f(0, 0, -1000);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 1000);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void mall2(float width, float height, UINT t) {
	glPushMatrix();
	glEnable(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, t);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);

	//top
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, height, -width); //1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, height, -width); //0 0
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, width);// 0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, width);//1 1

															   //bottom
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, 0, width);//1 1
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, 0, width);//0 1
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, 0, -width);//0 0
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, 0, -width);//1 0

														   //back
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height, width);//0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, height, width);// 1 1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, 0, width);//1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, 0, width);//0 0


														  //front
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, 0, -width);//1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, 0, -width);//0 0
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, -width);// 0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, -width);// 1 1

																//left
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, width);//0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, height, -width);//1 1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, 0, -width);// 1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, 0, width);//0 0

														   //right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height, -width);//0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, width);//1 1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, 0, width);//1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, 0, -width);//0 0

	glEnd();

	glDisable(GL_SMOOTH);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void draw_sign(UINT t) {
	glPushMatrix();
	GLUquadric *qobj;
	qobj = gluNewQuadric();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.1, 0.1, 0.1);
	gluCylinder(qobj, 0.1, 0.1, 10, 32, 70);
	glPopMatrix();

	glTranslatef(0, 10, 0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, t);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2, 0, 0);//1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);//0 0
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 2, 0);// 0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2, 2, 0);// 1 1
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_SMOOTH);

	glPopMatrix();
}


enum doorstate {
	roll_up, roll_down, stop
};
doorstate door = stop;
float rolldoor = 0;

void draw_garage(int width, int height, UINT building, UINT roof, UINT front, UINT lights, UINT land) {
	glPushMatrix();

	//top roof
	glPushMatrix();
	glTranslated(0, height, 0);
	mall2(width + 4, 2, roof);
	glPopMatrix();

	if (night == 1) {
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, Light_Specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Light_Spot_direction1);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, Light_CutOff1);
	}

	//side lights
	{
		glPushMatrix();
		glTranslated(width - 2, (height / 2) + 6, -width - 1);
		glRotated(90, 1, 0, 0);
		mall2(1.5, 2, lights);
		glColor3f(1, 1, 1);
		draw_sphere(0, 0, 0, 0.5);
		glPopMatrix();

		glPushMatrix();
		glTranslated(-width + 2, (height / 2) + 6, -width - 1);
		glRotated(90, 1, 0, 0);
		mall2(1.5, 2, lights);
		glColor3f(1, 1, 1);
		draw_sphere(0, 0, 0, 0.5);
		glPopMatrix();

	}



	glEnable(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);


	//glBindTexture(GL_TEXTURE_2D, t2);
	//glColor3f(1, 1, 1);
	//glBegin(GL_QUADS);
	////top
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(width+3, height, -width); //1 0
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-width-3, height, -width); //0 0
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-width-3, height, width);// 0 1
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(width+3, height, width);//1 1
	//glEnd();

	glBindTexture(GL_TEXTURE_2D, front);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	//front roll door

	if (door == roll_up)
	{
		rolldoor += 0.37;
		if (rolldoor > height) { door = stop; }
	}

	else if (door == roll_down)
	{
		rolldoor = rolldoor - 0.37;
		if (rolldoor < 0.1) { door = stop; }
	}
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width - 4, rolldoor, -width);//1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width + 4, rolldoor, -width);//0 0
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width + 4, height, -width);// 0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width - 4, height, -width);// 1 1
	glEnd();

	glBindTexture(GL_TEXTURE_2D, building);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	//front edge1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, 0, -width);//1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width - 4, 0, -width);//0 0
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width - 4, height, -width);// 0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, -width);// 1 1
	glEnd();

	glBindTexture(GL_TEXTURE_2D, building);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glPushMatrix();
	//front edge2
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width + 4, 0, -width);//1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, 0, -width);//0 0
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, -width);// 0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width + 4, height, -width);// 1 1
	glPopMatrix();
	glEnd();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, land);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	//bottom
	glTexCoord2f(2.0f, 2.0f); glVertex3f(width, 0.2, width);//1 1
	glTexCoord2f(0.0f, 2.0f); glVertex3f(-width, 0.2, width);//0 1
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, 0.2, -width);//0 0
	glTexCoord2f(2.0f, 0.0f); glVertex3f(width, 0.2, -width);//1 0
	glEnd();


	glBindTexture(GL_TEXTURE_2D, building);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	//								 //bottom
	//glVertex3f(width, 0.2, width);//1 1
	//glVertex3f(-width, 0.2, width);//0 1
	//glVertex3f(-width, 0.2, -width);//0 0
	//glVertex3f(width, 0.2, -width);//1 0

	//back
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height, width);//0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, height, width);// 1 1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, 0, width);//1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, 0, width);//0 0

														  //left
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, width);//0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, height, -width);//1 1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, 0, -width);// 1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, 0, width);//0 0

														   //right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height, -width);//0 1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, width);//1 1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, 0, width);//1 0
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, 0, -width);//0 0

	glEnd();
	glDisable(GL_SMOOTH);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//Yassarooooooo

void cube(float x, float y, float z, float r, float g, float b)
{
	glBegin(GL_QUADS);
	//up
	glColor3f(1, 0, 0);
	glVertex3f(x/2, y/2, z/2);
	glVertex3f(-x/2, y/2, z/2);
	glVertex3f(-x/2, y/2, -z/2);
	glVertex3f(x/2, y/2, -z/2);

	//arm1 Bottom face
	glColor3f(0, 1, 0);
	glVertex3f(x / 2, -y / 2, z / 2);
	glVertex3f(-x / 2, -y / 2, z / 2);
	glVertex3f(-x / 2, -y / 2, -z / 2);
	glVertex3f(x / 2, -y / 2, -z / 2);
	//arm1 Front face
	glColor3f(0, 0, 1);
	glVertex3f(x/2, y/2, -z/2);
	glVertex3f(-x/2, y/2, -z/2);
	glVertex3f(-x/2, -y/2, -z/2);
	glVertex3f(x/2, -y/2, -z/2);

	//arm1 Back face
	glColor3f(1, 1, 0);
	glVertex3f(x / 2, y / 2, z / 2);
	glVertex3f(-x / 2, y / 2, z / 2);
	glVertex3f(-x / 2, -y / 2, z / 2);
	glVertex3f(x / 2, -y / 2, z / 2);
	//arm1 Left face
	glColor3f(1, 0, 1);
	glVertex3f(-x/2, y/2, z/2);
	glVertex3f(-x/2, y/2, -z/2);
	glVertex3f(-x/2, -y/2, -z/2);
	glVertex3f(-x/2, -y/2, z/2);
	//arm1 Right face
	glColor3f(0, 1, 1);
	glVertex3f(x / 2, y / 2, z / 2);
	glVertex3f(x / 2, y / 2, -z / 2);
	glVertex3f(x / 2, -y / 2, -z / 2);
	glVertex3f(x / 2, -y / 2, z / 2);
	glEnd();
}

double Car::traction(){
	double ret = 0;
	if ((keys['W'] && !keys['S'])){
		if (currentgear == 6)//lazm y62 al mo7rk
			currentgear = 0;
		double rpm = eng->getrpm(v[0], finalgear, gears[currentgear], frontwheels[0].getwheelradius());
		automaticgear(rpm);
		rpm = eng->getrpm(v[0], finalgear, gears[currentgear], frontwheels[0].getwheelradius());
		ret = eng->gettorque(rpm * finalgear * gears[currentgear] / frontwheels[0].getwheelradius());
		for (int i = 0; i < 2; i++){
			frontwheels[i].calwheelspeed(eng->getrpm(v[0], finalgear, gears[currentgear], frontwheels[0].getwheelradius()), finalgear, gears[currentgear]);
			rearwheels[i].calwheelspeed(eng->getrpm(v[0], finalgear, gears[currentgear], frontwheels[0].getwheelradius()), finalgear, gears[currentgear]);
		}
	}
	else if ((keys['S'] && !keys['W'])){
		currentgear = 6;
		ret -= eng->gettorque(eng->getrpm(frontwheels[0].getwheelspeed(), finalgear, gears[currentgear], frontwheels[0].getwheelradius()) * finalgear * gears[currentgear] / frontwheels[0].getwheelradius());
		for (int i = 0; i < 2; i++){
			frontwheels[i].calwheelspeed(eng->getrpm(frontwheels[0].getwheelspeed(), finalgear, gears[currentgear], frontwheels[0].getwheelradius()), finalgear, gears[currentgear]);
			rearwheels[i].calwheelspeed(eng->getrpm(frontwheels[0].getwheelspeed(), finalgear, gears[currentgear], frontwheels[0].getwheelradius()), finalgear, gears[currentgear]);
		}
	}
	return ret;
}

double Car::breakforce(int axis){
	if (keys[32]&&v[axis]!=0){
		return cb*v[axis] / abs(v[axis]);
	}
	return 0;
}


void Car::movecar(){
	int sign0 = 0;
	if (v[0] != 0){
		sign0 = v[0] / abs(v[0]);
	}
	int sign1 = 0;
	if (v[1] != 0){
		sign1 = v[1] / abs(v[1]);
	}
	if (keys['D']){
		frontwheels[0].turnright();
		frontwheels[1].turnright();
	}
	if (keys['A']){
		frontwheels[0].turnleft();
		frontwheels[1].turnleft();
	}
	if (!keys['A'] && !keys['D']){
		frontwheels[0].turntonormal();
		frontwheels[1].turntonormal();
	}
	double totalforcelong = 0;
	totalforcelong += traction();
	totalforcelong -= airresistance(0);
	totalforcelong -= fraction(0);
	totalforcelong -= weight();
	totalforcelong -= breakforce(0);
	acceleration[0] = totalforcelong / mass;
	v[0] += acceleration[0] * dt;
	if (v[0] != 0 && sign0 != v[0] / abs(v[0]) && sign0){
		v[0] = 0;
		omega = 0;
	}
	if (v[0] != 0){
	double totalforcelat = 0;
	double cartorque = 0;
	totalforcelat -= airresistance(1);
	totalforcelat -= fraction(1);
	totalforcelat -= breakforce(1);
	totalforcelat += lateralforce(calrearslipangle())*c;
	totalforcelat += cos(frontwheels[0].getdelta()) * lateralforce(calfrontslipangle()) * b;
	cartorque = totalforcelat;
	double radius = 0;
	if (frontwheels[0].getdelta() != 0)
		radius = length / sin(frontwheels[0].getdelta());
	double idelta = mass * radius * radius;
	totalforcelat -= lateralforce(calfrontslipangle())*cos(frontwheels[0].getdelta());
	acceleration[1] = totalforcelat / mass;
	v[1] += dt*acceleration[1];

	if (v[1] != 0 && sign1 != v[1] / abs(v[1]) && sign1){
		v[1] = 0;
		omega = 0;
	}
	if (v[0] != 0)
		carPos += (float)(v[0] * dt) * carFront;
	//if (v[1] != 0)
	//	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (float)(v[1] * dt);
	if (frontwheels[0].getdelta() != 0){
		if (idelta)
			angularacceleration = cartorque / idelta;
		else
			angularacceleration = 0;
		omega += angularacceleration*dt;
		yaw += omega*dt;
	}
	else{
		omega = 0;
	}
	glm::vec3 front;
		front.x = cos(glm::radians(yaw))*cos(glm::radians(theta));
		front.y = sin(glm::radians(theta));
		front.z = sin(glm::radians(yaw))*cos(glm::radians(theta));
		carFront = glm::normalize(front);
		carRight = glm::normalize(glm::cross(carFront, up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		carUp = glm::normalize(glm::cross(carRight, carFront));
	}
	if (carPos.z >= 100 && carPos.z <= 150 && carPos.x >= -15 && carPos.x <= 15){
		if (yaw < 180 && yaw > 0)
			theta = 3.4336303624505220749169491700816;
		else
			theta = -3.4336303624505220749169491700816;
	}
	else if (carPos.z >= 200 && carPos.z <= 250 && carPos.x >= -15 && carPos.x <= 15){
		if (yaw < 180 && yaw > 0)
			theta = -3.4336303624505220749169491700816;
		else
			theta = 3.4336303624505220749169491700816;
	}
	else
		theta = 0;
}


void Car::drawcar(){

	glPushMatrix();
	glTranslated(carPos.x, carPos.y, carPos.z);
	glRotated(-yaw, 0, 1, 0);
	glRotated(theta, 0, 0, 1);
	//cube(5, 5, 5, 0, 0, 0);
	model->scale = 1.5;
	model->Draw();
	glPopMatrix();
}

ref class managedGlobal{
public:
	static Project1::GUI^ form;
};

Car ca;
Camera cam;

void form()
{
	msclr::interop::marshal_context context;
	if (managedGlobal::form != nullptr){
		std::string rhoo = context.marshal_as<std::string>(managedGlobal::form->rho->Text);
		if (rhoo != ""&&std::stod(rhoo))
			ca.setrho(std::stod(rhoo));
	}
	else
		ca.setrho(1.64);
	if (managedGlobal::form != nullptr){
		std::string gra = context.marshal_as<std::string>(managedGlobal::form->gravity->Text);
		if (gra != ""&&std::stod(gra))
			ca.setgravity(std::stod(gra));
	}
	else
		ca.setgravity(10);
	if (managedGlobal::form != nullptr){
		std::string rw = context.marshal_as<std::string>(managedGlobal::form->wheelRadius->Text);
		if (rw != ""&&std::stod(rw))
			ca.setwheel(std::stod(rw));
	}
	else
		ca.setmass(19.5);
	if (managedGlobal::form != nullptr){
		std::string masss = context.marshal_as<std::string>(managedGlobal::form->mass->Text);
		if (masss != ""&&std::stod(masss))
			ca.setmass(std::stod(masss));
	}
	else
		ca.setmass(500);
	if (managedGlobal::form != nullptr){
		std::string areaa = context.marshal_as<std::string>(managedGlobal::form->frontarea->Text);
		if (areaa != ""&&std::stod(areaa))
			ca.setarea(std::stod(areaa),0);
	}
	else
		ca.setmass(2);
	if (managedGlobal::form != nullptr){
		std::string areaa = context.marshal_as<std::string>(managedGlobal::form->sidear->Text);
		if (areaa != ""&&std::stod(areaa))
			ca.setarea(std::stod(areaa), 1);
	}
	else
		ca.setmass(2);
	if (managedGlobal::form != nullptr){
		std::string cdd = context.marshal_as<std::string>(managedGlobal::form->cd->Text);
		if (cdd != ""&&std::stod(cdd))
			ca.setcd(std::stod(cdd));
	}
	else
		ca.setmass(0.35);
	if (managedGlobal::form != nullptr){
		std::string crr = context.marshal_as<std::string>(managedGlobal::form->cr->Text);
		if (crr != ""&&std::stod(crr))
			ca.setcr(std::stod(crr));
	}
	else
		ca.setmass(0.1);
	if (managedGlobal::form != nullptr){
		std::string cbb = context.marshal_as<std::string>(managedGlobal::form->cb->Text);
		if (cbb != ""&&std::stod(cbb))
			ca.setcb(std::stod(cbb));
	}
	else
		ca.setmass(5000);
	if (managedGlobal::form != nullptr){
		std::string length = context.marshal_as<std::string>(managedGlobal::form->l->Text);
		if (length != ""&&std::stod(length))
			ca.setLength(std::stod(length));
	}
	else
		ca.setmass(2);
	if (managedGlobal::form != nullptr){
		std::string cca = context.marshal_as<std::string>(managedGlobal::form->ca->Text);
		if (cca != ""&&std::stod(cca))
			ca.setca(std::stod(cca));
	}
	else
		ca.setmass(867);
}

void DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	form();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Mayytrix

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Sphere_Ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Sphere_Diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Sphere_Specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Sphere_Shininess);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_Specular);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light_Spot_direction);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);

	cam.setcam(ca.getpos(),ca.getfro(),ca.getup());
	cam.lookCamera();

	ca.movecar();
	ca.drawcar();

	/*glPushMatrix();
	glTranslated(0, -3, -20);
	cube(5, 5, 5,  0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -3, 20);
	cube(5, 5, 5, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(20, -3, 0);
	cube(5, 5, 5, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, -3, 0);
	cube(5, 5, 5, 0, 0, 0);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, -2, 100);
	glBegin(GL_QUADS);
	//up
	glColor3f(1,1 , 0);
	glVertex3f(-15, 0, 0);
	glVertex3f(15, 0, 0);
	glVertex3f(15, 3, 50);
	glVertex3f(-15,3, 50);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -2, 200);
	glBegin(GL_QUADS);
	//up
	glColor3f(1, 1, 0);
	glVertex3f(-15, 3, 0);
	glVertex3f(15, 3, 0);
	glVertex3f(15, 0, 50);
	glVertex3f(-15, 0, 50);
	glEnd();
	glPopMatrix();


	glColor3f(1, 1, 1);
	skybox();

	glPushMatrix();
	glTranslated(-250, -3, -150);
	glRotated(-90, 0, 1, 0);
	glPushMatrix();
	glTranslated(0, 3.5, -125);
	draw_road(18, 90);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(-423, 20, 0);

	glPushMatrix();
	glTranslated(225, -19.2, 0);
	glRotated(90, 0, 1, 0);
	draw_floor2(75, 170);*/

	/*
	for (int i = -100; i < 150; i += 20) {
		glPushMatrix();
		glTranslatef(-76, -1, i);
		draw_tree();
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(76, -1, i);
		draw_tree();
		glColor3f(1, 1, 1);
		glPopMatrix();

	}*/

	/*for (int i = -100; i < 150; i += 30) {
		glPushMatrix();
		glTranslatef(-76, -1, i);
		draw_light();
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(76, -1, i);
		draw_light();
		glColor3f(1, 1, 1);
		glPopMatrix();

	}*/
	glPopMatrix();

	//buildings
	/*{
		glPushMatrix();
		glTranslatef(-900, -3, -550);
		mall2(10, 50, texture[10]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-950, -3, 1000);
		glRotated(30, 0, 1, 0);
		mall2(15, 100, texture[13]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-185, -3, -350);
		mall2(15, 70, texture[11]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-85, -3, -800);
		mall2(15, 70, texture[13]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-155, -3, -250);
		mall2(10, 85, texture[11]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-105, -3, 300);
		mall2(10, 120, texture[11]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-500, -3, 700);
		glRotated(-30, 0, 1, 0);
		mall2(20, 40, texture[12]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-50, -3, 550);
		glRotated(-30, 0, 1, 0);
		mall2(20, 40, texture[12]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-550, -3, -700);
		glRotated(-30, 0, 1, 0);
		mall2(20, 40, texture[12]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-685, -3, 0);
		mall2(15, 70, texture[11]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-250, -3, 700);
		glRotated(30, 0, 1, 0);
		mall2(15, 100, texture[13]);
		glPopMatrix();

		glPopMatrix();
	}
*/

	//road
	glPushMatrix();
	draw_road(20, 1000);
	glPopMatrix();

	//grass
	glPushMatrix();
	glTranslated(10, 0, 0);
	draw_grass();
	glPopMatrix();

	//floor
	glPushMatrix();
	glTranslated(-10, 0, 0);
	draw_floor();
	glPopMatrix();

	//Street Lights
	glPushMatrix();
	for (int i = -300; i < 300; i += 25) {
		glPushMatrix();
		glTranslatef(21, -3, 0);
		glTranslatef(0, 0, i);
		draw_light();
		glPopMatrix();

	}
	glPopMatrix();

	//lights
	glPushMatrix();
	glTranslatef(-21, -3, -20);
	draw_light();
	glTranslatef(0, 0, 40);
	draw_light();
	glPopMatrix();

	//traffic
	{
		glPushMatrix();
		glTranslatef(-21, -3, -30);
		draw_traffic_signal();
		glPopMatrix();

	//	//traffic signal 2
		glPushMatrix();
		glTranslatef(21, -3, 27);
		glRotatef(180, 0, 1, 0);
		draw_traffic_signal();
		glPopMatrix();
	}

	//trees
	glPushMatrix();
	for (int i = -200; i < 200; i += 30) {
		glPushMatrix();
		glTranslatef(25, -1, i);
		draw_tree();
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(45, -1, i + 10);
		draw_tree();
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(65, -1, i + 15);
		draw_tree();
		glColor3f(1, 1, 1);
		glPopMatrix();

	}
	glPopMatrix();





	glFlush();											// Done Drawing The Quad	

	//DO NOT REMOVE THIS
	SwapBuffers(hDC);
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
													if (!HIWORD(wParam))					// Check Minimization State
													{
														active = TRUE;						// Program Is Active
													}
													else
													{
														active = FALSE;						// Program Is No Longer Active
													}

													return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
													switch (wParam)							// Check System Calls
													{
													case SC_SCREENSAVE:					// Screensaver Trying To Start?
													case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
														return 0;							// Prevent From Happening
													}
													break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
													PostQuitMessage(0);						// Send A Quit Message
													return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
													keys[wParam] = TRUE;					// If So, Mark It As TRUE
													return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
													keys[wParam] = FALSE;					// If So, Mark It As FALSE
													return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
													ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
													return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	managedGlobal::form = gcnew Project1::GUI;
	System::Threading::Thread^ th1 = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(managedGlobal::form, &Project1::GUI::show_th));
	th1->Start();

	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL Window", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer = SetTimer(hWnd, 0, 50, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (GetKeyState('L') & 0x80) {
			if (night == 0)
			{
				night = 1;
				day = false;
			}
			else if (night == 1) {
				night = 0;
				day = true;
			}
		}
	}


	return 0;

}
