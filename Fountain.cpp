#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include "ParticleSystem.hpp"

#define ANGULO10	(5000.0f*M_PI)/9.0f
#define ANGULO80	(40000.0f*M_PI)/9.0f
#define ANGULO360	2000.0f*M_PI

float deltaTime = 0.0f;

void setDeltaTime(float dt) {
	deltaTime = dt;
	srand(rand());
}

class Info {
	public:
		float position[3];
		float initialPosition[3];
		float initialVelocity[3];
		float time;
};

void drawFunction(const void *particle) {
	glVertex3f(((Info*)particle)->position[0],((Info*)particle)->position[1],((Info*)particle)->position[2]);
}

int particleConstructor(void *&particle) {
	if((particle = new Info())!=nullptr)
		return CONSTRUCTION_SUCCEEDED;
	return CONSTRUCTION_FAILED;
}

void particleDestructor(void *&particle) {
	delete (Info*)particle;
}

void refreshFunction(const void *particle) {
	((Info*)particle)->time += deltaTime;
	((Info*)particle)->position[0] = ((Info*)particle)->initialPosition[0] + ((Info*)particle)->initialVelocity[0]*((Info*)particle)->time;
	((Info*)particle)->position[1] = ((Info*)particle)->initialPosition[1] + ((Info*)particle)->initialVelocity[1]*((Info*)particle)->time - 5.0f*((Info*)particle)->time*((Info*)particle)->time;
	((Info*)particle)->position[2] = ((Info*)particle)->initialPosition[2] + ((Info*)particle)->initialVelocity[2]*((Info*)particle)->time;
}

void particleGenerationFunction(const void *particle) {
	((Info*)particle)->position[0] = 0.0f;
	((Info*)particle)->position[1] = 0.21f;
	((Info*)particle)->position[2] = 0.0f;
	((Info*)particle)->initialPosition[0] = ((Info*)particle)->position[0];
	((Info*)particle)->initialPosition[1] = ((Info*)particle)->position[1];
	((Info*)particle)->initialPosition[2] = ((Info*)particle)->position[2];
	srand(rand());
	float velocity = 6.0f + ((float)(rand()%4000))/1000.0f;
	srand(rand());
	float angle = (ANGULO80 + ((float)(rand()%(int)ANGULO10)))/10000.0f;
	srand(rand());
	float angle1 = ((float)(rand()%(int)ANGULO360))/1000.0f;
	((Info*)particle)->initialVelocity[0] = velocity*cos(angle);
	((Info*)particle)->initialVelocity[1] = velocity*sin(angle);
	((Info*)particle)->initialVelocity[2] = ((Info*)particle)->initialVelocity[0]*sin(angle1);
	((Info*)particle)->initialVelocity[0] *= cos(angle1);
	((Info*)particle)->time = 0.0f;
}

int particleKillFunction(const void *particle) {
	if(((Info*)particle)->position[1]<0.0f)
		return DEAD_PARTICLE;
	return ACTIVE_PARTICLE;
}