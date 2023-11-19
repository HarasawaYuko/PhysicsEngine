#pragma once
#include "Object.h"

//Õ“ËƒNƒ‰ƒX

class Collision {
private:
	std::pair<Object*, Object*> pair;
	uint16_t key;
	uint16_t type;
public:
	Collision(Object* , Object*);
	uint16_t getKey()const;
	uint16_t getType()const;
};