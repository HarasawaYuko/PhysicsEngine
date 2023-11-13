#pragma once
#include "include.h"

//二次元ベクトル
struct Vec2 {
private:
	float x = 0;
	float y = 0;
public:
	Vec2();
	Vec2(const float x,const float y);

	float getX()const;
	float getY()const;
	void setX(const float);
	void setY(const float);
	void set(const float, const float);

	Vec2 operator+(const Vec2) const;
	Vec2 operator-(const Vec2) const;
	
	float dot(const Vec2)const;//内積
	float cross(const Vec2)const;//外積
	float norm()const;//大きさ
	float distance(const Vec2)const;//２点間の距離
};