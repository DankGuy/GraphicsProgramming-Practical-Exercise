#include <Windows.h>
#include <gl/GL.h>
#include <string>

// #pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 3 Exercise"
int quesNo = 1;
double xTranslateLeft = 0.0, xTranslateRight = 0.0;
double yTranslateLeft = 0.0, yTranslateRight = 0.0;

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
		else if (wParam == VK_LEFT || wParam == VK_RIGHT)
			translateX();
		else if (wParam == VK_UP || wParam == VK_DOWN)
			translateY();
		else if (wParam == 0x20)
			reset();
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


void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	switch (quesNo)
	{
	case 1:
		q1();
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