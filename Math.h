#pragma once
#include "include.h"

//�񎟌��x�N�g��
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
	
	float dot(const Vec2)const;//����
	float cross(const Vec2)const;//�O��
	float norm()const;//�傫��
	float distance(const Vec2)const;//�Q�_�Ԃ̋���
};