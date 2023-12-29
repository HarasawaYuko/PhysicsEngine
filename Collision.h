#pragma once
#include "Object.h"
#include "ContactPoint.h"

//Õ“ËƒNƒ‰ƒX

class Collision {
private:
	int contactNum;
	float friction;//–€CŒW”
	float e = 0.8;


	std::pair<Object*, Object*> pair;//‚¢‚ç‚È‚¢
	uint16_t key;//‚¢‚ç‚È‚¢
	uint16_t type;//‚¢‚ç‚È‚¢
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
	void addContactPoint(const ContactPoint);//íœ—\’è
	void addContactPoint(const float , const Vec2 ,const Vec2 , const Vec2);//íœ—\’è
	void Draw()const;
	void setFri(const float );
	float getFri()const;
	ContactPoint& getCp(const int);
};