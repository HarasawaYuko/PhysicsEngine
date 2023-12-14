#include "Constraints.h"

static const float e_CC = 0.8f; //�~�Ɖ~�̔����W��
static float k_CC;//�o�l�W��

void Constraint::initialize(const float timeStep) {
	k_CC = (float)(1 / (timeStep));
}

bool Constraint::circle_line(Collision &col) {
	Circle* cir = static_cast<Circle*>(col.getObj1());
	Line* line = static_cast<Line*>(col.getObj2());
	//���Α��x���擾
	Vec2 V12 = Vec2(line->getV().x - cir->getV().x, line->getV().y - cir->getV().y);
	/*printfDx("cir:%s \n", cir->getV().toString().c_str());
	printfDx("line:%s \n", line->getV().toString().c_str());
	printfDx("���Α��x:%s \n" , V12.toString().c_str());*/
	//���Α��x�̖@������
	float V12_n = V12.dot(col.getN());
	//printfDx("dot:%f\n",V12_n );
	//���͂̌W�������߂�
	//float c = ((cir->getM() * line->getM()) / (cir->getM() + line->getM())) * ((1 + col.getE()) * V12_n - k_CC * col.getD());
	//float c = -(1 + col.getE()) * cir->getM() * (cir->getV().dot(col.getN()));
	float c;
	if (V12.dot(col.getN()) > 0) {
		c = -cir->getM()/2 * ((col.getE() + 1) * (k_CC * col.getD()));
	}
	else {
		c = cir->getM()/2 * ((col.getE() + 1) * (V12.dot(col.getN()) - k_CC * col.getD()));
	}
	//���x�̕ύX
	cir->addV(col.getN() * (c / cir->getM()));
	line->addV(col.getN() * (-c / line->getM()));
	return true;
}

bool Constraint::circle_circle(Collision &col ) {
	Circle* cir1 = static_cast<Circle*>(col.getObj1());
	Circle* cir2 = static_cast<Circle*>(col.getObj2());
	//���Α��x���擾
	Vec2 V12 = Vec2(cir2->getV().x - cir1->getV().x , cir2->getV().y - cir1->getV().y);
	//���Α��x�̖@������
	float V12_n = V12.dot(col.getN());
	//���͂̌W�������߂�
	//float c = ((cir1->getM() * cir2->getM()) / (cir1->getM() + cir2->getM()))*((1+col.getE())*V12_n + k_CC * col.getD());
	float c;
	if (V12.dot(col.getN()) > 0) {
		c = ((cir1->getM() * cir2->getM()) / (cir1->getM() + cir2->getM()))*(-k_CC * col.getD());
	}
	else {
		c = ((cir1->getM() * cir2->getM()) / (cir1->getM() + cir2->getM()))*((1+col.getE())*V12_n - k_CC * col.getD());
	}
	//���x�̕ύX
	cir1->addV(col.getN()*(c/cir1->getM()));
	cir2->addV(col.getN() * (-c / cir2->getM()));
	return true;
}