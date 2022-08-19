#include <Windows.h>
#include <iostream>
#include <gl/GL.h>
#include <string>
#include <math.h>
#define WINDOW_TITLE "Practical 4 Exercise"

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

void drawCube(float sz) {
	glBegin(GL_QUADS);
	// Face 1 : Bottom
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 : Left
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(0.0f, 0.0f, sz);

	// Face 3 : Front
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, 0.0f, sz);

	// Face 4 : Right
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(sz, 0.0f, 0.0f);

	// Face 5 : Back
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(sz, sz, 0.0f);

	// Face 6 : Top
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(sz, sz, sz);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glEnd();

}
void drawPyramid(float sz) {
	glBegin(GL_LINE_LOOP);
		// Face 1 : Bottom
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0f, 0.0f, sz);
		glVertex3f(sz, 0.0f, sz);
		glVertex3f(sz, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(sz/2, sz, sz/2);
		glVertex3f(0.0f, 0.0f, sz);
		glVertex3f(sz/2, sz, sz/2);
		glVertex3f(sz, 0.0f, sz);
		glVertex3f(sz/2, sz, sz/2);
		glVertex3f(sz, 0.0f, 0.0f);
		glVertex3f(sz / 2, sz, sz / 2);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glLineWidth(3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glRotatef(1.0, 1.0, 0.0, 0.0);
	//glRotatef(0.5, 0.0, 1.0, 0.0);
	//glRotatef(0.5, 0.0, 0.0, 1.0);
	glRotatef(0.5, 1.0, 1.0, 1.0);
	//glRotatef(0.5, 1.0, 1.0, 0.0);
	//glRotatef(0.5, 1.0, 0.0, 1.0);

	drawPyramid(0.5);
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