#include "Collision.h"

Collision::Collision(Object* obj1, Object* obj2) 
	:pair(std::make_pair(obj1 , obj2)),
	type(obj1->getType() | obj2 -> getType())
{
	uint16_t id1 = (uint16_t)obj1->getId();
	uint16_t id2 = (uint16_t)obj2->getId();
	key = (id1 << 8) | id2;
}

uint16_t Collision::getKey() const{
	return key;
}

uint16_t Collision::getType() const {
	return type;
}