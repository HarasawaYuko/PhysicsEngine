#pragma once
#include <random>

#include "Circle.h"
#include "Pair.h"

//�����V�~�����[�V�����N���X

class World {
private:
	const float gravity = 200.8f;//�d�͉����x
	float TIME_STEP;
	uint16_t totalNum;//�ʎZ�Œǉ������I�u�W�F�N�g�̐��@65536�ȏ�ɂȂ������U���Z�b�g����K�v����
	int objNum;//world���ɂ���I�u�W�F�N�g�̐�

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