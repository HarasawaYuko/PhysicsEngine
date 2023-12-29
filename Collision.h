#pragma once
#include "Object.h"
#include "ContactPoint.h"

//�Փ˃N���X

class Collision {
private:
	int contactNum;
	float friction;//���C�W��
	float e = 0.8;


	std::pair<Object*, Object*> pair;//����Ȃ�
	uint16_t key;//����Ȃ�
	uint16_t type;//����Ȃ�
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
	void addContactPoint(const ContactPoint);//�폜�\��
	void addContactPoint(const float , const Vec2 ,const Vec2 , const Vec2);//�폜�\��
	void Draw()const;
	void setFri(const float );
	float getFri()const;
	ContactPoint& getCp(const int);
};