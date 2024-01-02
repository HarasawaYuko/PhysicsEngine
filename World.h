#pragma once
#include <random>

#include "Circle.h"
#include "Pair.h"

//物理シミュレーションクラス

class World {
private:
	const float gravity = 200.8f;//重力加速度
	float TIME_STEP;
	uint16_t totalNum;//通算で追加したオブジェクトの数　65536以上になったら一旦リセットする必要あり
	int objNum;//world内にあるオブジェクトの数

	void applyForce();
	void detectCollision();
	void solveConstraints();
	void integrate();
public:
	World(float timeStep = 1.f/(float)FPS);
	std::vector<Collision> collisions;
	std::vector<Object*> objects;
	std::vector<Pair> pairs;
	void initialize();
	void physicsSimulate();
	void add(Object*);
};