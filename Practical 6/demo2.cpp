#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

// #pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 5B Demo"
float tx = 0.0, tz = 0.0, tSpeed = 1.0;		// translate for modelview
bool isOrtho = true;						// is orthographic view?
float ONear = -10.0, OFar = 10.0;			// Ortho near and far
float PNear = 1.0, PFar = 21.0;				// Perspective zmin & zmax
float ptx = 0, pty = 0, ptSpeed = 0.1;		// translate for projection
float pry = 0.2, prSpeed = 1.0;				// rotation in y for projection

//lightning
float amb[3] = { 1.0,0.0,0.0 }; //ambient light
float pos[3] = { 0.0,6.0,0.0 }; //light position
float dif[3] = { 0.0,1.0,0.0 }; //gree colour diffuse light
float posD[3] = { 6.0,0.0,0.0 }; //dif light pos(6,0,0)

//material
float ambM[3] = { 1.0,0.0,0.0 }; //red colour ambient material
float difM[3] = { 1.0,0.0,0.0 };

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
		else if (wParam == VK_UP) {
			// limit the movement in the z axis within the view volume so that it wont disappear
			if (isOrtho) {
				if (tz > ONear)
					tz -= tSpeed;
			}
			else {
				if (tz > PNear + 3.0)
					tz -= tSpeed;
			}
		}
		else if (wParam == VK_DOWN) {
			if (isOrtho) {
				if (tz < OFar)
					tz += tSpeed;
			}
			else {
				if (tz < PFar / 2)
					tz += tSpeed;
			}
		}
		else if (wParam == 'O') {
			isOrtho = true;
			tz = 0; // reset
		}
		else if (wParam == 'P') {
			isOrtho = false;
			tz = 2.0; // reset, exact value (1.0 + 1) check back frustum
		}
		else if (wParam == 'A') {
			ptx -= ptSpeed;
		}
		else if (wParam == 'D') {
			ptx += ptSpeed;
		}
		else if (wParam == VK_LEFT) {
			tx -= tSpeed;
		}
		else if (wParam == VK_RIGHT) {
			tx += tSpeed;
		}
		else if (wParam == 'L') {
			pry += prSpeed;
		}
		else if (wParam == 'R') {
			pry -= prSpeed;
		}
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
	gluSphere(sphere, r, 30, 30);
	// if do not delete, the program will crash eventually as the object will be incremented by time
	gluDeleteQuadric(sphere);
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

void projection() {
	glMatrixMode(GL_PROJECTION); // refer to projection matrix
	glLoadIdentity(); // reset projection
	glTranslatef(ptx, pty, 0);
	glRotatef(pry, 0.0, 1.0, 0.0);		// ry for projection
	if (isOrtho) {
		// ortho view
		glOrtho(-10.0, 10.0, -10.0, 10.0, ONear, OFar); // ortho projection
	}
	else {
		gluPerspective(20, 1.0, -1.0, 1.0);
		glFrustum(-10.0, 10.0, -10.0, 10.0, PNear, PFar);
	}


}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	projection();

	glEnable(GL_LIGHTING);

	//light 0: red colour ambient light
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHT0);

	//light 1: red colour ambient light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT1, GL_POSITION, posD);
	glEnable(GL_LIGHT1);

	// now have 2 matrix, specify to move model view or projection view
	glMatrixMode(GL_MODELVIEW); // refer to model view matrix
	//after enable lightning the sphere colour will not show, only the lightning colour will be shown
	glLoadIdentity(); // reset modelview matrix
	glTranslatef(tx, 0.0, tz); // translate along the z-axis

	//red ambient material
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambM);

	//red diffuse material
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difM);

	drawSphere(5.0);

	glPopMatrix();

	glRotatef(0.02, 0.0, 1.0, 0);

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