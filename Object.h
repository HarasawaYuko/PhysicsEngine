#pragma once
#include "Math.h"
#include "UIMaterial.h"

//ObjectNX@ZÎÛÌ}`ÍK¸p³·é
enum Type : uint16_t {
	CIRCLE = 0b0000'0000'0000'0001,
	LINE   = 0b0000'0000'0000'0010,
	BOX    = 0b0000'0000'0000'0100,
	CONVEX = 0b0000'0000'0000'1000
};

class Object {
protected:
	Vec2 center;//dSÀW
	Vec2 force;//Í
	Vec2 acceleration;//Á¬x
	Vec2 velocity;//¬x
	bool active = true;
	bool touch = false;
	float mass;
	const Type type;
	Color color;
	uint8_t id;
	int index;
	float friction;//CW
	float e;//½­W
	float angle_v;//p¬x@WA
	float angle;//ñ]p@WA
	float inertiaTensor;//µ«e\
	static const float MASS_RATE;
	Object(Vec2 v , Type ,float mass = 10 ,Color color = COLOR_BLACK ,bool act = true , float ang = 0.f , float ang_v = 0.f);
public:
	virtual void Draw()const = 0;
	float getM();
	Vec2 getC()const;
	Vec2 getV()const;
	void setAngle(const float);
	void setAngV(const float);
	void updateAngle(const float);
	float getAngle()const;
	float getAngV()const;
	bool isActive()const;
	uint8_t getId()const;
	void setMass(const float);
	void addV(const Vec2);
	void addVang(const float);
	void setTouch();
	void unTouch();
	int getIndex()const;
	void setIndex(const int);
	void setFri(const float);
	float getFri() const;
	void setE(const float);
	float getE()const;
	virtual void updatePos(const float);
	Type getType()const;
	virtual bool isValid()const = 0;
	virtual std::string toString()const = 0;
	virtual void setColor(Color color);
	unsigned int getColor() const;
	float getI()const;
	Vec2 getCirV(const Vec2&)const;
};