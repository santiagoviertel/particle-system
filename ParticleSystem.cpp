#include <stdlib.h>
#include "ParticleSystem_priv.hpp"

ParticleSystem::ParticleSystem(int particleNumber, int (*particleConstructorFunction)(void **particle), void (*particleDestructorFunction)(void **particle)) {
      if(particleConstructorFunction!=NULL&&particleConstructorFunction!=NULL) {
          ParticleSystem::array = (pParticle)malloc(particleNumber*sizeof(Particle));
          if(ParticleSystem::array!=NULL) {
              ParticleSystem::arraySize = particleNumber;
              ParticleSystem::particleConstructorFunction = particleConstructorFunction;
              ParticleSystem::particleDestructorFunction = particleDestructorFunction;
              for(int i=0;i<particleNumber;i+=1) {
                  ParticleSystem::array[i].activation = true;
                  if(particleConstructorFunction(&ParticleSystem::array[i].data) != SUCCESS_CREATION) {
                      for(i-=1;i>=0;i-=1)
                          particleDestructorFunction(&ParticleSystem::array[i].data);
                      free(ParticleSystem::array);
                      ParticleSystem::array = NULL;
                      ParticleSystem::arraySize = 0;
                      ParticleSystem::particleConstructorFunction = NULL;
                      ParticleSystem::particleDestructorFunction = NULL;
                      i = particleNumber;
                  }
              }
          }
          else {
              ParticleSystem::arraySize = 0;
              ParticleSystem::particleConstructorFunction = NULL;
              ParticleSystem::particleDestructorFunction = NULL;
          }
      }
      else {
          ParticleSystem::array = NULL;
          ParticleSystem::arraySize = 0;
          ParticleSystem::particleConstructorFunction = NULL;
          ParticleSystem::particleDestructorFunction = NULL;
      }
      ParticleSystem::continuity = false;
      ParticleSystem::visible = true;
      ParticleSystem::drawFunction = NULL;
      ParticleSystem::generationParticleFunction = NULL;
      ParticleSystem::killParticleFunction = NULL;
      ParticleSystem::refreshFunction = NULL;
}

void ParticleSystem::draw(void) {
     if(ParticleSystem::drawFunction!=NULL&&ParticleSystem::visible)
         for(int i=0;i<ParticleSystem::arraySize;i+=1)
             if(ParticleSystem::array[i].activation)
                 ParticleSystem::drawFunction(ParticleSystem::array[i].data);
}

bool ParticleSystem::isVisible(void) {
     return ParticleSystem::visible;
}

void ParticleSystem::refresh(void) {
     int i;
     if(ParticleSystem::refreshFunction!=NULL)
         for(i=0;i<ParticleSystem::arraySize;i+=1)
             if(ParticleSystem::array[i].activation)
                 ParticleSystem::refreshFunction(ParticleSystem::array[i].data);
     if(ParticleSystem::killParticleFunction!=NULL)
         for(i=0;i<ParticleSystem::arraySize;i+=1)
             if(ParticleSystem::array[i].activation)
                 if(ParticleSystem::killParticleFunction(ParticleSystem::array[i].data)==KILL_PARTICLE) {
                     if(ParticleSystem::continuity&&ParticleSystem::generationParticleFunction!=NULL)
                         ParticleSystem::generationParticleFunction(ParticleSystem::array[i].data);
                     else
                         ParticleSystem::array[i].activation = false;
                 }
}

void ParticleSystem::restart(void) {
     
}

void ParticleSystem::setContinuity(bool continuity) {
     ParticleSystem::continuity = continuity;
}

void ParticleSystem::setDrawFunction(void (*df)(void *particle)) {
     ParticleSystem::drawFunction = df;
}

void ParticleSystem::setGenerationParticleFunction(void (*gpf)(void *particle)) {
     ParticleSystem::generationParticleFunction = gpf;
     for(int i=0;i<ParticleSystem::arraySize;i+=1)
         ParticleSystem::generationParticleFunction(ParticleSystem::array[i].data);
}

void ParticleSystem::setKillParticleFunction(int (*kpf)(void *particle)) {
     ParticleSystem::killParticleFunction = kpf;
}

void ParticleSystem::setRefreshFunction(void (*rf)(void *particle)) {
     ParticleSystem::refreshFunction = rf;
}

void ParticleSystem::setVisible(bool visible) {
     ParticleSystem::visible = visible;
}

ParticleSystem::~ParticleSystem(void) {
      if(ParticleSystem::particleDestructorFunction!=NULL)
          for(int i=0;i<ParticleSystem::arraySize;i+=1)
              ParticleSystem::particleDestructorFunction(&ParticleSystem::array[i].data);
      if(ParticleSystem::array!=NULL)
          free(ParticleSystem::array);
}
