#include "World.h"

//物理シミュレーション

World::World(float timeStep) {
	TIME_STEP = timeStep;
}

void World::initialize() {

}

void World::physicsSimulate() {
	//外力を加える
	applyForce();

	//衝突検知
	detectCollision();
	
	//拘束の解消
	solveConstraints();
	
	//位置の更新
	integrate();
}

void World::add(Object* obj) {
	objects.push_back(obj);
}

/***private***/
//力を加える
void World::applyForce() {
	//重力加速度を計算
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