#pragma once
#include "include.h"
#include "Math.h"

//�S���v�Z�ɕK�v�ȏՓˏ��

struct Constraint {
	Vec2 axis;//�S����
	float denom;//����
	float f;//�����S����
	float lowerF;
	float upperF;
	float accumImpulse;//�~�ς��ꂽ�S����
};