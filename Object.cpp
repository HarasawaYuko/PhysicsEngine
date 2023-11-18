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
	//�����Ȃ����̂̏ꍇ�������Ȃ�
	if (!active) return;
	center = center + (velocity * step);
}

Type Object::getType()const{
	return type;
}

Object::Object(Type type , bool act) {
	type = type;
	active = act;
}

bool Object::operator<(const Object& another) const
{
	return type > another.getType();
};