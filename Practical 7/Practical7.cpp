#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL, hBMP2 = NULL, hBMP3 = NULL;

float rotate = 0;
int changeTexture = 1, question = 0;

float tz = 0.0, z = -2.0, rspeed = 0.012, px = 0, py = 0, openAngle = 0;
boolean isortho = true, open = false, r = 0, isRotate = false;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		if (wParam == 0x31) question = 1;
		if (wParam == 0x32) question = 2;
		if (wParam == 0x33) question = 3;
		if (wParam == 0x34) question = 4;
		if (wParam == 'R') {
			isRotate = !isRotate;
			if (isRotate)
				rotate += 1;
			else
				rotate = 0;
		}
		if (wParam == VK_NUMPAD1) changeTexture = 1;
		if (wParam == VK_NUMPAD2) changeTexture = 2;
		if (wParam == VK_NUMPAD3) changeTexture = 3;
		else if (wParam == 'V') {
			if (isortho) {
				isortho = false;
			}
			else {
				isortho = true;
			}
		}
		else if (wParam == VK_SPACE) {
			tz = 0;
			z = -2;
		}
		else if (wParam == 'O') {
			open = !open;
		}
		else  if (wParam == 'W') {
			if (py > -1) py += 0.1;
		}
		else  if (wParam == 'S') {
			if (py < 1) py -= 0.1;
		}
		else  if (wParam == 'A') {
			if (px < 1) px -= 0.1;
		}
		else  if (wParam == 'D') {
			if (px > -1) px += 0.1;
		}
		else if (wParam == VK_LEFT) {
			r -= 5;
		}
		else if (wParam == VK_RIGHT) {
			r += 5;
		}

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

//Texture Intialize
GLuint loadTexture(LPCSTR filename) {
	//Take from step 1
	GLuint texture = 0;        //texture name

	//Step 3: Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);    //Unpack bitmap file
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	//Step 4: Assign texture to polygon
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Take from step 5
	DeleteObject(hBMP);
	return texture;
}

//Example 1
void draw2DQuads() {

	//RIGHT QUADS
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 1);
	glBegin(GL_QUADS);
	// BOTTOM LEFT OF QUAD
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.1, 0.1, 0);

	// BOTTOM RIGHT OF QUAD
	glTexCoord2f(0.0f, 1);
	glVertex3f(0.5, 0.1, 0);

	// TOP RIGHT OF QUAD
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, 0);

	// TOP LEFT OF QUAD
	glTexCoord2f(1, 0.0f);
	glVertex3f(0.1, 0.5, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	//LEFT QUADS

	glBegin(GL_QUADS);
	glVertex3f(-0.1, 0.1, 0);
	glVertex3f(-0.5, 0.1, 0);
	glVertex3f(-0.5, 0.5, 0);
	glVertex3f(-0.1, 0.5, 0);
	glEnd();
}

//Question 1
void draw3DPyramid(float value1, float value2) {

	// value1 = 0.3
	// value2 = 0.6

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	texture = loadTexture("Brick.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);

	glRotatef(1, 0, 0, 1);
	glBegin(GL_TRIANGLES);

	//Front
	glTexCoord3f(1, 0, 0);
	glVertex3f(-value1, 0, 0);
	glTexCoord3f(0, 0, 0);
	glVertex3f(value1, 0, 0);
	glTexCoord3f(0, 1, 0);
	glVertex3f(0, value2, value1);

	//Left
	glTexCoord3f(0, 0, 0);
	glVertex3f(-value1, 0, 0);
	glTexCoord3f(1, 0, 1);
	glVertex3f(-value1, 0, value2);
	glTexCoord3f(0, 1, 1);
	glVertex3f(0, value2, value1);

	//Back
	glTexCoord3f(0, 1, 1);
	glVertex3f(0, value2, value1);
	glTexCoord3f(1, 0, 1);
	glVertex3f(-value1, 0, value2);
	glTexCoord3f(0, 0, 1);
	glVertex3f(value1, 0, value2);

	//Right
	glTexCoord3f(0, 1, 1);
	glVertex3f(0, value2, value1);
	glTexCoord3f(1, 0, 1);
	glVertex3f(value1, 0, value2);
	glTexCoord3f(0, 0, 0);
	glVertex3f(value1, 0, 0);
	glEnd();

	//Base
	glBegin(GL_QUADS);
	glTexCoord3f(0, 0, 0);
	glVertex3f(-value1, -0.01, 0);
	glTexCoord3f(0, 1, 1);
	glVertex3f(-value1, -0.01, value2);
	glTexCoord3f(1, 1, 1);
	glVertex3f(value1, -0.01, value2);
	glTexCoord3f(1, 0, 0);
	glVertex3f(value1, -0.01, 0);


	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glDeleteTextures(1, &texture);

}

//Question 2
void draw3DCube(float sz, GLuint texture) {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	//Face 1 : Bottom
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, 0.0f, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	//Face 2 : Left 
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);

	//Face 3 : Front 
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, sz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, sz);

	//Face 4 : Right
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, sz, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);

	//Face 5 : Back 
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, sz, 0.0f);

	//Face 6 : Top 
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, sz, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, sz, sz);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &texture);

}

//Question 3 Ice Cream
void drawCone()
{
	GLUquadricObj* cone = gluNewQuadric();
	gluQuadricTexture(cone, true);

	texture = loadTexture("iceCone.bmp");
	glPushMatrix();
	glRotatef(90, -1, 0, 0);
	glTranslatef(0, 0, -0.7);

	//draw Cone

	//Outside cone
	glBindTexture(GL_TEXTURE_2D, texture);
	gluQuadricDrawStyle(cone, GLU_LINE);
	gluCylinder(cone, 0, 0.25, 0.7, 15, 5);
	//Inside cone
	gluQuadricDrawStyle(cone, GLU_FILL);
	gluCylinder(cone, 0, 0.25, 0.7, 15, 5);
	glPopMatrix();

	gluDeleteQuadric(cone);
	glDeleteTextures(1, &texture);
}
void drawSphere()
{
	GLUquadricObj* sphere = gluNewQuadric();

	//draw Green Sphere
	gluQuadricTexture(sphere, true);
	texture = loadTexture("iceChoco.bmp");

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, 0.23, 100, 100);
	glPopMatrix();
	glDeleteTextures(1, &texture);

	texture = loadTexture("iceVanila.bmp");
	//draw Grey Sphere
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture);
	glTranslatef(0, 0.25, 0);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, 0.21, 100, 100);
	glPopMatrix();

	gluDeleteQuadric(sphere);
	glDeleteTextures(1, &texture);

}
void drawDisk()
{
	GLUquadricObj* disk = gluNewQuadric();
	gluQuadricTexture(disk, true);
	texture = loadTexture("iceVanila.bmp");

	//draw PartialDisk
	glPushMatrix();
	glTranslatef(-0.12, 0.4, 0);

	glBindTexture(GL_TEXTURE_2D, texture);

	//Inner
	gluPartialDisk(disk, 0.09, 0.10, 100, 10, 200, 270);

	//Outer
	gluPartialDisk(disk, 0.085, 0.105, 1000, 1, 220, 190);
	glPopMatrix();
	gluDeleteQuadric(disk);
	glDeleteTextures(1, &texture);
}
void drawCylinder()
{
	GLUquadricObj* cylinder = gluNewQuadric();
	gluQuadricTexture(cylinder, true);
	texture = loadTexture("chocolate.bmp");

	glPushMatrix();
	glRotatef(70, -1, 0, -0.4);
	glTranslatef(-0.05, 0, 0.25);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.03, 0.03, 0.5, 10, 10);
	glPopMatrix();
	gluDeleteQuadric(cylinder);
	glDeleteTextures(1, &texture);

}
void drawCherry()
{
	GLUquadricObj* cherry = gluNewQuadric();
	gluQuadricTexture(cherry, true);
	texture = loadTexture("cherry.bmp");

	//cherry body
	glPushMatrix();
	glRotatef(70, 0, 1, -1);
	glTranslatef(-0.2, 0.4, 0);

	glBindTexture(GL_TEXTURE_2D, texture);
	gluQuadricDrawStyle(cherry, GLU_FILL);
	gluSphere(cherry, 0.06, 30, 30);
	glPopMatrix();

	//cherry head
	glPushMatrix();
	glTranslatef(0.3, 0.4, 0);
	gluQuadricDrawStyle(cherry, GLU_FILL);
	gluPartialDisk(cherry, 0.09, 0.099, 100, 10, 280, 120);
	glPopMatrix();
	gluDeleteQuadric(cherry);
	glDeleteTextures(1, &texture);
}

//Question 4 London Bridge
void sphere(float rad, int h, int v) {
	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, rad, h, v);
	gluDeleteQuadric(sphere);
}
void cylinder(float bot, float top, float height, int h, int v, LPCSTR filename) {
	GLUquadricObj* cylinder = gluNewQuadric();
	gluQuadricTexture(cylinder, true);
	texture = loadTexture(filename);

	gluQuadricDrawStyle(cylinder, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluCylinder(cylinder, bot, top, height, h, v);		//draw cylinder
	gluDeleteQuadric(cylinder);
	glDeleteTextures(1, &texture);
}
void cylinderLine(float bot, float top, float height, int h, int v) {
	GLUquadricObj* cylinderLine = gluNewQuadric();
	gluQuadricDrawStyle(cylinderLine, GLU_LINE);
	gluCylinder(cylinderLine, bot, top, height, h, v);		//draw cylinder
	gluDeleteQuadric(cylinderLine);
}
void cube(float length, float height, float width) {
	glBegin(GL_QUADS);

	// Face 1 / Bottom
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, width);
	glTexCoord2f(1, 1);
	glVertex3f(length, 0.0f, width);
	glTexCoord2f(1, 0);
	glVertex3f(length, 0.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 / Left
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, height, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, height, width);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, width);

	// Face 3 / Front
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, height, 0);
	glTexCoord2f(1, 0);
	glVertex3f(length, height, 0);
	glTexCoord2f(0, 0);
	glVertex3f(length, 0.0f, 0);

	// Face 4 / Right
	glTexCoord2f(0, 1);
	glVertex3f(length, 0.0f, 0);
	glTexCoord2f(1, 1);
	glVertex3f(length, height, 0);
	glTexCoord2f(1, 0);
	glVertex3f(length, height, width);
	glTexCoord2f(0, 0);
	glVertex3f(length, 0.0f, width);

	// Face 5 / Back
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.0f, width);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, height, width);
	glTexCoord2f(1, 0);
	glVertex3f(length, height, width);
	glTexCoord2f(0, 0);
	glVertex3f(length, 0, width);

	// Face 6 / Top
	glTexCoord2f(0, 1);
	glVertex3f(0, height, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(length, height, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(length, height, width);
	glTexCoord2f(0, 0);
	glVertex3f(0, height, width);
	glEnd();

}
void cubeLine(float length, float height, float width) {
	glBegin(GL_LINE_LOOP);
	// Face 1 / Bottom
	glVertex3f(0.0f, 0.0f, width);
	glVertex3f(length, 0.0f, width);
	glVertex3f(length, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 / Left
	glVertex3f(0, 0.0f, 0.0f);
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(0.0f, height, width);
	glVertex3f(0, 0, width);

	// Face 3 / Front
	glVertex3f(0.0f, 0.0f, 0);
	glVertex3f(0.0f, height, 0);
	glVertex3f(length, height, 0);
	glVertex3f(length, 0.0f, 0);

	// Face 4 / Right
	glVertex3f(length, 0.0f, 0);
	glVertex3f(length, height, 0);
	glVertex3f(length, height, width);
	glVertex3f(length, 0.0f, width);

	// Face 5 / Back
	glVertex3f(0, 0.0f, width);
	glVertex3f(0.0f, height, width);
	glVertex3f(length, height, width);
	glVertex3f(length, 0, width);

	// Face 6 / Top
	glVertex3f(0, height, 0.0f);
	glVertex3f(length, height, 0.0f);
	glVertex3f(length, height, width);
	glVertex3f(0, height, width);
	glEnd();
}


void projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glTranslatef(px, py, 0);
	glRotatef(r, 0, 1, 0);
	glRotatef(2, 1, 0, 0);

	if (isortho) {
		glOrtho(-5, 5, -5, 5, -5, 5);
	}
	else {
		//gluPerspective(10, 1, -1, 20);
		glFrustum(-2, 2, -2, 2, 1, 11);
	}
}
void leftBuild() {
	glEnable(GL_TEXTURE_2D);

#pragma region basement
	glPushMatrix();

	glTranslatef(-2.75, -2, 0);
	cubeLine(1.5, 1, 1.5);
	texture = loadTexture("wall.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	cube(1.5, 1, 1.5);
	glDeleteTextures(1, &texture);
	glPopMatrix();
#pragma endregion basement

#pragma region body
	glPushMatrix();
	texture = loadTexture("window.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glTranslatef(-2.5, 0, 0.3);
	cubeLine(1, 2, 1);
	cube(1, 2, 1);
	glDeleteTextures(1, &texture);
	glPopMatrix();
#pragma endregion body

#pragma region bodyDesign
	glPushMatrix();
	texture = loadTexture("bodydesign.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glTranslatef(-2.6, 1.25, 0.3);
	cube(1.2, 0.2, 1.2);
	cubeLine(1.2, 0.2, 1.2);
	glDeleteTextures(1, &texture);
	glPopMatrix();

	glPushMatrix();
	texture = loadTexture("bodydesign.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glTranslatef(-2.6, 0.5, 0.3);
	cube(1.2, 0.2, 1.2);
	cubeLine(1.2, 0.2, 1.2);
	glDeleteTextures(1, &texture);
	glPopMatrix();
#pragma endregion bodyDesign

#pragma region pillars

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-2.6, 1.3, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-1.4, 1.3, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-2.6, 0.2, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-1.4, 0.2, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "wall.bmp");
	glPopMatrix();
#pragma endregion pillars

#pragma region topCones

	//Top 4 small cones
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-2.6, -1.3, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-1.4, -1.3, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-2.6, -0.2, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-1.4, -0.2, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "wall.bmp");
	glPopMatrix();

	//Top Big cone
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-2, -0.7, 2);
	cylinder(0.6, 0, 1, 20, 1, "wall.bmp");
	glPopMatrix();

#pragma endregion topCones
	glDisable(GL_TEXTURE_2D);

}
void rightBuild() {
	glEnable(GL_TEXTURE_2D);
#pragma region basement
	glPushMatrix();
	glTranslatef(2.75, -2, 0);
	cubeLine(1.5, 1, 1.5);
	texture = loadTexture("wall.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	cube(1.5, 1, 1.5);
	glDeleteTextures(1, &texture);
	glPopMatrix();

#pragma endregion basement

#pragma region body
	glPushMatrix();
	texture = loadTexture("window.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glTranslatef(3, 0, 0.3);
	cubeLine(1, 2, 1);
	cube(1, 2, 1);
	glDeleteTextures(1, &texture);
	glPopMatrix();
#pragma endregion body

#pragma region bodyDesign
	glPushMatrix();
	texture = loadTexture("bodydesign.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glTranslatef(2.9, 1.25, 0.3);
	cube(1.2, 0.2, 1.2);
	cubeLine(1.2, 0.2, 1.2);
	glDeleteTextures(1, &texture);
	glPopMatrix();

	glPushMatrix();
	texture = loadTexture("bodydesign.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glTranslatef(2.9, 0.5, 0.3);
	cube(1.2, 0.2, 1.2);
	cubeLine(1.2, 0.2, 1.2);
	glDeleteTextures(1, &texture);
	glPopMatrix();
#pragma endregion bodyDesign

#pragma region pillars
	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(2.9, 1.3, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(4.1, 1.3, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(2.9, 0.2, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(4.1, 0.2, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "wall.bmp");
	glPopMatrix();
#pragma endregion pillars

#pragma region topCones
	//Top 4 small cones
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(2.9, -1.3, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(4.1, -1.3, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(2.9, -0.2, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(4.1, -0.2, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "wall.bmp");
	glPopMatrix();

	//Top Big cone
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(3.5, -0.7, 2);
	cylinder(0.6, 0, 1, 20, 1, "wall.bmp");
	glPopMatrix();
#pragma endregion topCones
	glDisable(GL_TEXTURE_2D);
}
void bridge() {
	glEnable(GL_TEXTURE_2D);
#pragma region topBridge
	glPushMatrix();
	texture = loadTexture("bridge.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glTranslatef(-1.5, 1, 0.4);
	cube(5, 0.4, 0.8);
	glDeleteTextures(1, &texture);
	glPopMatrix();
#pragma endregion topBridge

#pragma region bridge
	texture = loadTexture("bridge.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);

	//left bridge
	glPushMatrix();
	glTranslatef(-4.7, -1.2, 0);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.25, -1.2, 0);
	glRotatef(openAngle, 0, 0, 1);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	//right bridge
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-6.2, -1.2, -1.5);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-2.75, -1.2, -1.5);
	glRotatef(openAngle, 0, 0, 1);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	glDeleteTextures(1, &texture);

	if (open) {
		if (openAngle < 45)
			openAngle += 0.4;
	}
	else {
		if (openAngle > 0)
			openAngle -= 0.4;
	}
#pragma endregion bridge

#pragma region water

	texture = loadTexture("sea.bmp");
	glPushMatrix();
	glTranslatef(-5, -6, -6);
	cube(10, 4, 10);
	glPopMatrix();
#pragma endregion water
	glDisable(GL_TEXTURE_2D);
}
void sky() {
	texture = loadTexture("sky.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	glTranslatef(-5, -5, -6);
	draw3DCube(30, texture);
	glPopMatrix();
	glDeleteTextures(1, &texture);
}

void drawBridge() {
	if (tz > 360)
		tz -= 360;
	tz += rotate;
	projection();

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	if (!isortho) {
		glTranslatef(0, 0, -4);
	}

	leftBuild();
	rightBuild();
	bridge();
	sky();

}


void example() {
	draw2DQuads();
}

void q3() {
	glPushMatrix();
	glRotatef(0.1, 0, 1, 0);
	drawCone();
	drawSphere();
	drawDisk();
	drawCylinder();
	drawCherry();
	glPopMatrix();
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClearColor(0.5, 0.5, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	if (question == 1) {
		//Question 1 Done
		glRotatef(rotate, 1, 1, 1);
		draw3DPyramid(0.3, 0.6);
	}
	else if (question == 2) {
		//Question 2 Done
		glRotatef(rotate, 1, 1, 1);
		draw3DCube(0.5, changeTexture);
		if (changeTexture == 1) {
			texture = loadTexture("Box.bmp");
		}
		else if (changeTexture == 2) {
			texture = loadTexture("Brick.bmp");
		}
		else if (changeTexture == 3) {
			texture = loadTexture("Metal.bmp");
		}
	}
	else if (question == 3) {
		//Question 3 Done
		glEnable(GL_DEPTH_TEST);
		q3();
		glDisable(GL_DEPTH_TEST);
	}
	else if (question == 4) {
		//Question 4
		glEnable(GL_DEPTH_TEST);
		glRotatef(rotate, 0, 1, 0.0);
		drawBridge();
		glDisable(GL_DEPTH_TEST);
	}

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------



	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------