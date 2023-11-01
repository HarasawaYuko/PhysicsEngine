#include "Math.h"

Vec2::Vec2()
	:x(0) , y(0)
{}

Vec2::Vec2(const float x , const float y) 
	:x(x) , y(y)
{}

float Vec2::getX() const{
	return x;
}

float Vec2::getY() const {
	return y;
}

void Vec2::setX(const float _x) {
	x = _x;
}

void Vec2::setY(const float _y) {
	y = _y;
}

Vec2 Vec2::operator+(const Vec2 vec) const {
	return Vec2(x + vec.x , y + vec.y);
}

Vec2 Vec2::operator-(const Vec2 vec) const {
	return Vec2(x - vec.x, y - vec.y);
}

//�񎟌��x�N�g���̓���
float Vec2::dot(const Vec2 vec) const{
	return x * vec.getX() + y * vec.getY();
}

//�񎟌��x�N�g���̊O��
float Vec2::cross(const Vec2 vec)const{
	return x * vec.getY() - y * vec.getX();
}

//�傫���̎擾
float Vec2::norm() const {
	return sqrt(x * x + y * y);
}

//�Q�_�Ԃ̋���
float Vec2::distance(const Vec2 vec) const{
	Vec2 sub = *this - vec;
	return sub.norm();
}