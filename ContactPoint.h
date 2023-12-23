#pragma once
#include "Math.h"
#include "Constraint.h"

//�Փ˓_�̏���ێ�����\����
struct ContactPoint {
	ContactPoint(const float , const Vec2 , const Vec2, const Vec2 );
	float depth;
	Vec2 pointA;//A�̏Փ˓_���[�J�����W
	Vec2 pointB;//B�̏Փ˓_���[�J�����W
	Vec2 normal;//�Փ˖@���x�N�g��
	Constraint constraint[2];//�S�� ��������0 ���C����1
};