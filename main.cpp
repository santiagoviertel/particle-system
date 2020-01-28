#include <math.h>
#include <time.h>
#include <chrono>
#include <GL/glut.h>
#include "ParticleSystem.hpp"
#include "Fountain.hpp"

#define WIDTH	640
#define HEIGHT	480
#define FATIA	M_PI/36.0f

using namespace std::chrono;

ParticleSystem *ps;

GLfloat groundAmbientLight[] =	{0.0f,0.0f,0.0f,0.0f};
GLfloat groundDiffuseLight[] =	{0.1f,0.35f,0.1f,1.0f};
GLfloat groundSpecularLight[] =	{0.45f,0.55f,0.45f,1.0f};
GLfloat groundShininessLight =	0.25f;

GLfloat fontAmbientLight[] =	{0.25f,0.25f,0.25f,1.0f};
GLfloat fontDiffuseLight[] =	{0.4f,0.4f,0.4f,1.0f};
GLfloat fontSpecularLight[] =	{0.774597f,0.774597f,0.774597f,1.0f};
GLfloat fontShininessLight =	0.6f;

GLfloat creationAreaAmbientLight[] =	{0.329412f,0.223529f,0.027451f,1.0f};
GLfloat creationAreaDiffuseLight[] =	{0.780392f,0.568627f,0.113725f,1.0f};
GLfloat creationAreaSpecularLight[] =	{0.992157f,0.941176f,0.807843f,1.0f};
GLfloat creationAreaShininessLight =	0.21794872f;

GLfloat waterAmbientLight[] =	{0.1f,0.18725f,0.1745f,1.0f};
GLfloat waterDiffuseLight[] =	{0.396f,0.74151f,0.69102f,1.0f};
GLfloat waterSpecularLight[] =	{0.297254f,0.30829f,0.306678f,1.0f};
GLfloat waterShininessLight =	0.1f;

void draw() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glBegin(GL_QUADS);
		//Ground
		glMaterialfv(GL_FRONT,GL_AMBIENT,groundAmbientLight);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,groundDiffuseLight);
		glMaterialfv(GL_FRONT,GL_SPECULAR,groundSpecularLight);
		glMaterialf(GL_FRONT,GL_SHININESS,groundShininessLight);
		glNormal3f(0.0f,1.0f,0.0f);
		glVertex3f(-5.0f,0.0f,5.0f);
		glVertex3f(5.0f,0.0f,5.0f);
		glVertex3f(5.0f,0.0f,-5.0f);
		glVertex3f(-5.0f,0.0f,-5.0f);

		//Fountain
		glMaterialfv(GL_FRONT,GL_AMBIENT,fontAmbientLight);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,fontDiffuseLight);
		glMaterialfv(GL_FRONT,GL_SPECULAR,fontSpecularLight);
		glMaterialf(GL_FRONT,GL_SHININESS,fontShininessLight);

		glVertex3f(-3.0f,0.01f,3.0f);
		glVertex3f(3.0f,0.01f,3.0f);
		glVertex3f(3.0f,0.01f,-3.0f);
		glVertex3f(-3.0f,0.01f,-3.0f);

		glVertex3f(-1.0f,0.2f,1.0f);
		glVertex3f(1.0f,0.2f,1.0f);
		glVertex3f(1.0f,0.2f,-1.0f);
		glVertex3f(-1.0f,0.2f,-1.0f);

		glNormal3f(0.0f,0.0f,-1.0f);
		glVertex3f(1.0f,0.2f,-1.0f);
		glVertex3f(-1.0f,0.2f,-1.0f);
		glVertex3f(-1.0f,0.01f,-1.0f);
		glVertex3f(1.0f,0.01f,-1.0f);

		glNormal3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.2f,1.0f);
		glVertex3f(1.0f,0.2f,-1.0f);
		glVertex3f(1.0f,0.01f,-1.0f);
		glVertex3f(1.0f,0.01f,1.0f);

		glNormal3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f,0.2f,1.0f);
		glVertex3f(1.0f,0.2f,1.0f);
		glVertex3f(1.0f,0.01f,1.0f);
		glVertex3f(-1.0f,0.01f,1.0f);

		glNormal3f(-1.0f,0.0f,0.0f);
		glVertex3f(-1.0f,0.2f,1.0f);
		glVertex3f(-1.0f,0.2f,-1.0f);
		glVertex3f(-1.0f,0.01f,-1.0f);
		glVertex3f(-1.0f,0.01f,1.0f);
	glEnd();

	//Water source
	glNormal3f(0.0f,1.0f,0.0f);
	glMaterialfv(GL_FRONT,GL_AMBIENT,creationAreaAmbientLight);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,creationAreaDiffuseLight);
	glMaterialfv(GL_FRONT,GL_SPECULAR,creationAreaSpecularLight);
	glMaterialf(GL_FRONT,GL_SHININESS,creationAreaShininessLight);
	glBegin(GL_POLYGON);
		for(float i=0.0f;i<2*M_PI;i+=FATIA)
			glVertex3f(sin(i),0.21f,cos(i));
	glEnd();

	//Water drops
	glNormal3f(-1.0f,0.0f,0.0f);
	glMaterialfv(GL_FRONT,GL_AMBIENT,waterAmbientLight);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,waterDiffuseLight);
	glMaterialfv(GL_FRONT,GL_SPECULAR,waterSpecularLight);
	glMaterialf(GL_FRONT,GL_SHININESS,waterShininessLight);
	glBegin(GL_POINTS);
		ps->draw();
	glEnd();

	glutSwapBuffers();
}

void refresh() {
	static high_resolution_clock::time_point curr;
	static high_resolution_clock::time_point prev = high_resolution_clock::now();
	duration<float,std::ratio<1>> deltaTime;
	curr = high_resolution_clock::now();
	deltaTime = curr - prev;
	prev = curr;
	setDeltaTime(deltaTime.count());
	ps->refresh();
	glutPostRedisplay();
}

void init(int &argc,char** argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Particle System");

	glViewport(0,0,WIDTH,HEIGHT);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);
	gluLookAt(-5.0f,8.0f,-10.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);

	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f,0.0f,0.0f,0.5f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);

	GLfloat direction[] = {-0.57735f,-0.57735f,-0.577350f,0.0f};
	GLfloat light_ambient[] = {0.5f,0.5f,0.5f,1.0f};
	GLfloat light_diffuse[] = {0.5f,0.5f,0.5f,1.0f};
	GLfloat light_specular[] = {0.5f,0.5f,0.5f,1.0f};
	glLightfv(GL_LIGHT0,GL_POSITION,direction);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	glEnable(GL_LIGHT0);

	GLfloat position[] = {-5.0f,8.0f,-10.0f,1.0f};
	glLightfv(GL_LIGHT1,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light_specular);
	glLightfv(GL_LIGHT1,GL_POSITION,position);
	glEnable(GL_LIGHT1);

	glutDisplayFunc(draw);
	glutIdleFunc(refresh);
	glutMainLoop();
}

int main(int argc,char** argv) {
	srand(time(NULL));
	ps = new ParticleSystem(7549,particleConstructor,particleDestructor);
	ps->setDrawFunction(drawFunction);
	ps->setRefreshFunction(refreshFunction);
	ps->setParticleGenerationFunction(particleGenerationFunction);
	ps->setParticleKillFunction(particleKillFunction);
	ps->setContinuity(true);

	init(argc,argv);

//	delete(ps);
	return 0;
}