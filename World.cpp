#include "Pair.h"
#include "detect.h"
#include "World.h"
#include "Solver.h"

World::World(float timeStep)
{
	TIME_STEP = timeStep;
	objNum = 0;
}

void World::initialize() {
	//������
	objNum = 0;
	Solver::initialize(TIME_STEP);
	pairs.clear();
	objects.clear();
}

void World::physicsSimulate() {
	static int count = 0;
	count++;
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
	objNum++;
	//���j�[�N��id�̊��蓖��
	totalNum++;
	obj->setId(totalNum);
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
//�u���[�h�t�F�[�Y
	std::vector<Pair> nowPairs;//���o���ꂽ�y�A
	static int count = 0;
	count++;
	for (int i = 0; i < objNum; i++) {
		for (int j = i + 1; j < objNum; j++) {
			//�o�E���f�B���O�{�b�N�X�ɂ�锻��
			if (Detect::broard(objects[i], objects[j])) {
				//����������y�A���쐬
				nowPairs.emplace_back(objects[i] , objects[j]);
				nowPairs.back().setType(New);
			}
		}
	}
	//�O�̃��X�g�Ɣ�r����Type��ݒ�
	for (int i = 0; i < nowPairs.size(); i++) {
		for (int j = 0; j < pairs.size();j++) {
			//������ނ����o���ꂽ��
			if (nowPairs[i].getKey() == pairs[j].getKey()) {
				nowPairs[i] = pairs[j];
				nowPairs[i].setType(Keep);
			}
		}
	}
	//�y�A�̔z����X�V
	this->pairs = nowPairs;
	//�ȑO�̏Փ˓_�̏󋵂��m�F���A�X�V����
	for (int i = 0; i < pairs.size();i++) {
		pairs[i].refreshCp();
	}


//�i���[�t�F�[�Y
	std::vector<uint32_t> erase;
	for (int i = 0; i < pairs.size(); i++) {
		const Pair& pair = pairs[i];
		float depth;//�ђʐ[�x
		Vec2 n;//�Փ˖@���x�N�g��
		Vec2 coord[2];//�Փˍ��W
		Vec2 coord_[2];//�Փˍ��W�i�ӏ�j
		//�Փ˂�����ނŏꍇ����
		switch (pair.getKind()) {
		case CONVEX_CONVEX:
			if (Detect::convex_convex(pair.getObj0(), pair.getObj1(), &depth, &n, coord ,coord_)) {
				//�Փ˂��Ă�����Փˏ����L�^
				ContactPoint cp;
				cp.depth = depth;
				cp.normal = n;
				cp.pointA = coord[0];
				cp.pointB = coord[1];
				cp.pointA_ = coord_[0];
				cp.pointB_ = coord_[1];
				cp.constraint->accumImpulse = 0.f;
				pair.getCol()->addCp(cp);
			}
			else {
				//�Փ˂��Ă��Ȃ����
				erase.push_back(pair.getKey());//�L�[���L�^
			}
			break;
		case CIRCLE_CIRCLE:
			if (Detect::circle_circle(pair.getObj0(), pair.getObj1(), &depth, &n, coord, coord_)) {
				//�Փ˂��Ă�����Փˏ����L�^
				ContactPoint cp;
				cp.depth = depth;
				cp.normal = n;
				cp.pointA = coord[0];
				cp.pointB = coord[1];
				cp.pointA_ = coord_[0];
				cp.pointB_ = coord_[1];
				cp.constraint->accumImpulse = 0.f;
				pair.getCol()->addCp(cp);
			}
			else {
				//�Փ˂��Ă��Ȃ����
				erase.push_back(pair.getKey());//�L�[���L�^
			}
			break;
		case CIRCLE_CONVEX:
			if (Detect::circle_convex(pair.getObj0(), pair.getObj1(), &depth, &n, coord, coord_)) {
				//�Փ˂��Ă�����Փˏ����L�^
				ContactPoint cp;
				cp.depth = depth;
				cp.normal = n;
				cp.pointA = coord[0];
				cp.pointB = coord[1];
				cp.pointA_ = coord_[0];
				cp.pointB_ = coord_[1];
				cp.constraint->accumImpulse = 0.f;
				pair.getCol()->addCp(cp);
			}
			else {
				//�Փ˂��Ă��Ȃ����
				erase.push_back(pair.getKey());//�L�[���L�^
			}
			break;
		}
	}
	//�Փ˂��Ă��Ȃ������y�A���폜
	for (int i = 0; i < erase.size(); i++) {
		for (int j = 0; j < pairs.size(); j++) {
			if (pairs[j].getKey() == erase[i]) {
				pairs.erase(pairs.begin() + j);
			}
		}
	}
	//printfDx("world �y�A��%d\n", pairs.size());
}


//�S���̉���
void World::solveConstraints() {
	//�S�Ẵy�A�ɂ���
	Solver::solve(this);
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
			objNum--;
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