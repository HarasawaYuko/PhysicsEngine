#pragma once
#include"Object.h"

//物理シミュレーションクラス

class World {
private:
	void applyForce();
	void detectCollision();
	void solveConstraints();
	void integrate();
public:
	std::vector<Object> objects;
	void physicsSimulate();
	void add(Object&);
};