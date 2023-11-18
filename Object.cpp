#include "Object.h"

float Object::getMass() {
	return mass;
}

void Object::setMass(const float m) {
	mass = m;
}

Vec2 Object::getC()const {
	return center;
}

Vec2 Object::getV()const{
	return velocity;
}

void Object::addV(const Vec2 acc) {
	if (!active) return;
	velocity = acc + velocity;
}

void Object::setTouch() {
	this->touch = true;
}

void Object::unTouch() {
	this->touch = false;
}

void Object::updatePos(const float step) {
	//“®‚©‚È‚¢•¨‘Ì‚Ìê‡‰½‚à‚µ‚È‚¢
	if (!active) return;
	center = center + (velocity * step);
}

Type Object::getType()const{
	return type;
}

Object::Object(Type type , Color color , bool act) 
	:type(type),color(color)
{
	active = act;
}

void Object::setColor(Color c) {
	this->color = c;
}

