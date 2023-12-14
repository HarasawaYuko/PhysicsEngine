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

//二次元ベクトルの内積
float Vec2::dot(const Vec2 vec) const{
	return x * vec.x + y * vec.y;
}

//二次元ベクトルの外積
float Vec2::cross(const Vec2 vec)const{
	return x * vec.y - y * vec.x;
}

//大きさの取得
float Vec2::norm() const {
	return (float)sqrt(x * x + y * y);
}

//２点間の距離
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
