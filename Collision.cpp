#include "Collision.h"

Collision::Collision(Object* obj1, Object* obj2) 
	:pair(std::make_pair(obj1 , obj2))
	,type(obj1->getType() | obj2 -> getType())
{
	uint16_t id1 = (uint16_t)obj1->getId();
	uint16_t id2 = (uint16_t)obj2->getId();
	key = (id1 << 8) | id2;
}

uint16_t Collision::getKey() const{
	return key;
}

uint16_t Collision::getType() const {
	return type;
}

Object* Collision::getObj1()const {
	return pair.first;
}

Object* Collision::getObj2()const {
	return pair.second;
}

float Collision::getE()const {
	return e;
}

int Collision::getContactNum()const {
	return contactNum;
}

void Collision::addContactPoint(const ContactPoint cp) {
	contactPoints.push_back(cp);
}

void Collision::addContactPoint(const float d, const Vec2 pA, const Vec2 pB, const Vec2 n) {
	contactPoints.emplace_back(d , pA , pB , n);
}

void Collision::Draw() const{
	for (auto cp : contactPoints) {
		//ローカル座標→ワールド座標に戻す
		Vec2 pA = LtoW(cp.pointA , pair.first->getC() ,pair.first->getAngle() );
		Vec2 pB = LtoW(cp.pointB, pair.second->getC(), pair.second->getAngle());
		//Vec2 pB = LtoW();
		//衝突点の描画
		DrawCircle((int)pA.x , (int)(WIN_SIZE_Y - pA.y), 3 , COLOR_RED);
		DrawCircle(pB.x, WIN_SIZE_Y - pB.y,3, COLOR_RED);
		//法線ベクトルの描画
		Vec2 nVec = pA + (cp.normal * 100);
		DrawLine(pA.x, WIN_SIZE_Y - pA.y,nVec.x , WIN_SIZE_Y - nVec.y  , COLOR_RED , 3.f);
	}
}

ContactPoint Collision::getCp(const int i)const {
	assert(i < 0 || contactNum <= i);
	return contactPoints[i];
}