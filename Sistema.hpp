/*Funções para atualização do Sistema de Partículas*/
void setDeltaTime(float dt);
/*Funções pertencentes ao Sistema de Partículas*/
void drawFunction(void *particle);
int particleConstructor(void **particle);
void particleDestructor(void **particle);
void refreshFunction(void *particle);
void generationParticleFunction(void *particle);
int killParticleFunction(void *particle);
