#include "World.h"

//物理シミュレーション

World::World(float timeStep)
{
	TIME_STEP = timeStep;
}

void World::initialize() {
	//床の作成
	Line* wall_under = new Line(Vec2(30 ,30), Vec2(770 , 30), false);
	add(wall_under);
	//円の配置
	Circle* cir1 = new Circle(300, 500, 50);
	add(cir1);
	//長方形の配置
	Box* box1 = new Box(400 , 500 , 60 , 70 );
	add(box1);
}

void World::physicsSimulate() {
	//printfDx("size: %d \n" , objects.size());
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
	std::sort(objects.begin(), objects.end());

	//ソート確認出力
	for (auto obj : objects) {
		printfDx("%s ", obj->toString().c_str());
	}
	printfDx("\n");
}

/***private***/
//力を加える
void World::applyForce() {
	//重力加速度を計算
	float acc = -gravity * TIME_STEP;
	for (Object* obj : objects) {
		obj->addV(Vec2(0, acc));
	}
}

void World::detectCollision() {
	//各オブジェクトの衝突を検知
	for (int i = 0; i < objects.size() - 1; i++) {
		for (int j = i + 1 ; j < objects.size(); j++) {
			//衝突した物体によって分類
			switch (objects[i]->getType() | objects[j]->getType()) {
			case Pair::CIRCLE_CIRCLE:
				break;
			case Pair::CIRCLE_LINE:
				break;
			}
		}
	}
}

void World::solveConstraints() {

}

void World::integrate() {
	auto itr = objects.begin();
	while (itr != objects.end())
	{
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