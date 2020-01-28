void setDeltaTime(float dt);

void drawFunction(const void *particle);
int particleConstructor(void *&particle);
void particleDestructor(void *&particle);
void refreshFunction(const void *particle);
void particleGenerationFunction(const void *particle);
int particleKillFunction(const void *particle);