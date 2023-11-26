#pragma once
#include "Object.h"

//Õ“ËƒNƒ‰ƒX

class Collision {
private:
	std::pair<Object*, Object*> pair;
	uint16_t key;
	uint16_t type;
	float depth;
	Vec2 nVec;
	Vec2 coord;
	float e = 0.9;
public:
	Collision(Object* , Object* ,const float ,const Vec2 ,const Vec2);
	uint16_t getKey()const;
	uint16_t getType()const;
	Object* getObj1()const;
	Object* getObj2()const;
	float getD()const;
	Vec2 getN()const;
	Vec2 getC()const;
	float getE()const;
};