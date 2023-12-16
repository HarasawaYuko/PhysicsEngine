#include "World.h"

World::World(float timeStep)
{
	TIME_STEP = timeStep;
}

void World::initialize() {
	//初期化
	Constraint::initialize(TIME_STEP);


	//Line設置
	/*Line* line1 = new Line(Vec2(290, 200), Vec2(500, 500), false);
	add(line1);*/
}

void World::physicsSimulate() {
	printfDx("size: %d \n" , objects.size());
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
	std::sort(objects.begin(), objects.end() , [](const Object* a, const Object* b) {
		return (uint16_t)a->getType() < (uint16_t)b->getType();
		});
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

//衝突検知
void World::detectCollision() {
	//DEBUG
	for (auto obj : objects) {
		obj->unTouch();
	}
	//各オブジェクトの衝突を検知
	bool contact;
	std::vector<Collision> newColls;
	for (int i = 0; i < objects.size() - 1; i++) {
		for (int j = i + 1 ; j < objects.size(); j++) {
			//動かない物体同士ならスキップ
			if (!objects[i]->isActive() && !objects[j]->isActive()) {
				continue;
			}
			contact = false;
			//衝突情報
			float depth;//貫通深度
			Vec2 nVec;//法線ベクトル
			Vec2 coord[2];//衝突座標

			//衝突した物体によって分類
			switch (objects[i]->getType() | objects[j]->getType()) {
			case Pair::CIRCLE_CIRCLE:
				//i:circle  j:circle
				if (Detect::circle_circle(objects[i], objects[j] ,&depth , &nVec , coord)) {
					objects[i]->setTouch();
					objects[j]->setTouch();
					contact = true;
				}
				break;
			case Pair::CIRCLE_LINE:
				//i:circle  j:line
				if (Detect::circle_line(objects[i], objects[j], &depth, &nVec, coord)) {
					objects[i]->setTouch();
					contact = true;
				}
				break;
			case Pair::BOX_BOX:
				//i:box j:box
				
				if (Detect::box_box(objects[i], objects[j], &depth, &nVec, coord)) {
					//printfDx("return true\n");
					objects[i]->setTouch();
					objects[j]->setTouch();
				}
				break;
			}
			//衝突していれば
			if (contact) {
				newColls.emplace_back(objects[i], objects[j] , depth , nVec , coord);
			}
			//printfDx("newColls %d\n" , newColls.size());
		}
	}

	//衝突リストを更新
	collisions.clear();
	collisions = newColls;
	//printfDx("collision %d\n", collisions.size());
}


//拘束の解消
void World::solveConstraints() {
	//各衝突の拘束を計算
	for (auto col : collisions) {
		switch (col.getType()) {
		case CIRCLE_LINE:
			Constraint::circle_line(col);
			break;
		case CIRCLE_CIRCLE:
			Constraint::circle_circle(col);
			break;
		}
	}
}

//位置の更新
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