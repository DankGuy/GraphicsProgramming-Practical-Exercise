#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

// #pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 5"

// window procedure acts as something like event listener (listen for message or input), full of switch cases
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		// wParam = window Parameter
		// VK = virtual key
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

double coneBr = 0.0, coneTr = 0.3, coneH = 1.0;
double PI = 3.1429;
double cherryX, cherryY, angle, cherryXPos = 0.0, cherryYPos = 0.0, cherryStickXR = 0.1, cherryStickYR = 0.18;

double rgbDivide(double rgb) {
	return (double)(rgb / 255.0);
}
void drawSphere(double r) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	//gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, r, 30, 30);
	// if do not delete, the program will crash eventually as the object will be incremented by time
	gluDeleteQuadric(sphere);
}
void drawCylinder(double br, double tr, double h) {
	glPushMatrix();
	glRotatef(0.5, 1.0, 1.0, 1.0);
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, br, tr, h, 30, 30);
	// if do not delete, the program will crash eventually as the object will be incremented by time
	gluDeleteQuadric(cylinder);
	glPopMatrix();

}
void drawDisk(double inner, double outer) {
	GLUquadricObj* disk = NULL;
	disk = gluNewQuadric();
	gluQuadricDrawStyle(disk, GLU_LINE);
	gluDisk(disk, inner, outer, 30, 30);
	gluDeleteQuadric(disk);
}

void cherryTopping() {
	// cherry body
	glColor3f(rgbDivide(155), rgbDivide(17), rgbDivide(30));
	drawSphere(0.1);

	// cherry stick
	glColor3f(rgbDivide(141), rgbDivide(282), 0);
	glLineWidth(3);
	glPushMatrix();
	glTranslatef(-0.1, -0.04, -0.1);
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (angle = 0; angle <= ((2 * PI) / 3); angle += (2 * PI) / 360) {
		cherryX = cherryXPos + cherryStickXR* cos(angle);
		cherryY = cherryYPos + cherryStickYR * sin(angle);
		glVertex2f(cherryX, cherryY);
	}
	glEnd();
	glPopMatrix();
}
void goldenDiskChocTopping() {
	glColor3f(rgbDivide(255), rgbDivide(204), 0);
	drawDisk(0.08, 0.15);
}
void vanillaScoop() {
	glColor3f(rgbDivide(209), rgbDivide(190), rgbDivide(168));
	drawSphere(0.29);
}
void ChocolateScoop() {
	glColor3f(rgbDivide(112), rgbDivide(66), rgbDivide(65));
	drawSphere(0.25);
}
void drawConeLine(double br, double tr, double h) {
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(rgbDivide(139), rgbDivide(69), rgbDivide(19));
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, br, tr, h, 30, 30);
	// if do not delete, the program will crash eventually as the object will be incremented by time
	gluDeleteQuadric(cylinder);
	glPopMatrix();
}
void drawConeBody(double br, double tr, double h) {
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(rgbDivide(205), rgbDivide(162), rgbDivide(111));
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluCylinder(cylinder, br, tr, h, 30, 30);
	// if do not delete, the program will crash eventually as the object will be incremented by time
	gluDeleteQuadric(cylinder);
	glPopMatrix();
}

void iceCream() {
	// rotate at y axis
	glRotatef(0.2, 0.0, 1.0, 0.0);

	// draw cone
	drawConeLine(coneBr, coneTr, coneH);
	drawConeBody(coneBr, coneTr, coneH);
	
	// draw ice cream part
	// vanilla, first scoop
	glPushMatrix();
	glTranslatef(0.0, 0.05, 0.0);
	vanillaScoop();
	glPopMatrix();

	// chocolate, second scoop
	glPushMatrix();
	glTranslatef(0.0, 0.35, 0.0);
	ChocolateScoop();
	glPopMatrix();

	// toppings
	// cherry
	glPushMatrix();
	glTranslatef(0.1, 0.6, 0);
	glRotatef(-60, 0, 0, 1);
	cherryTopping();
	glPopMatrix();

	// golden ring chocolate
	glPushMatrix();
	glTranslatef(-0.15, 0.55, 0);
	glRotatef(-30, 1, 0, 0);
	goldenDiskChocTopping();
	glPopMatrix();
}


// initialize pixel format for the window
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

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	iceCream();

	//glRotatef(0.5, 1.0, 1.0, 1.0);
	//drawCylinder(0.5, 0.5, 1.0);

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	// wc = window class
	// create window type object
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
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