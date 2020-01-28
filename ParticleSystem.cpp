#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(int numberParticles,int (*particleConstructorFunction)(void *&particle),void (*particleDestructorFunction)(void *&particle)) {
	if(particleConstructorFunction!=nullptr && particleDestructorFunction!=nullptr) {
		ParticleSystem::array.resize(numberParticles);
		ParticleSystem::particleConstructorFunction = particleConstructorFunction;
		ParticleSystem::particleDestructorFunction = particleDestructorFunction;
		for(int i=0;i<numberParticles;++i) {
			ParticleSystem::array[i].active = true;
			if(particleConstructorFunction(ParticleSystem::array[i].data) != CONSTRUCTION_SUCCEEDED) {
				for(--i;i>=0;--i)
					particleDestructorFunction(ParticleSystem::array[i].data);
				ParticleSystem::array.clear();
				ParticleSystem::particleConstructorFunction = nullptr;
				ParticleSystem::particleDestructorFunction = nullptr;
				break;
			}
		}
	} else {
		ParticleSystem::array.clear();
		ParticleSystem::particleConstructorFunction = nullptr;
		ParticleSystem::particleDestructorFunction = nullptr;
	}
	ParticleSystem::continuity = false;
	ParticleSystem::visible = true;
	ParticleSystem::drawFunction = nullptr;
	ParticleSystem::particleGenerationFunction = nullptr;
	ParticleSystem::particleKillFunction = nullptr;
	ParticleSystem::refreshFunction = nullptr;
}

void ParticleSystem::draw() {
	if(ParticleSystem::visible && ParticleSystem::drawFunction!=nullptr)
		for(int i=0;i<ParticleSystem::array.size();++i)
			if(ParticleSystem::array[i].active)
				ParticleSystem::drawFunction(ParticleSystem::array[i].data);
}

bool ParticleSystem::isVisible() {
	return ParticleSystem::visible;
}

void ParticleSystem::refresh() {
	int i;
	if(ParticleSystem::refreshFunction != nullptr)
		for(i=0;i<ParticleSystem::array.size();++i)
			if(ParticleSystem::array[i].active)
				ParticleSystem::refreshFunction(ParticleSystem::array[i].data);
	if(ParticleSystem::particleKillFunction != nullptr)
		for(i=0;i<ParticleSystem::array.size();++i)
			if(ParticleSystem::array[i].active)
				if(ParticleSystem::particleKillFunction(ParticleSystem::array[i].data) == DEAD_PARTICLE)
					if(ParticleSystem::continuity && ParticleSystem::particleGenerationFunction!=nullptr)
						ParticleSystem::particleGenerationFunction(ParticleSystem::array[i].data);
					else
						ParticleSystem::array[i].active = false;
}

void ParticleSystem::setContinuity(bool continuity) {
	ParticleSystem::continuity = continuity;
}

void ParticleSystem::setDrawFunction(void (*df)(const void *particle)) {
	ParticleSystem::drawFunction = df;
}

void ParticleSystem::setParticleGenerationFunction(void (*pgf)(const void *particle)) {
	ParticleSystem::particleGenerationFunction = pgf;
	for(int i=0;i<ParticleSystem::array.size();++i)
		ParticleSystem::particleGenerationFunction(ParticleSystem::array[i].data);
}

void ParticleSystem::setParticleKillFunction(int (*pkf)(const void *particle)) {
	ParticleSystem::particleKillFunction = pkf;
}

void ParticleSystem::setRefreshFunction(void (*rf)(const void *particle)) {
	ParticleSystem::refreshFunction = rf;
}

void ParticleSystem::setVisible(bool visible) {
	ParticleSystem::visible = visible;
}

ParticleSystem::~ParticleSystem() {
	if(ParticleSystem::particleDestructorFunction != nullptr)
		for(int i=0;i<ParticleSystem::array.size();++i)
			ParticleSystem::particleDestructorFunction(ParticleSystem::array[i].data);
}