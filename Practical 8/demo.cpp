#pragma comment (lib, "GLU32.lib")
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <corecrt_math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical Demo 5B"

int qNo = 1;


//Projection
float tz = 0, tspeed = 0.01, tx = 0, ty = 0;
bool isOrtho = true;					// Is orthorgraphic View?
float ONear = -10.0, OFar = 10.0;		//Ortho near and Far
float PNear = 4.0, PFar = 21.0;			//Perspective Near and Far
float ptx = 0, pty = 0, ptSpeed = 0.1;  //traslate for projection
float pry = 0, prSpeed = 2;				//rotate y for projection

//Lighting
float degree = 0;
float dSpeed = 0;
float px = 1, py = 1, pz = 1, pSpeed = 1, rSpeed = 0;
float amb[3] = { 1.0,1.0,1.0 };			//white color ambient light
float posA[3] = { 0.0,6.0, 0.0 };		//position for lighting{0,6,0}
float dif[3] = { 1.0,1.0,1.0 };			//white color dif light
float posB[3] = { 6,0, 0 };		//position for lighting{6,0,0}
float ambM[3] = { 0.0, 0.0, 1.0 };		//red color amb material
float difM[3] = { 1.0, 0.0, 0.0 };		//red color dif material
bool isLightOn = false;					//is light on ?


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
		else if (wParam == VK_UP) {
			dSpeed += 0.01;

		}
		else if (wParam == VK_DOWN) {
			dSpeed -= 0.01;
		}
		else if (wParam == VK_SPACE)
			isLightOn = !isLightOn;
		else if (wParam == 'W') {
			py += pSpeed;

		}
		else if (wParam == 'S') {
			py -= pSpeed;
		}
		else if (wParam == 'A') {
			px -= pSpeed;
		}
		else if (wParam == 'D') {
			px += pSpeed;
		}
		else if (wParam == 'E') {
			pz += pSpeed;

		}
		else if (wParam == 'Q') {
			pz -= pSpeed;

		}
		else if (wParam == 0x31)
			qNo = 1;
		else if (wParam == 0x32)
			qNo = 2;

		break;

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
void drawSphereWithoutGLU()
{
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = 0.5;
	int sliceNo = 30, stackNo = 30;
	for (sliceA = 0.0; sliceA < PI; sliceA += PI / sliceNo)
	{
		glBegin(GL_LINE_STRIP);
		for (stackA = 0.0; stackA < PI; stackA += PI / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void DrawSphere(double r) {


	GLUquadricObj* sphere = NULL;
	glPointSize(2);
	sphere = gluNewQuadric();


	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, r, 30, 30);
	gluDeleteQuadric(sphere);

}

void DrawCylinder(double br, double tr, double h) {


	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	glColor3f(1, 0, 0);
	gluCylinder(cylinder, br, tr, h, 10, 10);
	gluDeleteQuadric(cylinder);
}

void DrawPyramid(float sz, float h) {
	glBegin(GL_POLYGON);

	//Bottom
	glVertex3f(sz, 0, sz);
	glVertex3f(-sz, 0, sz);
	glVertex3f(-sz, 0, -sz);
	glVertex3f(sz, 0, -sz);

	//back
	glVertex3f(sz, 0, -sz);
	glVertex3f(-sz, 0, -sz);
	glVertex3f(0, h, 0);

	//right
	glVertex3f(0, h, 0);
	glVertex3f(sz, 0, -sz);
	glVertex3f(sz, 0, sz);

	//front
	glVertex3f(sz, 0, sz);
	glVertex3f(0, h, 0);
	glVertex3f(-sz, 0, sz);

	//left
	glVertex3f(-sz, 0, sz);
	glVertex3f(0, h, 0);
	glVertex3f(-sz, 0, -sz);


	glEnd();

}

void projection() {
	glMatrixMode(GL_PROJECTION);  //refer to porjetion matrix
	glLoadIdentity();				// reset to project matrix

	glTranslatef(ptx, pty, 0);		//translate for projection matrix
	glRotatef(pry, 0.0, 1.0, 0.0);		//rotate y-axis for projection

	if (isOrtho) {
		//Ortho View
		glOrtho(-10.0, 10.0, -10.0, 10.0, ONear, OFar);
	}
	else {
		//Perspective View
		gluPerspective(20, 1.0, -1, 1);
		glFrustum(-10.0, 10.0, -10.0, 10.0, PNear, PFar);
	}

}

void shadow() {
	//squish matrix based on the light pos(px,py,pz)
	GLfloat squishMat[16] =
	{ py,-px,0,0,
		0,0,0,0,
		0,-pz,py,0,
		0,-1,0,py

	};

	glPushMatrix();
	glTranslatef(0.0f, 0.9f, 0.0f); //move slight up on plane
	glMultMatrixf(squishMat);	//mutiply  with the mode
	glRotatef(30, 1, 0, 0);	//transformation for plane
	glDisable(GL_LIGHTING);
	glColor3f(0.1, 0.1, 0.1);	//black

	DrawSphere(1.5);// shadow polugon
	glEnable(GL_LIGHTING);
	glPopMatrix();

}

void lighting() {
	if (isLightOn) {
		//enable lighting for the whole scene
		glEnable(GL_LIGHTING);
		shadow();
	}
	else {
		//disable lighting for the whole scene
		glDisable(GL_LIGHTING);
	}


	//Light 0 : Red Color amb light at pos (0,6,0) above
	//glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	//glLightfv(GL_LIGHT0, GL_POSITION, posA);
	//glEnable(GL_LIGHT0); //on the light


	//Light 1 : green color dif light at pos (6,0,0) above
	glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT1, GL_POSITION, posB);
	glEnable(GL_LIGHT1);


}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clear screen
	glEnable(GL_DEPTH_TEST);



	posB[0] = px;
	posB[1] = py;
	posB[2] = pz;

	projection();	//projection
			//lighting
	//reset to modelview matrix

	//glTranslatef(tx, ty, tz);		//tranlate along the z-axis

	//red color amb material
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambM);

	//red color dif material
	lighting();
	glMatrixMode(GL_MODELVIEW);		//refer to modelview Matrix
	//degree += dSpeed;
	glLoadIdentity();
	//glRotatef(degree,-1,-1,-1);

	//plane

	glPushMatrix();
	glLoadIdentity();
	glRotatef(30, 1, 0, 0);
	glTranslatef(0, 5, 0);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, difM);
	glColor3f(0, 1, 1);		//if on light, you will see the color of light rather than the original color of object.
	DrawSphere(1.5);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glLoadIdentity();
	glRotatef(30, 1, 0, 0);
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(6, 0, 6);
	glVertex3f(6, 0, -6);
	glVertex3f(-6, 0, -6);
	glVertex3f(-6, 0, 6);
	glEnd();
	glPopMatrix();


	//degree += dSpeed;

	/*glDisable(GL_LIGHTING);
	glLoadIdentity();
	glRotatef(degree, 1, 1, 1);
	glTranslatef(px, py, pz);

	glColor3f(0, 1, 1);
	DrawSphere(0.5);*/




}

void displayPyramid() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clear screen
	glEnable(GL_DEPTH_TEST);



	posB[0] = px;
	posB[1] = py;
	posB[2] = pz;

	projection();	//projection
	lighting();			//lighting
	//reset to modelview matrix

	//glTranslatef(tx, ty, tz);		//tranlate along the z-axis

	//red color amb material
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambM);
	//red color dif material
	glPushMatrix();
	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difM);
	glColor3f(0, 1, 1);		//if on light, you will see the color of light rather than the original color of object.
	DrawPyramid(3, 3);
	glPopMatrix();

	degree += dSpeed;


	glDisable(GL_LIGHTING);
	glLoadIdentity();
	glRotatef(degree, 1, 1, 1);
	glTranslatef(px, py, pz);

	glColor3f(0, 1, 1);
	DrawSphere(0.5);

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
		if (qNo == 1) {
			display();
		}
		else if (qNo == 2) {
			displayPyramid();
		}


		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------