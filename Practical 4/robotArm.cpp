
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int qNo = 2;
float x, y, z;
float xRot, yRot, zRot, lzRot;

double c(double value) {
	return value / 255;
}

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
		//else if (wParam == 0x31)
		//	qNo = 1; //press key 1
		//else if (wParam == 0x32)
		//	qNo = 2; //press key 2
		//else if (wParam == 0x33)
		//	qNo = 3; //press key 3
		//else if (wParam == 0x34)
		//	qNo = 4; //press key 4
		//else if (wParam == 0x35)
		//	qNo = 5; //press key 5
		else if (wParam == VK_LEFT)
			xRot -= 1;
		else if (wParam == VK_RIGHT)
			xRot += 1;
		else if (wParam == 0x5a) // z
			yRot -= 1;
		else if (wParam == 0x58) // x
			yRot += 1;
		else if (wParam == 0x43) // c
			zRot -= 1;
		else if (wParam == 0x56) // v
			zRot += 1;
		else if (wParam == VK_DOWN)
			lzRot -= 1;
		else if (wParam == VK_UP)
			lzRot += 1;
		else if (wParam == VK_SPACE)
			xRot = 0, yRot = 0, zRot = 0, lzRot = 0;

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

//Arms
void upperArm(float sx, float sy, float sz) {

	glBegin(GL_LINE_STRIP);
	glColor3f(1, 1, 1);

	//Bottom
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(sx, 0.0f, sz);
	glVertex3f(sx, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//Left 
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sy, 0.0f);
	glVertex3f(0.0f, sy, sz);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//Front
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(0.0f, sy, sz);
	glVertex3f(sx, sy, sz);
	glVertex3f(sx, 0.0f, sz);
	//Right
	glVertex3f(sx, 0.0f, sz);
	glVertex3f(sx, sy, sz);
	glVertex3f(sx, sy, 0.0f);
	glVertex3f(sx, 0.0f, 0.0f);
	//Back
	glVertex3f(sx, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sy, 0.0f);
	glVertex3f(sx, sy, 0.0f);
	//Top
	glVertex3f(sx, sy, 0.0f);
	glVertex3f(0.0f, sy, 0.0f);
	glVertex3f(0.0f, sy, sz);
	glVertex3f(sx, sy, sz);

	glEnd();
}

void lowerArm(float sx, float sy, float sz) {

	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);

	//Bottom
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(-sx, 0.0f, sz);
	glVertex3f(-sx, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//Left 
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sy, 0.0f);
	glVertex3f(0.0f, sy, sz);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//Front
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(0.0f, sy, sz);
	glVertex3f(-sx, sy, sz);
	glVertex3f(-sx, 0.0f, sz);
	//Right
	glVertex3f(-sx, 0.0f, sz);
	glVertex3f(-sx, sy, sz);
	glVertex3f(-sx, sy, 0.0f);
	glVertex3f(-sx, 0.0f, 0.0f);
	//Back
	glVertex3f(-sx, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sy, 0.0f);
	glVertex3f(-sx, sy, 0.0f);
	//Top
	glVertex3f(-sx, sy, 0.0f);
	glVertex3f(0.0f, sy, 0.0f);
	glVertex3f(0.0f, sy, sz);
	glVertex3f(-sx, sy, sz);

	glEnd();
}

//Main
void P1_3() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//Whole arm rotation
	glPushMatrix();
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glRotatef(zRot, 0, 0, 1);

	//Upper arm
	upperArm(0.6, 0.3, 0.3);

	//Lower Arm
	glPushMatrix();
	glRotatef(-(lzRot), 0, 0, 1);
	lowerArm(0.6, 0.3, 0.3);
	glPopMatrix();

	glPopMatrix();

}

void display()
{
	switch (qNo) {
		/*case 1:
			P4Demo();
			break;*/
	case 2:
		P1_3();
		break;
	}

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

