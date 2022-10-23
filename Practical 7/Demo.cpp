#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

// #pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 7 Demo"

// Step 1 : Vairable Declaration
GLuint textureArr[2];
BITMAP BMP;				// bitmap structure
HBITMAP hBMP = NULL;	// bitmap handle


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

void drawSphere(double r) {
	glPushMatrix();
	glRotatef(0.5, 1.0, 1.0, 1.0);
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GL_TRIANGLES);
	gluQuadricTexture(sphere, true);
	gluSphere(sphere, r, 30, 30);
	// if do not delete, the program will crash eventually as the object will be incremented by time
	gluDeleteQuadric(sphere);
	glPopMatrix();
}
void drawCube(float sz) {
	glBegin(GL_QUADS);

	// face 1 : bottom
	//glColor3f(1, 0, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, 0.0f, sz);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	
	// face 2 : left
	//glColor3f(0, 1, 0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);

	// face 3 : front
	//glColor3f(0, 0, 1);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, sz);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, sz);


	// face 4 : right
	//glColor3f(1, 1, 0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, sz);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, sz, sz);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, 0.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);

	// face 5 : back
	//glColor3f(1, 0, 1);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, 0.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, 0.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, sz, 0.0f);


	// face 6 : 
	//glColor3f(0, 1, 1);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, sz, 0.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, sz, sz);
	glEnd();
}
void drawCylinder(double br, double tr, double h) {
	glPushMatrix();
	glRotatef(0.5, 1.0, 1.0, 1.0);
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, br, tr, h, 30, 30);
	// if do not delete, the program will crash eventually as the object will be incremented by time
	gluDeleteQuadric(cylinder);
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

GLuint loadTexture(LPCSTR filename) {
	//Take from step 1
	GLuint texture = 0;		//texture name

	//Step 3: Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	//Step 4: Assign texture to polygon
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//take from step 5
	DeleteObject(hBMP);

	return texture;
}
void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(0.1, 1.0, 1.0, 1.0);

	// Step 5 : Remove texture info
	//// Cube 1 : Box texture
	//textureArr[0] = loadTexture("Box.bmp");
	//drawCube(0.5);
	//glDeleteTextures(1, &textureArr[0]);

	//// Cube 2 : Box texture
	//textureArr[1] = loadTexture("ice.bmp");
	//drawCube(-0.5);
	//glDeleteTextures(1, &textureArr[1]);

	// Sphere : Box texture
	textureArr[0] = loadTexture("Box.bmp");
	drawSphere(0.19);
	glDeleteTextures(1, &textureArr[0]);

	// Cylinder : Ice texture
	textureArr[1] = loadTexture("ice.bmp");
	drawCylinder(0.2, 0.2, 0.8);
	glDeleteTextures(1, &textureArr[1]);

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