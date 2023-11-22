#pragma once
#include "Object.h"

//�Փ˃N���X

class Collision {
private:
	std::pair<Object*, Object*> pair;
	uint16_t key;
	uint16_t type;
	float depth;
	Vec2 nVec;
	Vec2 coord;
public:
	Collision(Object* , Object* ,const float ,const Vec2 ,const Vec2);
	uint16_t getKey()const;
	uint16_t getType()const;
};