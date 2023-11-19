#include "World.h"

World::World(float timeStep)
{
	TIME_STEP = timeStep;
}

void World::initialize() {
	//���̍쐬
	Line* wall_under = new Line(Vec2(30 ,300), Vec2(770 , 300), false);
	add(wall_under);
	//�~�̔z�u
	Circle* cir1 = new Circle(300, 500, 50);
	add(cir1);
	//�����`�̔z�u
	Box* box1 = new Box(400 , 500 , 60 , 70 );
	add(box1);

	//Line�ݒu
	/*Line* line1 = new Line(Vec2(290, 200), Vec2(500, 500), false);
	add(line1);*/
}

void World::physicsSimulate() {
	//printfDx("size: %d \n" , objects.size());
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
	std::sort(objects.begin(), objects.end() , [](const Object* a, const Object* b) {
		return (uint16_t)a->getType() < (uint16_t)b->getType();
		});
}

/***private***/
//�͂�������
void World::applyForce() {
	//�d�͉����x���v�Z
	float acc = -gravity * TIME_STEP;
	for (Object* obj : objects) {
		obj->addV(Vec2(0, acc));
	}
}

void World::detectCollision() {
	//DEBUG
	for (auto obj : objects) {
		obj->unTouch();
	}
	//�e�I�u�W�F�N�g�̏Փ˂����m
	bool contact;
	std::vector<Collision> newColls;
	for (int i = 0; i < objects.size() - 1; i++) {
		for (int j = i + 1 ; j < objects.size(); j++) {
			//�����Ȃ����̓��m�Ȃ�X�L�b�v
			if (!objects[i]->isActive() && !objects[j]->isActive()) {
				continue;
			}
			contact = false;
			//�Փ˂������̂ɂ���ĕ���
			switch (objects[i]->getType() | objects[j]->getType()) {
			case Pair::CIRCLE_CIRCLE:
				//i:circle  j:circle
				if (Detect::circle_circle(objects[i], objects[j])) {
					objects[i]->setTouch();
					objects[j]->setTouch();
					contact = true;
				}
				break;
			case Pair::CIRCLE_LINE:
				//i:circle  j:line
				if (Detect::circle_line(objects[i], objects[j])) {
					objects[i]->setTouch();
					contact = true;
				}
				break;
			}
			//�Փ˂��Ă����
			if (contact) {
				newColls.emplace_back(objects[i], objects[j]);
			}
			printfDx("newColls %d\n" , newColls.size());
		}
	}

	//�Փ˃��X�g���X�V
	collisions.clear();
	collisions = newColls;
	printfDx("collision %d\n", collisions.size());
}

void World::solveConstraints() {
	//�e�Փ˂̍S�����v�Z
	for (auto col : collisions) {
		switch (col.getType()) {
		case CIRCLE_LINE:

			break;
		}
	}
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