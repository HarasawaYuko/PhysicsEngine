#pragma once
#include "Math.h"

//Object�N���X�@���Z�Ώۂ̐}�`�͕K���p������
enum Type {
	CIRCLE
};

class Object {
protected:
	Vec2 center;//�d�S���W
	Vec2 force;//��
	Vec2 acceleration;//�����x
	Vec2 velocity;//���x
	Object(){}
public:
	virtual void Draw();
	Type type;
};