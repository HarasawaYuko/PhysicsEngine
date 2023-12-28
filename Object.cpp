#include "Object.h"

static std::vector<uint8_t> usedId;
static const int ObjMax = 100;

const float Object::MASS_RATE = 1600.f;

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

void Object::setAngle(const float ang) {
	angle = ang;
}

void Object::setAngV(const float ang_v) {
	angle_v = ang_v;
}

void Object::updateAngle(const float step) {
	angle += (angle_v * step);
}

float Object::getAngle()const {
	return angle;
}

float Object::getAngV()const {
	return angle_v;
}

bool Object::isActive()const {
	return active;
}

void Object::addV(const Vec2 acc) {
	if (!active) {
		return;
	}
	velocity = acc + velocity;
}

void Object::addVang(const float acc) {
	if (!active)
	{
		return;
	}
	angle_v += acc;
}

void Object::setTouch() {
	this->touch = true;
}

void Object::unTouch() {
	this->touch = false;
}

void Object::setId(const uint16_t i) {
	if (i < 0 || UINT16_MAX < i) {
		//�ǉ��I�u�W�F�N�g��������Ȃ��O
		assert(false);
	}
	this->id = i;
}

uint16_t Object::getId() const{
	return id;
}

int Object::getIndex()const {
	return index;
}

void Object::setIndex(const int i) {
	index = i;
}

void Object::setFri(const float fri) {
	friction = fri;
}

float Object::getFri()const {
	return friction;
}

void Object::setE(const float e_) {
	e = e_;
}

float Object::getE()const {
	return e;
}

void Object::updatePos(const float step) {
	//�����Ȃ����̂̏ꍇ�������Ȃ�
	if (!active) return;
	center = center + (velocity * step);
}

Type Object::getType()const{
	return type;
}

BBox& Object::getBbox() const{
	return bbox;
}

//�R���X�g���N�^
Object::Object(Vec2 v ,Type type ,float mass, Color color , bool act , float ang , float ang_v ) 
	:velocity(v) ,  type(type),color(color) ,mass(mass),active(act) , angle(ang), angle_v(ang_v)
{
	//id�̐ݒ�
	for (int id = 0; id < ObjMax; id++) {
		//�g���Ă��Ȃ�id������
		if (std::find(usedId.begin(), usedId.end(), id) != usedId.end()) {
			this->id = id;
		}
	}
}

void Object::setColor(Color c) {
	this->color = c;
}

unsigned int Object::getColor() const{
	return color;
}

//�����e���\���̎擾
float Object::getI()const {
	return inertiaTensor;
}

//�~�^���̑��x���擾�@point ���[�J�����W
//return ���[���h���W�ł̑��x
Vec2 Object::getCirV(const Vec2& point)const {
	//�傫�����擾 v = r��
	float length = point.norm() * angle_v;
	Vec2 result = point.normal().normalize() * length;
	return result.rotation(angle);
}