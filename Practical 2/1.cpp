#include <Windows.h>
#include <gl/GL.h>
#include <string>

// #pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 2 Exercise"
void changeColor();
void reset();

int quesNo = 1;
float tx = 0, ty = 0, tSpeed = 0.1;
std::string color;


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