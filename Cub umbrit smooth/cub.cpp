#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static int angle = 0;

void myInit()
{
	// setari pentru sursa de lumina
	// intensitatea componentei ambientale din sursa 0 este nula
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	// intensitatea componentei difuze din sursa 0 este maxima pentru fiecare componenta de culoare
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// intensitatea componentei speculare din sursa 0 este maxima pentru fiecrae compopnenta de culoare
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	// pozitia sursei de lumina nu este cea implicita
	GLfloat light_position[] = { 0.0, 1.0, 0.0, 0.0 };
	// sursa de lumina pe axa x la infinit
	GLfloat global_ambient[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// lumina ambientala in scena

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	glFrontFace(GL_CW); // orientarea implicita a varfurilor in sensul rotirii acelor
	glEnable(GL_LIGHTING); // activare iluminare
	glEnable(GL_LIGHT0); // activare sursa 0

	glEnable(GL_AUTO_NORMAL); // activare calculare normale daca varfurile s-au determinat cu GL_MAP2_VERTEX_3 sau GL_MAP2_VERTEX_4
	glEnable(GL_NORMALIZE); // activare normalizare (vectori unitari) vectori
glEnable(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST); // activare test adancime
	
}



void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0, 0.0, -4.0);
	glRotatef(angle, 1.0, 0.0, 1.0);

	auxSolidCube(1.0);
	glColor3f(1.0, 0.0, 1.0);

	auxSwapBuffers();
}


void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 3.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
}

void CALLBACK IdleFunction()
{
	angle += 1;
	display();
	Sleep(1000/60);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_DOUBLE | AUX_RGB | AUX_DEPTH);
	auxInitPosition(200, 100, 800, 600);
	auxInitWindow("CUB");
	myInit();
	auxReshapeFunc(myReshape);
	auxIdleFunc(IdleFunction);
	auxMainLoop(display);
	return 0;
}
