
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#define WINDOW_TITLE "P4"

int qNo = 2;

float x = 0, y = 1, z = 0;
float rx = 0, ry = 0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == 0x58) {   //Press key 'x'
			x = 0;
			y = 1;
			z = 0;
		}
		else if (wParam == 0x59) {   //Press key 'y'
			x = 1;
			y = 0;
			z = 0;
		}
		else if (wParam == 0x5a) {   //Press key 'x'
			x = 0;
			y = 0;
			z = 1;
		}
		else if (wParam == VK_UP) {   //Press key 'UP'
			rx += 10;
		}
		else if (wParam == VK_DOWN) {   //Press key 'DOWN'
			rx -= 10;
		}
		else if (wParam == VK_LEFT) {   //Press key 'LEFT'
			ry += 10;
		}
		else if (wParam == VK_RIGHT) {   //Press key 'RIGHT'
			ry -= 10;
		}
		else if (wParam == VK_SPACE) {   //Press key 'SPACE'
			rx = 00;
			ry = 00;
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

void drawCube(float sz) {
	glBegin(GL_QUADS);
	// face 1 : bottom
	glColor3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	// face 2 : left
	glColor3f(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(0.0f, 0.0f, sz);
	// face 3 : front
	glColor3f(0, 0, 1);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, 0.0f, sz);
	// face 4 : right
	glColor3f(1, 1, 0);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(sz, 0.0f, 0.0f);
	// face 5 : back
	glColor3f(1, 0, 1);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(sz, sz, 0.0f);
	// face 6 : 
	glColor3f(0, 1, 1);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glEnd();
}

void drawPyramid(float sz) {

	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	//Face 1 : Bottom 
	glColor3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(sz / 2, sz, sz / 2);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(sz / 2, sz, sz / 2);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz / 2, sz, sz / 2);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(sz / 2, sz, sz / 2);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();


}

void drawRectangle() {
	glBegin(GL_LINES);
	//Face1:Bottom
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	//Face2:Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	//Face3:front
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, 1.0f, 0.0f);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	//Face4:Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-2.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-2.0f, 1.0f, 1.0f);
	glEnd();

	//Face5:Back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-2.0f, 1.0f, 1.0f);
	glVertex3f(-2.0f, 1.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 1.0f);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	//Face6:Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-2.0f, 0.0f, 1.0f);
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(0.5, 1.0, 1.0, 1.0);
	drawCube(0.5);
	//drawCube(-0.5);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);

	//glRotatef(0.1, x, y, z);
	//drawPyramid(0.5);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);

	//glPushMatrix();

	//glRotatef(ry, 1, 1, 1);

	//glPushMatrix();
	//glScalef(0.4, 0.4, 0.4);
	//drawRectangle();

	//glPushMatrix();
	//glRotatef(rx, 0, 0, 1);
	//glTranslatef(2, 0, 0);
	//drawRectangle();
	//glPopMatrix();

	//glPopMatrix();

	//glPopMatrix();

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
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
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