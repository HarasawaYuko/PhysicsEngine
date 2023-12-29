#include "Collision.h"

Collision::Collision(Object* obj1, Object* obj2) 
	:pair(std::make_pair(obj1 , obj2))
	,type(obj1->getType() | obj2 -> getType())
	,contactNum(0)
{
	uint16_t id1 = (uint16_t)obj1->getId();
	uint16_t id2 = (uint16_t)obj2->getId();
	key = (id1 << 8) | id2;
}

Collision::Collision() 
	:contactNum(0)
{
}

void Collision::addCp(ContactPoint cp) {
	if (contactNum == 2) {
		//衝突点の数が2の場合は増やさない
		
		//衝突点が複数ある場合は距離が最も遠いものを選択
		float dis = contactPoints[0].pointA.distance(contactPoints[1].pointA);
		float dis0 = contactPoints[0].pointA.distance(cp.pointA);
		float dis1 = contactPoints[1].pointA.distance(cp.pointA);
		int index;
		float disNew;
		if (dis0 < dis1) {
			index = 1;
			disNew = dis1;
		}
		else {
			index = 0;
			disNew = dis0;
		}
		if (dis < disNew) {
			contactPoints[index] = cp;
		}
	}
	else if (contactNum == 1) {
		contactPoints[1] = cp;
		contactNum++;
	}
	contactPoints[0] = cp;
	contactNum++;
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

void Collision::setFri(const float fri) {
	friction = fri;
}

float Collision::getFri()const {
	return friction;
}

ContactPoint& Collision::getCp(const int i){
	assert(0 <= i && i < contactNum);
	return contactPoints[i];
}

//削除予定
void Collision::addContactPoint(const ContactPoint cp) {
	contactPoints[0] = cp;
}