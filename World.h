#pragma once
#include "Line.h"
#include "Circle.h"
#include "Box.h"
#include "Pair.h"
#include <random>

//�����V�~�����[�V�����N���X

class World {
private:
	const float gravity = 9.8f;//�d�͉����x
	float TIME_STEP;
	
	void applyForce();
	void detectCollision();
	void solveConstraints();
	void integrate();
public:
	World(float timeStep = float(0.1));
	std::vector<Object*> objects;
	void initialize();
	void physicsSimulate();
	void add(Object*);
};