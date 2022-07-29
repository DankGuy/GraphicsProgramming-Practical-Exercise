#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

// #pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 1 Demo"
int questionNo = 6;


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
		else if (wParam == 0x31) { // press key '1'
			questionNo = 1;
		}
		else if (wParam == 0x32) { // press key '2'
			questionNo = 2;
		}
		else if (wParam == 0x33) { // press key '3'
			questionNo = 3;
		}
		else if (wParam == 0x34) { // press key '4'
			questionNo = 4;
		}
		else if (wParam == 0x35) {
			questionNo = 5;
		}
		else if (wParam == 0x36) {
			questionNo = 6;
		}
		else if (wParam == 0x37) {
			questionNo = 7;
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

void pahangFlag()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	glClearColor(1, 0, 0, 0);
	// clear screen
	glClear(GL_COLOR_BUFFER_BIT);

	// GL_SMOOTH is default
	glShadeModel(GL_SMOOTH);
	// Begin drawing
	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-7.0, 3.0);
	glVertex2f(7.0, 3.0);
	glVertex2f(7.0, 0.0);
	glVertex2f(-7.0, 0.0);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(7.0, 0.0);
	glVertex2f(7.0, -3.0);
	glVertex2f(-7.0, -3.0);
	glVertex2f(-7.0, -0.0);


	// End drawing
	glEnd();

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}

void n9Flag() {
	// set background color to black
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-1.0, 1.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 1.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-1.0, 1.0);
	glVertex2f(-1.0, 0.0);
	glVertex2f(0.0, 0.0);
	glEnd();

	// begin the background (yellow part of the flag)
	glBegin(GL_QUADS);

	glColor3f(1.0, 0.95, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(1.0, 1.0);
	glVertex2f(0.0, 1.0);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(1.0, 0.95, 0.0);
	glVertex2f(-1.0, -1.0);
	glVertex2f(1.0, -1.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(-1.0, 0.0);

	glEnd();
}

void englandFlag() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// left dark red
	glBegin(GL_QUADS);
	glColor3f(0.51, 0.0, 0.0);
	glVertex2f(-1, -0.2);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.8, -0.2);
	glVertex2f(-0.8, 0.2);
	glColor3f(0.51, 0.0, 0.0);
	glVertex2f(-1, 0.2);
	glEnd();

	// middle horizontal red
	glBegin(GL_QUADS);
	glColor3f(1.0, 0, 0);
	glVertex2f(-0.8, -0.2);
	glVertex2f(0.8, -0.2);
	glVertex2f(0.8, 0.2);
	glVertex2f(-0.8, 0.2);
	glEnd();

	// right dark red
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(0.8, -0.2);
	glColor3f(0.51, 0, 0);
	glVertex2f(1, -0.2);
	glVertex2f(1, 0.2);
	glColor3f(1, 0.0, 0.0);
	glVertex2f(0.8, 0.2);
	glEnd();

	// top dark red
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(-0.2, 0.8);
	glVertex2f(0.2, 0.8);
	glColor3f(0.51, 0, 0);
	glVertex2f(0.2, 1);
	glVertex2f(-0.2, 1);
	glEnd();

	// middle vertical red
	glBegin(GL_QUADS);
	glColor3f(1.0, 0, 0);
	glVertex2f(-0.2, -0.8);
	glVertex2f(0.2, -0.8);
	glVertex2f(0.2, 0.8);
	glVertex2f(-0.2, 0.8);
	glEnd();

	// bottom dark red
	glBegin(GL_QUADS);
	glColor3f(0.51, 0, 0);
	glVertex2f(-0.2, -1);
	glVertex2f(0.2, -1);
	glColor3f(1.0, 0, 0);
	glVertex2f(0.2, -0.8);
	glVertex2f(-0.2, -0.8);
	glEnd();

	// top left corner quad
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-0.8, 0.8);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(-0.8, 1);
	glVertex2f(-1, 1);
	glVertex2f(-1, 0.8);
	glEnd();

	// left rec
	glBegin(GL_QUADS);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(-1, 0.2);
	glColor3f(1, 1, 1);
	glVertex2f(-0.8, 0.2);
	glVertex2f(-0.8, 0.8);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(-1, 0.8);
	glEnd();

	// top rec
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-0.8, 0.8);
	glVertex2f(-0.2, 0.8);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(-0.2, 1);
	glVertex2f(-0.8, 1);
	glEnd();

	// top left quad
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-0.8, 0.2);
	glVertex2f(-0.2, 0.2);
	glVertex2f(-0.2, 0.8);
	glVertex2f(-0.8, 0.8);
	glEnd();

	// top right corner quad
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(0.8, 0.8);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(1, 0.8);
	glVertex2f(1, 1);
	glVertex2f(0.8, 1);
	glEnd();

	// right rec
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(0.8, 0.2);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(1, 0.2);
	glVertex2f(1, 0.8);
	glColor3f(1, 1, 1);
	glVertex2f(0.8, 0.8);
	glEnd();

	// top rec
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(0.2, 0.8);
	glVertex2f(0.8, 0.8);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(0.8, 1);
	glVertex2f(0.2, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(0.2, 0.2);
	glVertex2f(0.8, 0.2);
	glVertex2f(0.8, 0.8);
	glVertex2f(0.2, 0.8);
	glEnd();

	// bottom left quad
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-0.8, -0.8);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(-1, -0.8);
	glVertex2f(-1, -1);
	glVertex2f(-0.8, -1);
	glEnd();

	// left rec
	glBegin(GL_QUADS);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(-1, -0.8);
	glColor3f(1, 1, 1);
	glVertex2f(-0.8, -0.8);
	glVertex2f(-0.8, -0.2);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(-1, -0.2);
	glEnd();

	// bottom rec
	glBegin(GL_QUADS);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(-0.8, -1);
	glVertex2f(-0.2, -1);
	glColor3f(1, 1, 1);
	glVertex2f(-0.2, -0.8);
	glVertex2f(-0.8, -0.8);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-0.8, -0.8);
	glVertex2f(-0.2, -0.8);
	glVertex2f(-0.2, -0.2);
	glVertex2f(-0.8, -0.2);
	glEnd();

	// bottom right quad
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(0.8, -0.8);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(0.8, -1);
	glVertex2f(1, -1);
	glVertex2f(1, -0.8);
	glEnd();

	// bottom rec
	glBegin(GL_QUADS);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(0.2, -1);
	glVertex2f(0.8, -1);
	glColor3f(1, 1, 1);
	glVertex2f(0.8, -0.8);
	glVertex2f(0.2, -0.8);
	glEnd();

	// right rec
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(0.8, -0.8);
	glColor3f(0.38, 0.38, 0.38);
	glVertex2f(1, -0.8);
	glVertex2f(1, -0.2);
	glColor3f(1, 1, 1);
	glVertex2f(0.8, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(0.2, -0.8);
	glVertex2f(0.8, -0.8);
	glVertex2f(0.8, -0.2);
	glVertex2f(0.2, -0.2);
	glEnd();
}

void scottlandFlag() {
	// set background color to black
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0); // white color
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, 1);
	glVertex2f(-1, 1);
	glEnd();

	// top triangle
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0); // blue
	glVertex2f(0, 0.3);
	glVertex2f(0.7, 1);
	glVertex2f(-0.7, 1);
	glEnd();

	// left triangle
	glBegin(GL_TRIANGLES);
	glVertex2f(-1, -0.7);
	glVertex2f(-0.3, 0);
	glVertex2f(-1, 0.7);
	glEnd();

	// bottom triangle
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.7, -1);
	glVertex2f(0.7, -1);
	glVertex2f(0, -0.3);
	glEnd();

	// right triangle
	glBegin(GL_TRIANGLES);
	glVertex2f(1, -0.7);
	glVertex2f(0.3, 0);
	glVertex2f(1, 0.7);
	glEnd();

	// border
	glBegin(GL_LINE_LOOP);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, 1);
	glVertex2f(-1, 1);
	glEnd();


}

void japanFlag() {
	float x = 0, y = 0; // origin of circle (x, y) (0, 0) 
	float r = 0.25; // r = radius = 1.0
	float angle = 0;
	float PI = 3.1429;
	float x2 = 0, y2 = 0; // Point on circle (x2, y2)
	int noOfTri = 30;


	glClear(GL_COLOR_BUFFER_BIT); // clear screen
	glClearColor(1, 1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0, 0);
	glVertex2f(x, y); // origin of circle
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	 }
	glEnd();

	// outline
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 1);
	glVertex2f(-0.5, 0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(0.5, 0.5);
	glEnd();
}

void happy() {
	float x = 0, y = 0;
	float r = 0.6;
	float angle;
	float PI = 3.1429;
	float x2 = 0, y2 = 0;
	int noOfTri = 30;

	glClear(GL_COLOR_BUFFER_BIT);

	// the whole face
	glClearColor(1, 1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(204, 204, 0);
	glVertex2f(x, y);
	for (angle = 0; angle <=  (2*PI); angle += (2*PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();


	

	// left eye
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(-0.205, 0.242);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = -0.205 + 0.08 * cos(angle);
		y2 = 0.242 + 0.1 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// left eye reflection
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(-0.235, 0.29);
	for (angle = 0; angle <= (2 * PI); angle += ((2 * PI) / noOfTri)) {
		x2 = -0.235 + 0.03 * cos(angle);
		y2 = 0.29 + 0.05 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// right eye
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(0.205, 0.242);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = 0.205 + 0.08 * cos(angle);
		y2 = 0.242 + 0.1 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// right eye reflection
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0.168, 0.29);
	for (angle = 0; angle <= (2 * PI); angle += ((2 * PI) / noOfTri)) {
		x2 = 0.168 + 0.03 * cos(angle);
		y2 = 0.29 + 0.05 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// left cheek
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0, 0);
	glVertex2f(-0.322, -0.085);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = -0.322 + 0.1 * cos(angle);
		y2 = -0.085 + 0.1 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// right cheek
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0, 0);
	glVertex2f(0.322, -0.085);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = 0.322 + 0.1 * cos(angle);
		y2 = -0.085 + 0.1 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// nose
	//glBegin(GL_TRIANGLE_FAN);
	//glColor3f(0, 0, 0);
	//glVertex2f(0, 0);
	//for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
	//	x2 = 0 + 0.07 * cos(angle);
	//	y2 = 0 + 0.05 * sin(angle);
	//	glVertex2f(x2, y2);
	//}
	//glEnd();

	// nose
	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(0.341, 0.302, 0.149);
	glVertex2f(-0.05, -0.05);
	glVertex2f(0.05, -0.05);
	glVertex2f(0, 0.04);
	glEnd();
	glPopMatrix();

	// left ear
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.4, 0.43);
	glVertex2f(-0.23, 0.54);
	glVertex2f(-0.6, 0.8);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(204, 204, 0);
	glVertex2f(-0.322, 0.46);
	for (angle = 0; angle <= (2*PI); angle += (2*PI) / noOfTri) {
		x2 = -0.322 + 0.1078 * cos(angle);
		y2 = 0.46 + 0.153 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();


	// right ear
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(0.4, 0.43);
	glVertex2f(0.23, 0.54);
	glVertex2f(0.6, 0.8);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(204, 204, 0);
	glVertex2f(0.322, 0.46);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = 0.322 + 0.1078 * cos(angle);
		y2 = 0.46 + 0.153 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();


	// mouth
	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glTranslatef(0, 0.4, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.522, 0.063, 0);
	glVertex2f(0, -0.2);
	for (angle = 0; angle <= (PI); angle += (PI) / noOfTri) {
		x2 = 0 + 0.2 * cos(angle);
		y2 = -0.2 + 0.15 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();


	// teeth
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1, 1, 1);
	glVertex2f(-0.1, -0.2);
	glVertex2f(-0.05, -0.3);
	glVertex2f(0, -0.2);
	glVertex2f(0.05, -0.3);
	glVertex2f(0.1, -0.2);
	glEnd();

	// teeth line
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(0, -0.2);
	glVertex2f(0, -0.3);
	glEnd();

}

void sad() {
	float x = 0, y = 0;
	float r = 0.6;
	float angle;
	float PI = 3.1429;
	float x2 = 0, y2 = 0;
	int noOfTri = 30;

	glClear(GL_COLOR_BUFFER_BIT);

	// the whole face
	glClearColor(1, 1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.361, 0.196, 0.588);
	glVertex2f(x, y);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// left eye
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(-0.205, 0.242);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = -0.205 + 0.08 * cos(angle);
		y2 = 0.242 + 0.1 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// left eye reflection
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(-0.235, 0.29);
	for (angle = 0; angle <= (2 * PI); angle += ((2 * PI) / noOfTri)) {
		x2 = -0.235 + 0.03 * cos(angle);
		y2 = 0.29 + 0.05 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// right eye
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(0.205, 0.242);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = 0.205 + 0.08 * cos(angle);
		y2 = 0.242 + 0.1 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// right eye reflection
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0.168, 0.29);
	for (angle = 0; angle <= (2 * PI); angle += ((2 * PI) / noOfTri)) {
		x2 = 0.168 + 0.03 * cos(angle);
		y2 = 0.29 + 0.05 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// left cheek
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.13, 0.694, 0.298);
	glVertex2f(-0.322, -0.085);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = -0.322 + 0.1 * cos(angle);
		y2 = -0.085 + 0.1 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// right cheek
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.13, 0.694, 0.298);
	glVertex2f(0.322, -0.085);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = 0.322 + 0.1 * cos(angle);
		y2 = -0.085 + 0.1 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// nose
	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(0.341, 0.302, 0.149);
	glVertex2f(-0.05, -0.05);
	glVertex2f(0.05, -0.05);
	glVertex2f(0, 0.04);
	glEnd();
	glPopMatrix();

	// left ear
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.4, 0.43);
	glVertex2f(-0.23, 0.54);
	glVertex2f(-0.6, 0.8);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.361, 0.196, 0.588);
	glVertex2f(-0.322, 0.46);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = -0.322 + 0.1078 * cos(angle);
		y2 = 0.46 + 0.153 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();


	// right ear
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(0.4, 0.43);
	glVertex2f(0.23, 0.54);
	glVertex2f(0.6, 0.8);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.361, 0.196, 0.588);
	glVertex2f(0.322, 0.46);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = 0.322 + 0.1078 * cos(angle);
		y2 = 0.46 + 0.153 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();


	// mouth
	glLineWidth(4);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	for (angle = 0; angle <= (PI); angle += (PI) / noOfTri) {
		x2 = -0.1 + 0.1 * cos(angle);
		y2 = -0.2 + 0.1 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glTranslatef(-0.2, 0, 0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	for (angle = 0; angle <= (PI); angle += (PI) / noOfTri) {
		x2 = 0.1 + 0.1 * cos(angle);
		y2 = 0.2 + 0.1 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	// tears
	glLineWidth(8);
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex2f(-0.2, 0.2);
	glVertex2f(-0.2, 0);
	glEnd();


	glLineWidth(8);
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex2f(0.2, 0.2);
	glVertex2f(0.2, 0);
	glEnd();
}

void display() {
	switch (questionNo) {
	case 1: 
		pahangFlag();
		break;
	case 2:
		n9Flag();
		break;
	case 3:
		englandFlag();
		break;
	case 4:
		scottlandFlag();
		break;
	case 5:
		japanFlag();
		break;
	case 6:
		happy();
		break;
	case 7:
		sad();
		break;
	default:
		happy();
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