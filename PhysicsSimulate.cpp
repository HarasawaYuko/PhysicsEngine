#include "PhysicsSimulate.h"
void applyForce();
void detectCollision();
void solveConstraints();
void integrate();

void physicsSimulate() {
	//�O�͂�������
	applyForce();

	//�Փˌ��m
	detectCollision();
	
	//�S���̉���
	solveConstraints();
	
	//�ʒu�̍X�V
	integrate();
}