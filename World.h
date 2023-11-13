#pragma once
#include"Object.h"

//�����V�~�����[�V�����N���X

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