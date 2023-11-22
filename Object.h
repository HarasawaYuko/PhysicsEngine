#pragma once
#include "Math.h"
#include "UIMaterial.h"

//Object�N���X�@���Z�Ώۂ̐}�`�͕K���p������
enum Type : uint16_t {
	CIRCLE = 0b0000'0000'0000'0001,
	LINE   = 0b0000'0000'0000'0010,
	BOX    = 0b0000'0000'0000'0100,
};


class Object {
protected:
	Vec2 center;//�d�S���W
	Vec2 force;//��
	Vec2 acceleration;//�����x
	Vec2 velocity;//���x
	bool active = true;
	bool touch = false;
	float mass = 10;
	const Type type;
	Color color;
	uint8_t id;
	Object(Type , Color color = COLOR_BLACK ,bool act = true);
public:
	virtual void Draw()const = 0;
	float getM();
	Vec2 getC()const;
	Vec2 getV()const;
	bool isActive()const;
	uint8_t getId()const;
	void setMass(const float);
	void addV(const Vec2);
	void setTouch();
	void unTouch();
	virtual void updatePos(const float);
	Type getType()const;
	virtual bool isValid()const = 0;
	virtual std::string toString()const = 0;
	virtual void setColor(Color color);
};