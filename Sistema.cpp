#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include "ParticleSystem.hpp"

//Número randômico máximo: 32767
#define ANGULO10 (5000*M_PI)/9
#define ANGULO80 (40000*M_PI)/9
#define ANGULO360 2000*M_PI

/*Funções e variáveis para atualização do Sistema de Partículas*/
float deltaTime = 0.0f;

void setDeltaTime(float dt)
{
     deltaTime = dt;
     srand(rand());
}

/*Funções pertencentes ao Sistema de Partículas*/
typedef struct {
        float posicao[3];
        float posicao_inicial[3];
        float velocidade_inicial[3];
        float tempo;
} Info;

void drawFunction(void *particle)
{
     glVertex3f(((Info*)particle)->posicao[0],((Info*)particle)->posicao[1],((Info*)particle)->posicao[2]);
}

int particleConstructor(void **particle)
{
    if((*particle = (Info*)malloc(sizeof(Info)))!=NULL)
        return SUCCESS_CREATION;
    return CREATION_ERROR;
}

void particleDestructor(void **particle)
{
     free(*particle);
}

void refreshFunction(void *particle)
{
     ((Info*)particle)->tempo += deltaTime;
     ((Info*)particle)->posicao[0] = ((Info*)particle)->posicao_inicial[0] + ((Info*)particle)->velocidade_inicial[0]*((Info*)particle)->tempo;
     ((Info*)particle)->posicao[1] = ((Info*)particle)->posicao_inicial[1] + ((Info*)particle)->velocidade_inicial[1]*((Info*)particle)->tempo - 5*(float)((Info*)particle)->tempo*((Info*)particle)->tempo;
     ((Info*)particle)->posicao[2] = ((Info*)particle)->posicao_inicial[2] + ((Info*)particle)->velocidade_inicial[2]*((Info*)particle)->tempo;
}

void generationParticleFunction(void *particle)
{
     ((Info*)particle)->posicao[0] = 0.0f;
     ((Info*)particle)->posicao[1] = 0.21f;
     ((Info*)particle)->posicao[2] = 0.0f;
     ((Info*)particle)->posicao_inicial[0] = ((Info*)particle)->posicao[0];
     ((Info*)particle)->posicao_inicial[1] = ((Info*)particle)->posicao[1];
     ((Info*)particle)->posicao_inicial[2] = ((Info*)particle)->posicao[2];
     srand(rand());
     float velocity = 6.0f + (float)(rand()%4000)/1000;
     srand(rand());
     float angle = (float)(ANGULO80 + (rand()%(int)ANGULO10))/10000;
     srand(rand());
     float angle1 = (float)(rand()%(int)ANGULO360)/1000;
     ((Info*)particle)->velocidade_inicial[0] = velocity*cos(angle);
     ((Info*)particle)->velocidade_inicial[1] = velocity*sin(angle);
     ((Info*)particle)->velocidade_inicial[2] = ((Info*)particle)->velocidade_inicial[0]*sin(angle1);
     ((Info*)particle)->velocidade_inicial[0] *= cos(angle1);
     ((Info*)particle)->tempo = 0.0f;
}

int killParticleFunction(void *particle)
{
     if(((Info*)particle)->posicao[1]<0.0f)
         return KILL_PARTICLE;
     return ACTIVE_PARTICLE;
}
