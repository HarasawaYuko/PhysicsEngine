#include "World.h"

//�����V�~�����[�V����

World::World(float timeStep) {
	TIME_STEP = timeStep;
}

void World::initialize() {

}

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

void World::add(Object* obj) {
	objects.push_back(obj);
}

/***private***/
//�͂�������
void World::applyForce() {
	//�d�͉����x���v�Z
	float acc = -gravity * TIME_STEP;
	printfDx("ac;%f\n", acc);
	for (Object* obj : objects) {
		obj->addV(Vec2(0, acc));
	}
}

void World::detectCollision() {

}

void World::solveConstraints() {

}

void World::integrate() {
	auto itr = objects.begin();
	while (itr != objects.end())
	{
		//clsDx();
		printfDx("velo;%f" , (*itr)->getV().y);
		(*itr)->updatePos(TIME_STEP);
		if (!(*itr)->isValid())
		{
			itr = objects.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}