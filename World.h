#pragma once
#include <random>

#include "Line.h"
#include "Circle.h"
#include "Box.h"
#include "Pair.h"

//物理シミュレーションクラス

class World {
private:
	const float gravity = 200.8f;//重力加速度
	float TIME_STEP;
	uint16_t num;//通算で追加したオブジェクトの数　65536以上になったら一旦リセットする必要あり
	int objNum;

	void applyForce();
	void detectCollision();
	void solveConstraints();
	void integrate();
public:
	World(float timeStep = 1.f/FPS);
	std::vector<Collision> collisions;
	std::vector<Object*> objects;
	std::vector<Pair> pairs;
	void initialize();
	void physicsSimulate();
	void add(Object*);
};