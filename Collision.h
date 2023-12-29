#pragma once
#include "Object.h"
#include "ContactPoint.h"

//衝突クラス

class Collision {
private:
	int contactNum;
	float friction;//摩擦係数
	float e = 0.8;


	std::pair<Object*, Object*> pair;//いらない
	uint16_t key;//いらない
	uint16_t type;//いらない
public:
	ContactPoint contactPoints[2];
	void addCp(ContactPoint);

	Collision(Object* , Object*);
	Collision();
	uint16_t getKey()const;
	uint16_t getType()const;
	Object* getObj1()const;
	Object* getObj2()const;
	float getE()const;
	int getContactNum()const;
	void addContactPoint(const ContactPoint);//削除予定
	void addContactPoint(const float , const Vec2 ,const Vec2 , const Vec2);//削除予定
	void Draw()const;
	void setFri(const float );
	float getFri()const;
	ContactPoint& getCp(const int);
};