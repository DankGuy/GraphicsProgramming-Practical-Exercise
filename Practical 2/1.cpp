#include <Windows.h>
#include <iostream>
#include <gl/GL.h>
#include <string>
#include <math.h>
#include <GL\freeglut.h>

// #pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 2 Exercise"
void changeColor();
void reset();
float rgbDivide(int rgb);
void starColorChanging();
void rotateAngleFunc();

int quesNo = 4;
double tx = 0, ty = 0, tSpeed = 0.1;
std::string color;
float red = rgbDivide(255), green = rgbDivide(255), blue = rgbDivide(0);
int rotateAngle = 0.0;
double scaleRatio = 0.0;


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
		else if (wParam == VK_RIGHT) // right arrow key
			tx += tSpeed;
		else if (wParam == VK_LEFT)
			tx -= tSpeed;
		else if (wParam == VK_DOWN)
			ty -= tSpeed;
		else if (wParam == VK_UP)
			ty += tSpeed;
		else if (wParam == 0x52)
			color = "red";
		else if (wParam == 0x47)
			color = "green";
		else if (wParam == 0x42)
			color = "blue";
		else if (wParam == 0x20)
			reset();
		else if (wParam == 0x31)
			quesNo = 1;
		else if (wParam == 0x32)
			quesNo = 2;
			//starColorChanging(0);
		else if (wParam == 0x33)
			quesNo = 3;
			//rotateAngleTimer(0);
		else if (wParam == 0x34)
			quesNo = 4;
		break;
		
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

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

// divide 255
float rgbDivide(int rgb) {
	return ((float)rgb) / 255;
}

// Q1
void q1() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(tx, ty, 0);

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	changeColor();
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(0, 0.5);
	glEnd();
}
void changeColor() {
	if (color == "red")
		glColor3f(1, 0, 0);
	else if (color == "green")
		glColor3f(0, 1, 0);
	else if (color == "blue")
		glColor3f(0, 0, 1);
	else if (color == "white")
		glColor3f(1, 1, 1);
}
void reset() {
	color = "white";
	tx = 0;
	ty = 0;
}

// Q2
void drawTriangle(float rotate) {
	glPushMatrix();
	glRotatef(rotate, 0, 0, 1);
	glBegin(GL_TRIANGLES);
		glVertex2f(0, 0.6);
		glVertex2f(-0.178, 0.24);
		glVertex2f(0.178, 0.24);
	glEnd();
	glPopMatrix();
}
void starColorChanging() {
	//glutPostRedisplay();
	//glutTimerFunc(1000 / 60, starColorChanging, 0);
	if (red == 1.0) {
		red = 0.0;
		blue = 0.0;
	}
	else if (green == 1.0) {
		green = 0.0;
		blue = 1.0;
	}
	else if (blue == 1.0) {
		blue = 0.0;
		red = 1.0;
	}
	else {
		red = 1.0;
		green = 1.0;
		blue = 0.0;
	}
}
void q2() {
	float PI = 3.1429;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(red, green, blue); // yellow
	starColorChanging();


	// hexagon
	glPushMatrix();
	glRotatef(54, 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
	for (float angle = 0; angle <= (2 * PI); angle += (2 * PI) / 5) {
		float x = 0 + 0.3 * cos(angle);
		float y = 0 + 0.3 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();

	// triangles
	drawTriangle(0.0);
	drawTriangle(73.0);
	drawTriangle(-73.0);
	drawTriangle(145.0);
	drawTriangle(-145.0);

	// lines
	glPushMatrix();
	glTranslatef(0, -0.05, 0);
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(rgbDivide(105), rgbDivide(105), rgbDivide(105)); // dimgray
		glVertex2f(0, 0.3);
		glVertex2f(0, 0.1);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(-0.15, 0.135);
		glVertex2f(0, 0.1);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0.15, 0.135);
		glVertex2f(0, 0.1);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 0.1);
		glVertex2f(-0.1, -0.1);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 0.1);
		glVertex2f(0.1, -0.1);
	glEnd();
	glPopMatrix();
}

// Q3
void rotateAngleFunc() {
	//glutPostRedisplay();
	//glutTimerFunc(1000 / 60, rotateAngleTimer, 0);
	
	if (rotateAngle < 360) {
		rotateAngle += 1.0;
	}
	else {
		rotateAngle = 0.0;
	}
}
void q3() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	rotateAngleFunc();
	glLoadIdentity();
	glRotatef(rotateAngle, 0, 0, 1);
	glPointSize(10);
	glBegin(GL_POINTS);
		glColor3f(1, 1, 1);
		glVertex2f(0, -0.5);
	glEnd();
}

// Q4
void expand() {
	if (scaleRatio < 9.5) {
		scaleRatio += 0.1;
	}
}
void q4() {
	glLoadIdentity();
	glScalef(scaleRatio, scaleRatio, 0.0);
	expand();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0, 0);
	glBegin(GL_QUADS);
		glVertex2f(-0.1, -0.1);
		glVertex2f(0.1, -0.1);
		glVertex2f(0.1, 0.1);
		glVertex2f(-0.1, 0.1);
	glEnd();
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	//glClear(GL_COLOR_BUFFER_BIT);

	//glLoadIdentity(); // reset
	//glTranslatef(-0.5, 0.5, 0);
	//glRotatef(90, 0, 0, 1); // Rz(90)
	//glScalef(0.5, 0.5, 1); // sx(0.5), sy(0.5) z cannot be 0

	//glBegin(GL_TRIANGLES);
	//glVertex2f(-0.5, 0);
	//glVertex2f(0, 0.5);
	//glVertex2f(0.5, 0);
	//glEnd();

	//glBegin(GL_QUADS);
	//glVertex2f(-0.5, 0);
	//glVertex2f(-0.5, 0.5);
	//glVertex2f(0.5, 0.5);
	//glVertex2f(0.5, 0);
	//glEnd();


	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------

	switch (quesNo)
	{
	case 1:
		q1();
		break;
	case 2:
		q2();
		break;
	case 3:
		q3();
		break;
	case 4:
		q4();
		break;
	default:
		q1();
		break;
	}

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
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
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