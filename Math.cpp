#include "Math.h"

Vec2::Vec2()
	:x(0) , y(0)
{}

Vec2::Vec2(const float x , const float y) 
	:x(x) , y(y)
{}

void Vec2::set(const float x , const float y) {
	this->x = x;
	this->y = y;
}

Vec2 Vec2::operator+(const Vec2 vec) const {
	return Vec2(x + vec.x , y + vec.y);
}

Vec2 Vec2::operator-(const Vec2 vec) const {
	return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator*(const float k) const {
	return Vec2(x * k, y *k);
}

//�񎟌��x�N�g���̓���
float Vec2::dot(const Vec2 vec) const{
	return x * vec.x + y * vec.y;
}

//�񎟌��x�N�g���̊O��
float Vec2::cross(const Vec2 vec)const{
	return x * vec.y - y * vec.x;
}

//�傫���̎擾
float Vec2::norm() const {
	return (float)sqrt(x * x + y * y);
}

//�Q�_�Ԃ̋���
float Vec2::distance(const Vec2 vec) const{
	Vec2 sub = *this - vec;
	return sub.norm();
}

Vec2 Vec2::normalize()const {
	float length = norm();
	return Vec2(x / length, y / length);
}

Vec2 Vec2::rotation(const float & ang)const {
	float rad = getRad(ang);
	float x_ = x*cos(rad) - y*sin(rad);
	float y_ = x*sin(rad) + y*cos(rad);
	return Vec2(x_ , y_);
}

Vec2 Vec2::normal()const {
	return Vec2(-y ,x);
}

std::string Vec2::toString() const
{
	return std::to_string(x) + "," + std::to_string(y);
}

Segment::Segment(const Vec2 s , const Vec2 e) 
	:start(s) , end(e)
{}

float getRad(const float ang) {
	return (ang * Pi) / 180.f;
}

//�_�ƒ����̋���
float getDistance(const Vec2& point , const Segment& seg) {
	return abs((point - seg.start).cross(seg.end - seg.start)) / (seg.end - seg.start).norm();
}

/*
�_�Ɛ����̋���
pattern�ɐ����Ɠ_�̈ʒu�֌W���L�^
0...start���ŒZ 1...end���ŒZ�@2...������̓_���ŒZ
*/
float getDistance(const Vec2& point, const Segment &seg , int* pattern) {
	//�ʒu�֌W�ŏꍇ����
	Vec2 StoE = seg.end - seg.start;
	Vec2 StoP = point - seg.start;
	Vec2 EtoP = point - seg.end;
	if (StoE.dot(StoP) < 0) {
		*pattern = 0;
		return point.distance(seg.start);
	}
	if ((StoE * -1).dot(EtoP) ) {
		*pattern = 1;
		return point.distance(seg.end);
	}
	*pattern = 2;
	return getDistance(point , seg);
}

//���[�J�����W�����[���h���W�ɕϊ�
Vec2 LtoW(const Vec2& local, const Vec2& worldCen , float ang) {
	return local.rotation(ang) + worldCen;
}

//���[���h���W�����[�J�����W�ɕϊ�
Vec2 WtoL(const Vec2 &world , const Vec2& worldCen , float ang) {
	return (world - worldCen).rotation(-ang);
}