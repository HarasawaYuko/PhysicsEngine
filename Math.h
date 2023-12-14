#pragma once
#include "include.h"

const float Pi = 3.141592;

//二次元ベクトル
struct Vec2 {
private:
public:
	float x = 0;
	float y = 0;
	Vec2();
	Vec2(const float x,const float y);

	void set(const float, const float);

	Vec2 operator+(const Vec2) const;
	Vec2 operator-(const Vec2) const;
	Vec2 operator*(const float) const;
	
	float dot(const Vec2)const;//内積
	float cross(const Vec2)const;//外積
	float norm()const;//大きさ
	float distance(const Vec2)const;//２点間の距離
	Vec2 normalize()const;//正規化
	std::string toString()const;
};

//ラジアンに変換する
float getRad(const float);