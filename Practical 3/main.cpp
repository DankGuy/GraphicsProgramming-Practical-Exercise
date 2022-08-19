#include <Windows.h>
#include <gl/GL.h>
#include <string>
#include <math.h>

// #pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 3 Exercise"
int quesNo = 2;
int noOfTri = 360;
double xTranslateLeft = 0.0, xTranslateRight = 0.0;
double yTranslateLeft = 0.0, yTranslateRight = 0.0;
double x = 0.95, y = 0.9;
double x2, y2;
double angle = 0.0;
const float PI = 3.1429;
double rotateSpeed = 0.0;
double birdFlies = 0.0;
bool idle = false;
bool accelerate = false;
bool day = false;
float rot;
std::string direction = "right";

void reset() {
	xTranslateLeft = 0.0;
	xTranslateRight = 0.0;
	yTranslateLeft = 0.0;
	yTranslateRight = 0.0;
}
void translateX() {
	xTranslateLeft -= 0.1;
	xTranslateRight += 0.1;
}
void translateY() {
	yTranslateLeft -= 0.1;
	yTranslateRight += 0.1;
}
float rgbDivide(float rgb) {
	return (float)rgb / 255;
}
void fanBlade(int degree) {

	// drawing blades
	glPushMatrix();
	if (degree == 90) {
		glTranslatef(0.35, 0.35, 0);
		glPushMatrix();
		glRotatef(degree, 0, 0, 1);
	}
	else if (degree == 180) {
		glTranslatef(0, 0.7, 0);
		glRotatef(degree, 0, 0, 1);
	}
	else if (degree == 270) {
		glTranslatef(-0.35, 0.35, 0);
		glRotatef(degree, 0, 0, 1);
	}

	glTranslatef(0, 0.35, 0);

	// let the blade spin automatically
	//if (!idle && direction == "left") {
	//	rotateSpeed -= 0.2;
	//	//if (accelerate) {
	//	//	rotateSpeed -= 0.5;
	//	//}
	//}
	//else if (!idle && direction == "right") {
	//	rotateSpeed += 0.2;
	//	//if (accelerate) {
	//	//	rotateSpeed += 0.5;
	//	//}
	//}

	//if (!idle) {
	//	rotateSpeed += 0.2;
	//}
	rot += rotateSpeed;

	glRotatef(rot, 0, 0, 1);
	glTranslatef(0, -0.34, 0);

	// branch
	glColor3f(rgbDivide(227), rgbDivide(218), rgbDivide(201));
	glBegin(GL_QUADS);
	glVertex2f(-0.22, 0.34);
	glVertex2f(-0.08, 0.34);
	glVertex2f(-0.08, 0.36);
	glVertex2f(-0.22, 0.36);
	glEnd();

	// blade body
	glColor3f(rgbDivide(222), rgbDivide(184), rgbDivide(135));
	glBegin(GL_QUADS);
	glVertex2f(-0.62, 0.312);
	glVertex2f(-0.22, 0.312);
	glVertex2f(-0.22, 0.388);
	glVertex2f(-0.62, 0.388);
	glEnd();

	// blade bottom side
	glColor3f(rgbDivide(166), rgbDivide(123), rgbDivide(91));
	glBegin(GL_QUADS);
	glVertex2f(-0.62, 0.288);
	glVertex2f(-0.22, 0.288);
	glVertex2f(-0.22, 0.312);
	glVertex2f(-0.62, 0.312);
	glEnd();

	// blade top side
	glBegin(GL_QUADS);
	glVertex2f(-0.62, 0.388);
	glVertex2f(-0.22, 0.388);
	glVertex2f(-0.22, 0.41);
	glVertex2f(-0.62, 0.41);
	glEnd();

	// blade pattern
	glColor3f(rgbDivide(152), rgbDivide(116), rgbDivide(86));
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(-0.58, 0.388);
	glVertex2f(-0.58, 0.31);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.54, 0.388);
	glVertex2f(-0.54, 0.31);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.5, 0.388);
	glVertex2f(-0.5, 0.312);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.46, 0.388);
	glVertex2f(-0.46, 0.31);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.42, 0.388);
	glVertex2f(-0.42, 0.31);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.38, 0.388);
	glVertex2f(-0.38, 0.312);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.34, 0.388);
	glVertex2f(-0.34, 0.31);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.3, 0.388);
	glVertex2f(-0.3, 0.31);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.26, 0.388);
	glVertex2f(-0.26, 0.31);
	glEnd();

	glPopMatrix();
	glPopMatrix();
}
void trees() {
	// trunks
	glColor3f(rgbDivide(131), rgbDivide(105), rgbDivide(83));
	glBegin(GL_QUADS);
	glVertex2f(-0.6, -0.6);
	glVertex2f(-0.5, -0.6);
	glVertex2f(-0.52, -0.4);
	glVertex2f(-0.58, -0.4);
	glEnd();

	// leaves part
	glPushMatrix();
	glTranslatef(0.015, 0, 0);
	glColor3f(0, 0.7, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.75, -0.4);
	glVertex2f(-0.35, -0.4);
	glVertex2f(((-0.75 - 0.35) / 2), 0.5);
	glEnd();
	glPopMatrix();
}
void sun() {
	glColor3f(rgbDivide(236), rgbDivide(88), rgbDivide(0));
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (angle = 0; angle <= (2 * PI); angle += ((2 * PI) / 360)) {
		x2 = x + 0.2 * cos(angle);
		y2 = y + 0.2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

}
void moon() {
	glColor3f(rgbDivide(252), rgbDivide(229), rgbDivide(112));
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (angle = 0; angle <= (2 * PI); angle += ((2 * PI) / 360)) {
		x2 = x + 0.2 * cos(angle);
		y2 = y + 0.2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
}
void bird() {
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
		glVertex2f(-0.02, 0);
		glVertex2f(0, 0);
		glVertex2f(-0.01, 0);
		glVertex2f(-0.03, 0.02);
		glVertex2f(-0.01, 0);
		glVertex2f(0.03, 0.02);
	glEnd();
}

void ok() {
	// blade pattern
	glColor3f(rgbDivide(152), rgbDivide(116), rgbDivide(86));
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(-0.58, 0.384);
	glVertex2f(-0.58, 0.312);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.54, 0.384);
	glVertex2f(-0.54, 0.312);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.5, 0.384);
	glVertex2f(-0.5, 0.312);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.46, 0.384);
	glVertex2f(-0.46, 0.312);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.42, 0.384);
	glVertex2f(-0.42, 0.312);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.38, 0.384);
	glVertex2f(-0.38, 0.312);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.34, 0.384);
	glVertex2f(-0.34, 0.312);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.3, 0.384);
	glVertex2f(-0.3, 0.312);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.26, 0.384);
	glVertex2f(-0.26, 0.312);
	glEnd();

}

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
		else if (wParam == 0x31)
			quesNo = 1;
		else if (wParam == 0x32)
			quesNo = 2;
		else if (wParam == VK_LEFT || wParam == VK_RIGHT)
			translateX();
		else if (wParam == VK_UP || wParam == VK_DOWN)
			translateY();
		else if (wParam == 0x20)
			reset();
		// a
		else if (wParam == 0x41) {
			direction = "left";
			idle = false;
			rotateSpeed -= 0.2;
		}
		// d
		else if (wParam == 0x44) {
			direction = "right";
			idle = false;
			rotateSpeed += 0.2;
		}
		// x
		//
		//else if (wParam == 0x58) {
		//	accelerate = !accelerate;
		//}
		// s
		else if (wParam == 0x53) {
			rotateSpeed = 0;
		}
		else if (wParam == 0x4C) { // L
			glClearColor(0, rgbDivide(191), rgbDivide(255), 0);
			day = true;
		}
		else if (wParam == 0x4E) { // N
			glClearColor(0, 0, 0, 0);
			day = false;
		}
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


// Q1
void q1() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 0, 0);

	// left quad
	glPushMatrix();
	glTranslatef(xTranslateLeft, yTranslateLeft, 1);
	glBegin(GL_QUADS);
		glVertex2f(-0.2, 0);
		glVertex2f(0, 0);
		glVertex2f(0, 0.2);
		glVertex2f(-0.2, 0.2);
	glEnd();
	glPopMatrix();

	// right quad
	glPushMatrix();
	glTranslatef(xTranslateRight, yTranslateRight, 1);
	glBegin(GL_QUADS);
		glVertex2f(0.2, 0);
		glVertex2f(0, 0);
		glVertex2f(0, 0.2);
		glVertex2f(0.2, 0.2);
	glEnd();
	glPopMatrix();
}
void windmill() {
	glClear(GL_COLOR_BUFFER_BIT);

	// grass
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
		glVertex2f(-1.0, -1.0);
		glVertex2f(1.0, -1.0);
		glVertex2f(1.0, -0.5);
		glVertex2f(-1.0, -0.5);
	glEnd();

	// trees
	trees();

	// sun / moon
	if (day) {
		sun();

		if (birdFlies <= 1 && birdFlies >= -2) {
			birdFlies -= 0.002;
		}
		else {
			birdFlies += 2;
		}
		glPushMatrix();
		glTranslatef(1.5, 0, 0);
		glScalef(1.2, 1.2, 0);
		glPushMatrix();
		glTranslatef(birdFlies, 0, 0);
		glPushMatrix();
		glTranslatef(-0.2, 0.5, 0);
		bird();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.4, 0.6, 0);
		bird();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.5, 0.65, 0);
		bird();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.55, 0.67, 0);
		bird();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
	}
	else {
		moon();
	}

	glPushMatrix();
	glScalef(0.6, 0.6, 0);
	glTranslatef(1.5, -0.3, 0);
	trees();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.8, 0.8, 0);
	glTranslatef(1.7, -0.3, 0);
	trees();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.8, 0.8, 0);
	glTranslatef(-0.5, -0.5, 0);
	trees();
	glPopMatrix();


	//glPushMatrix();
	//glColor3f(rgbDivide(250), rgbDivide(70), rgbDivide(22));
	//glBegin(GL_TRIANGLE_FAN);
	//glVertex2f(x, y);
	//for (angle = 0; angle <= (PI); angle += ((PI) / 360)) {
	//	x2 = x + 0.2 * cos(angle);
	//	y2 = y + 0.2 * sin(angle);
	//	glVertex2f(x2, y2);
	//}
	//glEnd();
	//glPopMatrix();

	// windmill base
	glColor3f(rgbDivide(160), rgbDivide(82), rgbDivide(45));
	glBegin(GL_QUADS);
		glVertex2f(-0.35, -0.6);
		glVertex2f(0.35, -0.6);
		glVertex2f(0.35, -0.52);
		glVertex2f(-0.35, -0.52);
	glEnd();

	// windmill body
	glColor3f(rgbDivide(255), rgbDivide(228), rgbDivide(181));
	glBegin(GL_QUADS);
		glVertex2f(-0.25, -0.52);
		glVertex2f(0.24, -0.52);
		glVertex2f(0.25, 0.2);
		glVertex2f(-0.25, 0.2);
	glEnd();


	// windmill left body
	glColor3f(rgbDivide(145), rgbDivide(163), rgbDivide(176));
	glBegin(GL_QUADS);
		glVertex2f(-0.33, -0.52);
		glVertex2f(-0.19, -0.52);
		glVertex2f(-0.19, 0.2);
		glVertex2f(-0.25, 0.2);
	glEnd();

	// windmill right body
	glBegin(GL_QUADS);
		glVertex2f(0.33, -0.52);
		glVertex2f(0.19, -0.52);
		glVertex2f(0.19, 0.2);
		glVertex2f(0.25, 0.2);
	glEnd();

	// semicircle top
	glColor3f(rgbDivide(28), rgbDivide(28), rgbDivide(240));
	glBegin(GL_TRIANGLE_FAN);
	for (angle = 0; angle <= (PI); angle += (2 * PI) / 360) {
		x2 = 0 + 0.25 * cos(angle);
		y2 = 0.2 + 0.3 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// windmill cracks
	glColor3f(rgbDivide(47), rgbDivide(79), rgbDivide(79));
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
		glVertex2f(-0.25, 0.2);
		glVertex2f(0, 0.02);
		glVertex2f(0, -0.1);
		glVertex2f(0, 0.02);
		glVertex2f(0.25, 0.2);
	glEnd();

	// fanblade center point
	glColor3f(rgbDivide(111), rgbDivide(78), rgbDivide(55));
	glBegin(GL_TRIANGLE_FAN);
	for (angle = 0; angle <= (2 * PI); angle += ((2 * PI) / 360)) {
		x2 = 0 + 0.08 * cos(angle);
		y2 = 0.35 + 0.08 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glColor3f(rgbDivide(176), rgbDivide(101), rgbDivide(0));
	glBegin(GL_TRIANGLE_FAN);
	for (angle = 0; angle <= (2 * PI); angle += ((2 * PI) / 360)) {
		x2 = 0 + 0.05 * cos(angle);
		y2 = 0.35 + 0.05 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// door
	glColor3f(rgbDivide(167), rgbDivide(85), rgbDivide(2));
	glBegin(GL_TRIANGLE_FAN);
	for (angle = 0; angle <= (PI); angle += ((2 * PI) / 360)) {
		x2 = 0 + 0.1 * cos(angle);
		y2 = -0.2 + 0.1 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_QUADS);
		glVertex2f(-0.1, -0.52);
		glVertex2f(0.1, -0.52);
		glVertex2f(0.1, -0.2);
		glVertex2f(-0.1, -0.2);
	glEnd();

	// door strips horizontal
	glColor3f(rgbDivide(100), rgbDivide(65), rgbDivide(23));
	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex2f(-0.1, -0.3);
		glVertex2f(0.1, -0.3);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(-0.1, -0.45);
		glVertex2f(0.1, -0.45);
	glEnd();

	// door strips vertical
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex2f(-0.08, -0.15);
		glVertex2f(-0.08, -0.52);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(-0.06, -0.12);
		glVertex2f(-0.06, -0.52);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(-0.04, -0.11);
		glVertex2f(-0.04, -0.52);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(-0.02, -0.11);
		glVertex2f(-0.02, -0.52);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, -0.10);
		glVertex2f(0, -0.52);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0.02, -0.11);
		glVertex2f(0.02, -0.52);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0.04, -0.12);
		glVertex2f(0.04, -0.52);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0.06, -0.13);
	glVertex2f(0.06, -0.52);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0.08, -0.15);
		glVertex2f(0.08, -0.52);
	glEnd();

	// fanblades
	fanBlade(0);
	fanBlade(90);
	fanBlade(180);
	fanBlade(270);

}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	switch (quesNo)
	{
	case 1:
		q1();
		break;
	case 2:
		windmill();
		//ok();
		break;
	default:
		break;
	}

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