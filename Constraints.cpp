#include "Constraints.h"

static const float e_CC = 0.8f; //円と円の反発係数
static float k_CC;//バネ係数

void Constraint::initialize(const float timeStep) {
	k_CC = (float)(1 / (timeStep));
}

bool Constraint::circle_line(Collision &col) {
	Circle* cir = static_cast<Circle*>(col.getObj1());
	Line* line = static_cast<Line*>(col.getObj2());
	//相対速度を取得
	Vec2 V12 = Vec2(line->getV().x - cir->getV().x, line->getV().y - cir->getV().y);
	/*printfDx("cir:%s \n", cir->getV().toString().c_str());
	printfDx("line:%s \n", line->getV().toString().c_str());
	printfDx("相対速度:%s \n" , V12.toString().c_str());*/
	//相対速度の法線成分
	float V12_n = V12.dot(col.getN());
	//printfDx("dot:%f\n",V12_n );
	//撃力の係数を求める
	//float c = ((cir->getM() * line->getM()) / (cir->getM() + line->getM())) * ((1 + col.getE()) * V12_n - k_CC * col.getD());
	//float c = -(1 + col.getE()) * cir->getM() * (cir->getV().dot(col.getN()));
	float c;
	if (V12.dot(col.getN()) > 0) {
		c = -cir->getM()/2 * ((col.getE() + 1) * (k_CC * col.getD()));
	}
	else {
		c = cir->getM()/2 * ((col.getE() + 1) * (V12.dot(col.getN()) - k_CC * col.getD()));
	}
	//速度の変更
	cir->addV(col.getN() * (c / cir->getM()));
	line->addV(col.getN() * (-c / line->getM()));
	return true;
}

bool Constraint::circle_circle(Collision &col ) {
	Circle* cir1 = static_cast<Circle*>(col.getObj1());
	Circle* cir2 = static_cast<Circle*>(col.getObj2());
	//相対速度を取得
	Vec2 V12 = Vec2(cir2->getV().x - cir1->getV().x , cir2->getV().y - cir1->getV().y);
	//相対速度の法線成分
	float V12_n = V12.dot(col.getN());
	//撃力の係数を求める
	//float c = ((cir1->getM() * cir2->getM()) / (cir1->getM() + cir2->getM()))*((1+col.getE())*V12_n + k_CC * col.getD());
	float c;
	if (V12.dot(col.getN()) > 0) {
		c = ((cir1->getM() * cir2->getM()) / (cir1->getM() + cir2->getM()))*(-k_CC * col.getD());
	}
	else {
		c = ((cir1->getM() * cir2->getM()) / (cir1->getM() + cir2->getM()))*((1+col.getE())*V12_n - k_CC * col.getD());
	}
	//速度の変更
	cir1->addV(col.getN()*(c/cir1->getM()));
	cir2->addV(col.getN() * (-c / cir2->getM()));
	return true;
}