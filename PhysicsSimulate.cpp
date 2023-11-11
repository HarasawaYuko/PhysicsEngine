#include "PhysicsSimulate.h"
void applyForce();
void detectCollision();
void solveConstraints();
void integrate();

void physicsSimulate() {
	//外力を加える
	applyForce();

	//衝突検知
	detectCollision();
	
	//拘束の解消
	solveConstraints();
	
	//位置の更新
	integrate();
}