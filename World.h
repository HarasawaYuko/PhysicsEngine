#pragma once
#include"Object.h"

//物理シミュレーションクラス

class World {
private:
	const float gravity = 9.8f;//重力加速度
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