#include "World.h"

//物理シミュレーション

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