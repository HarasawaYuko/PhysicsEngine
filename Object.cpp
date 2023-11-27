#include "Object.h"

static std::vector<uint8_t> usedId;
static const int ObjMax = 100;

float Object::getM() {
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

bool Object::isActive()const {
	return active;
}

uint8_t Object::getId()const {
	return id;
}

void Object::addV(const Vec2 acc) {
	if (!active) {
		return;
	}
	velocity = acc + velocity;
}

void Object::setTouch() {
	this->touch = true;
}

void Object::unTouch() {
	this->touch = false;
}

void Object::updatePos(const float step) {
	//動かない物体の場合何もしない
	if (!active) return;
	center = center + (velocity * step);
}

Type Object::getType()const{
	return type;
}

//コンストラクタ
Object::Object(Type type ,float mass, Color color , bool act) 
	:type(type),color(color) ,mass(mass)
{
	active = act;
	//idの設定
	for (int id = 0; id < ObjMax; id++) {
		//使われていないidを検索
		if (std::find(usedId.begin(), usedId.end(), id) != usedId.end()) {
			this->id = id;
		}
	}
}

void Object::setColor(Color c) {
	this->color = c;
}

