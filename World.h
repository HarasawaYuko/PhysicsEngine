#pragma once
#include <random>

#include "Line.h"
#include "Circle.h"
#include "Box.h"
#include "Pair.h"

//�����V�~�����[�V�����N���X

class World {
private:
	const float gravity = 200.8f;//�d�͉����x
	float TIME_STEP;
	uint16_t num;//�ʎZ�Œǉ������I�u�W�F�N�g�̐��@65536�ȏ�ɂȂ������U���Z�b�g����K�v����
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