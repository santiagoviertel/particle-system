/*Fun��es para atualiza��o do Sistema de Part�culas*/
void setDeltaTime(float dt);
/*Fun��es pertencentes ao Sistema de Part�culas*/
void drawFunction(void *particle);
int particleConstructor(void **particle);
void particleDestructor(void **particle);
void refreshFunction(void *particle);
void generationParticleFunction(void *particle);
int killParticleFunction(void *particle);
