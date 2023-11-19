#pragma once
#include <random>

#include "Line.h"
#include "Circle.h"
#include "Box.h"
#include "Pair.h"
#include "detect.h"
#include "Collision.h"

//物理シミュレーションクラス

class World {
private:
	const float gravity = 3.8f;//重力加速度
	float TIME_STEP;
	std::vector<Collision> collisions;

	
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