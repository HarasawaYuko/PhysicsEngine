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

std::string Vec2::toString() const
{
	return std::to_string(x) + "," + std::to_string(y);
}

float getRad(const float ang) {
	return (ang * Pi) / 180;
}
