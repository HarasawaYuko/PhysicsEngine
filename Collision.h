#pragma once
#include "Object.h"

//�Փ˃N���X

class Collision {
private:
	std::pair<Object*, Object*> pair;
	uint16_t key;
	Collision() {};
	Collision(const Collision&) {}
	Collision& operator=(const Collision&) {}
public:
	Collision(Object* , Object*);
	uint16_t getKey()const;
};