#pragma once
#include <random>

#include "Line.h"
#include "Circle.h"
#include "Box.h"
#include "Pair.h"
#include "detect.h"
#include "Collision.h"
#include "Solver.h"

//物理シミュレーションクラス

class World {
private:
	const float gravity = 1.8f;//重力加速度
	float TIME_STEP;

	void applyForce();
	void detectCollision();
	void solveConstraints();
	void integrate();
public:
	World(float timeStep = 1.f/FPS);
	std::vector<Collision> collisions;
	std::vector<Object*> objects;
	void initialize();
	void physicsSimulate();
	void add(Object*);
};