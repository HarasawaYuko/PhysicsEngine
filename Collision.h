#pragma once
#include "Object.h"

//Õ“ËƒNƒ‰ƒX

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