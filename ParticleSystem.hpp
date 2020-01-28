#ifndef __ParticleSystem_HPP__
#define __ParticleSystem_HPP__

#include <vector>

#define CONSTRUCTION_SUCCEEDED	1
#define CONSTRUCTION_FAILED		-1
#define ACTIVE_PARTICLE			2
#define DEAD_PARTICLE			-2

class Particle {
	public:
		void *data;
		bool active;
};

class ParticleSystem {
	private:
		std::vector<Particle> array;
		bool continuity;
		bool visible;
		int (*particleConstructorFunction)(void *&particle);
		void (*particleDestructorFunction)(void *&particle);
		void (*drawFunction)(const void *particle);
		void (*particleGenerationFunction)(const void *particle);
		int (*particleKillFunction)(const void *particle);
		void (*refreshFunction)(const void *particle);

	public:
		ParticleSystem(int numberParticles,int (*particleConstructorFunction)(void *&particle),void (*particleDestructorFunction)(void *&particle));
		void draw();
		bool isVisible();
		void refresh();
		void setContinuity(bool continuity);
		void setDrawFunction(void (*df)(const void *particle));
		void setParticleGenerationFunction(void (*pgf)(const void *particle));
		void setParticleKillFunction(int (*pkf)(const void *particle));
		void setRefreshFunction(void (*rf)(const void *particle));
		void setVisible(bool visible);
		~ParticleSystem();
};

#endif