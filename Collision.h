#pragma once
#include "Object.h"
#include "ContactPoint.h"

//�Փ˃N���X

class Collision {
private:
	std::pair<Object*, Object*> pair;
	uint16_t key;
	uint16_t type;
	int contactNum;
	float friction;//���C�W��
	float e = 0.8;
public:
	std::vector<ContactPoint> contactPoints;
	Collision(Object* , Object*);
	uint16_t getKey()const;
	uint16_t getType()const;
	Object* getObj1()const;
	Object* getObj2()const;
	float getE()const;
	int getContactNum()const;
	void addContactPoint(const ContactPoint);
	void addContactPoint(const float , const Vec2 ,const Vec2 , const Vec2);
	void Draw()const;
	void setFri(const float );
	float getFri()const;
	ContactPoint& getCp(const int);
};