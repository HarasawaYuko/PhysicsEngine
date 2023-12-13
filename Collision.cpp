#include "Collision.h"

Collision::Collision(Object* obj1, Object* obj2 , const float d , const Vec2 n , const Vec2 c) 
	:pair(std::make_pair(obj1 , obj2)),depth(d), nVec(n) , coord(c),
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

Object* Collision::getObj1()const {
	return pair.first;
}

Object* Collision::getObj2()const {
	return pair.second;
}

float Collision::getD()const {
	return depth;
}

Vec2 Collision::getN()const {
	return nVec;
}

Vec2 Collision::getC()const {
	return coord;
}

float Collision::getE()const {
	return e;
}