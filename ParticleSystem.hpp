#define SUCCESS_CREATION 1
#define ACTIVE_PARTICLE 2
#define CREATION_ERROR -1
#define KILL_PARTICLE -2

class ParticleSystem {
    public:
        //Funções
        ParticleSystem(int particleNumber, int (*particleConstructorFunction)(void **particle), void (*particleDestructorFunction)(void **particle));
        void draw(void);
        bool isVisible(void);
        void refresh(void);
        void restart(void);
        void setContinuity(bool continuity);
        void setDrawFunction(void (*df)(void *particle));
        void setGenerationParticleFunction(void (*gpf)(void *particle));
        void setKillParticleFunction(int (*kpf)(void *particle));
        void setRefreshFunction(void (*rf)(void *particle));
        void setVisible(bool visible);
        ~ParticleSystem(void);
};
