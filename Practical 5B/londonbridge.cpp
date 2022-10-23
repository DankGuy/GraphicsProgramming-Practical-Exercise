#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

float tz = 0.0;

float z = -2.0, rotate = 0, rspeed = 0.2, px = 0, py = 0, openAngle = 0;
boolean isortho = true, open = false, r = 0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 'R') {
			if (rotate != 0) {
				rotate = 0;
			}
			else {
				rotate = rspeed;
			}
		}
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
			r -= 2;
		}
		else if (wParam == VK_RIGHT) {
			r += 2;
		}
		break;

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

	// set pixel format returns whether it successfully set the pixel format
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

void sphere(float rad, int h, int v) {
	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, rad, h, v);		
	gluDeleteQuadric(sphere);
}
void cylinder(float bot, float top, float height, int h, int v) {
	GLUquadricObj* cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, bot, top, height, h, v);		//draw cylinder
	gluDeleteQuadric(cylinder);
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

#pragma region basement
	glPushMatrix();
	glTranslatef(-2.75, -2, 0);
	glColor3f(0, 0, 0);
	cubeLine(1.5, 1, 1.5);
	glColor3f(0.5, 0.5, 0.5);
	cube(1.5, 1, 1.5);
	glPopMatrix();
#pragma endregion basement

#pragma region body
	glPushMatrix();
	glTranslatef(-2.5, 0, 0.3);	
	glColor3f(0, 0, 0);
	cubeLine(1, 2, 1);
	glColor3f(0.80, 0.7, 0.50);
	cube(1, 2, 1);
	glPopMatrix();
#pragma endregion body

#pragma region bodyDesign
	glPushMatrix();
	glTranslatef(-2.6, 1.25, 0.3);
	glColor3f(0.78, 0.66, 0.5);
	cube(1.2, 0.2, 1.2);
	glColor3f(0, 0, 0);
	cubeLine(1.2, 0.2, 1.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.6, 0.5,0.3);
	glColor3f(0.78, 0.66, 0.5);
	cube(1.2, 0.2, 1.2);
	glColor3f(0, 0, 0);
	cubeLine(1.2, 0.2, 1.2);
	glPopMatrix();
#pragma endregion bodyDesign

#pragma region pillars
	
	
	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-2.6, 1.3, -2);
	glColor3f(0.7, 0.6, 0.4);
	cylinder(0.2, 0.2, 3, 25, 1);
	glPopMatrix(); 
	
	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-1.4, 1.3, -2);
	glColor3f(0.7, 0.6, 0.4);
	cylinder(0.2, 0.2, 3, 25, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-2.6, 0.2, -2);
	glColor3f(0.7, 0.6, 0.4);
	cylinder(0.2, 0.2, 3, 25, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-1.4, 0.2, -2);
	glColor3f(0.7, 0.6, 0.4);
	cylinder(0.2, 0.2, 3, 25, 1);
	glPopMatrix();
#pragma endregion pillars

#pragma region topCones

	//Top 4 small cones
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-2.6, -1.3, 2);
	glColor3f(0.5, 0.4, 0.3);
	cylinder(0.2, 0, 0.5, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-1.4, -1.3, 2);
	glColor3f(0.5, 0.4, 0.3);
	cylinder(0.2, 0, 0.5, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-2.6, -0.2, 2);
	glColor3f(0.5, 0.4, 0.3);
	cylinder(0.2, 0, 0.5, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-1.4, -0.2, 2);
	glColor3f(0.5, 0.4, 0.3);
	cylinder(0.2, 0, 0.5, 20, 1);
	glPopMatrix();

	//Top Big cone
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-2, -0.7, 2);
	glColor3f(0.5, 0.4, 0.3);
	cylinder(0.6, 0, 1, 20, 1);
	glPopMatrix();

#pragma endregion topCones
	
}

void rightBuild() {

#pragma region basement
	glPushMatrix();
	glTranslatef(2.75, -2, 0);
	glColor3f(0, 0, 0);
	cubeLine(1.5, 1, 1.5);
	glColor3f(0.5, 0.5, 0.5);
	cube(1.5, 1, 1.5);
	glPopMatrix();
#pragma endregion basement

#pragma region body
	glPushMatrix();
	glTranslatef(3, 0, 0.3);
	glColor3f(0, 0, 0);
	cubeLine(1, 2, 1);
	glColor3f(0.80, 0.7, 0.50);
	cube(1, 2, 1);
	glPopMatrix();
#pragma endregion body

#pragma region bodyDesign
	glPushMatrix();
	glTranslatef(2.9, 1.25, 0.3);
	glColor3f(0.78, 0.66, 0.5);
	cube(1.2, 0.2, 1.2);
	glColor3f(0, 0, 0);
	cubeLine(1.2, 0.2, 1.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.9, 0.5, 0.3);
	glColor3f(0.78, 0.66, 0.5);
	cube(1.2, 0.2, 1.2);
	glColor3f(0, 0, 0);
	cubeLine(1.2, 0.2, 1.2);
	glPopMatrix();
#pragma endregion bodyDesign

#pragma region pillars
	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(2.9, 1.3, -2);
	glColor3f(0.7, 0.6, 0.4);
	cylinder(0.2, 0.2, 3, 25, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(4.1, 1.3, -2);
	glColor3f(0.7, 0.6, 0.4);
	cylinder(0.2, 0.2, 3, 25, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(2.9, 0.2, -2);
	glColor3f(0.7, 0.6, 0.4);
	cylinder(0.2, 0.2, 3, 25, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(4.1, 0.2, -2);
	glColor3f(0.7, 0.6, 0.4);
	cylinder(0.2, 0.2, 3, 25, 1);
	glPopMatrix();
#pragma endregion pillars

#pragma region topCones
	//Top 4 small cones
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(2.9, -1.3, 2);
	glColor3f(0.5, 0.4, 0.3);
	cylinder(0.2, 0, 0.5, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(4.1, -1.3, 2);
	glColor3f(0.5, 0.4, 0.3);
	cylinder(0.2, 0, 0.5, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(2.9, -0.2, 2);
	glColor3f(0.5, 0.4, 0.3);
	cylinder(0.2, 0, 0.5, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(4.1, -0.2, 2);
	glColor3f(0.5, 0.4, 0.3);
	cylinder(0.2, 0, 0.5, 20, 1);
	glPopMatrix();

	//Top Big cone
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(3.5, -0.7, 2);
	glColor3f(0.5, 0.4, 0.3);
	cylinder(0.6, 0, 1, 20, 1);
	glPopMatrix();
#pragma endregion topCones

}

void bridge() {

#pragma region topBridge
	glPushMatrix();
	glTranslatef(-1.5, 1, 0.4);
	glColor3f(0.5, 0.4, 0.3);
	cube(5, 0.4, 0.8);
	glPopMatrix();
	glPopMatrix();
#pragma endregion topBridge

#pragma region bridge
	//left bridge
	glPushMatrix();
	glTranslatef(-4.7, -1.2, 0);
	glColor3f(0.5, 0.4, 0.3);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.25, -1.2, 0);
	glRotatef(openAngle, 0, 0, 1);
	glColor3f(0.5, 0.4, 0.3);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	//right bridge
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-6.2, -1.2, -1.5);
	glColor3f(0.5, 0.4, 0.3);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-2.75, -1.2, -1.5);
	glRotatef(openAngle, 0, 0, 1);
	glColor3f(0.5, 0.4, 0.3);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	if (open) {
		if (openAngle < 45) openAngle += 0.5;
	}
	else {
		if (openAngle > 0) openAngle -= 0.5;
	}
#pragma endregion bridge

#pragma region water
	glPushMatrix();
	glColor3f(0.5, 0.97, 1);
	glTranslatef(-5, -6, -6);
	cube(10, 4, 10);
	glPopMatrix();
#pragma endregion water
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
	glRotatef(tz, 0, 1, 0.0);
	leftBuild();
	rightBuild();
	bridge();
}

void display()
{
	glClearColor(0.53, 0.8, 0.92, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	drawBridge();

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
		CW_USEDEFAULT, CW_USEDEFAULT, 700, 700,
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
