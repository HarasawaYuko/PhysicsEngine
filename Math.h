#pragma once
#include "include.h"

const float Pi = 3.141592;
const float INF = 10000000000.0f;

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
	Vec2 rotation(const float &)const;//回転
	std::string toString()const;
};

//線分
struct Segment {
public:
	Segment(){}
	Segment(const Vec2 , const Vec2);
	Vec2 start;
	Vec2 end;
};

//ラジアンに変換する
float getRad(const float);
//点と直線の距離を求める
float getDistance(const Vec2& , const Segment &);
float getDistance(const Vec2&, const Segment & , int*);

Vec2 LtoW(const Vec2& ,const Vec2& ,const float);
Vec2 WtoL(const Vec2&, const Vec2& ,const float);