#pragma once
#include "Math.h"

//Object�N���X�@���Z�Ώۂ̐}�`�͕K���p������
enum Type {
	CIRCLE,
	LINE
};

class Object {
protected:
	Vec2 center;//�d�S���W
	Vec2 force;//��
	Vec2 acceleration;//�����x
	Vec2 velocity;//���x
	bool active = true;
	float mass = 10;
	Type type;
	Object(){}
public:
	virtual void Draw()const = 0;
	float getMass();
	Vec2 getV()const;
	void setMass(const float);
	void addV(const Vec2);
	void updatePos(const float);
	Type getType()const;
	virtual bool isValid()const = 0;
};