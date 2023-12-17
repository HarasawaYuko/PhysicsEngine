#include "Collision.h"

Collision::Collision(Object* obj1, Object* obj2) 
	:pair(std::make_pair(obj1 , obj2))
	,type(obj1->getType() | obj2 -> getType())
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

float Collision::getE()const {
	return e;
}

int Collision::getContactNum()const {
	return contactNum;
}

void Collision::addContactPoint(const ContactPoint cp) {
	contactPoints.push_back(cp);
}

void Collision::addContactPoint(const float d, const Vec2 pA, const Vec2 pB, const Vec2 n) {
	contactPoints.emplace_back(d , pA , pB , n);
}