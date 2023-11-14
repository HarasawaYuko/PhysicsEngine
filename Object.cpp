#include "Object.h"

float Object::getMass() {
	return mass;
}

void Object::setMass(const float m) {
	mass = m;
}

Vec2 Object::getV()const{
	return velocity;
}

void Object::addV(const Vec2 acc) {
	if (!active) return;
	velocity = acc + velocity;
}

void Object::updatePos(const float step) {
	//動かない物体の場合何もしない
	if (!active) return;
	center = center + (velocity * step);
}

Type Object::getType()const{
	return type;
}