#include "World.h"

//�����V�~�����[�V����

void World::physicsSimulate() {
	//�O�͂�������
	applyForce();

	//�Փˌ��m
	detectCollision();
	
	//�S���̉���
	solveConstraints();
	
	//�ʒu�̍X�V
	integrate();
}

void World::add(Object &obj) {
	objects.push_back(obj);
}

/***private***/

void World::applyForce() {

}

void World::detectCollision() {

}

void World::solveConstraints() {

}

void World::integrate() {

}