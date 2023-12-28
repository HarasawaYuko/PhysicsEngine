#include "World.h"

World::World(float timeStep)
{
	TIME_STEP = timeStep;
}

void World::initialize() {
	//������
	Solver::initialize(TIME_STEP);


	//Line�ݒu
	/*Line* line1 = new Line(Vec2(290, 200), Vec2(500, 500), false);
	add(line1);*/
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
	//���j�[�N��id�̊��蓖��
	num++;
	obj->setId(num);
	//�I�u�W�F�N�g��ނɂ���ă\�[�g
	std::sort(objects.begin(), objects.end() , [](const Object* a, const Object* b) {
		return (uint16_t)a->getType() < (uint16_t)b->getType();
		});
	//�C���f�b�N�X�̐U�蒼��
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->setIndex(i);
	}
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

//�Փˌ��m
void World::detectCollision() {
	//DEBUG
	for (auto obj : objects) {
		obj->unTouch();
	}
	//�u���[�h�t�F�[�Y
	
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
			//�Փˏ��
			float depth;//�ђʐ[�x
			Vec2 nVec;//�@���x�N�g��
			Vec2 coord[2];//�Փˍ��W

			//�Փ˂������̂ɂ���ĕ���
			switch (objects[i]->getType() | objects[j]->getType()) {
			case Kind::CIRCLE_CIRCLE:
				//i:circle  j:circle
				if (Detect::circle_circle(objects[i], objects[j] ,&depth , &nVec , coord)) {
					objects[i]->setTouch();
					objects[j]->setTouch();
					contact = true;
				}
				break;
			case Kind::CIRCLE_LINE:
				//i:circle  j:line
				if (Detect::circle_line(objects[i], objects[j], &depth, &nVec, coord)) {
					objects[i]->setTouch();
					contact = true;
				}
				break;
			case Kind::BOX_BOX:
				//i:box j:box
				
				if (Detect::box_box(objects[i], objects[j], &depth, &nVec, coord)) {
					//printfDx("return true\n");
					objects[i]->setTouch();
					objects[j]->setTouch();
					contact = true;
				}
				break;
			}
			//�Փ˂��Ă����
			if (contact) {
				newColls.emplace_back(objects[i], objects[j]);
				newColls.back().addContactPoint(depth , coord[0] , coord[1] , nVec);
			}
		}
	}

	//�Փ˃��X�g���X�V
	collisions.clear();
	//printfDx("newColls %d\n", newColls.size());
	collisions = newColls;
	//printfDx("collision %d\n", collisions.size());
}


//�S���̉���
void World::solveConstraints() {
	//�e�Փ˂̍S�����v�Z
	for (auto col : collisions) {
		switch (col.getType()) {
		case CIRCLE_LINE:
			Solver::circle_line(col);
			break;
		case CIRCLE_CIRCLE:
			Solver::circle_circle(col);
			break;
		}
	}
}

//�ʒu�̍X�V
void World::integrate() {
	auto itr = objects.begin();
	bool isErase = false;//�I�u�W�F�N�g���폜���ꂽ��
	while (itr != objects.end())
	{
		(*itr)->updatePos(TIME_STEP);
		if (!(*itr)->isValid())
		{
			itr = objects.erase(itr);
			isErase = true;
		}
		else
		{
			itr++;
		}
	}
	//�폜����������
	if (isErase) {
		//�C���f�b�N�X�̐U�蒼��
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->setIndex(i);
		}
	}
}