#pragma once
#include "include.h"

const float Pi = 3.141592;
const float INF = 10000000000.0f;

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
	Vec2 normalize()const;//���K��
	Vec2 rotation(const float &)const;//��]
	std::string toString()const;
};

//����
struct Segment {
public:
	Segment(){}
	Segment(const Vec2 , const Vec2);
	Vec2 start;
	Vec2 end;
};

//���W�A���ɕϊ�����
float getRad(const float);
//�_�ƒ����̋��������߂�
float getDistance(const Vec2& , const Segment &);
float getDistance(const Vec2&, const Segment & , int*);

Vec2 LtoW(const Vec2& ,const Vec2& ,const float);
Vec2 WtoL(const Vec2&, const Vec2& ,const float);