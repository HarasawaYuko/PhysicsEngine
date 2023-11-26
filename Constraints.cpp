#include "Constraints.h"

static const float e_CC = 0.8f; //�~�Ɖ~�̔����W��
static float k_CC;//�o�l�W��

void Constraint::initialize(const float timeStep) {
	k_CC = 1 / (timeStep);
}

bool Constraint::circle_line(Object* c, Object* l) {
	Circle* cir = static_cast<Circle*>(c);
	Line* line = static_cast<Line*>(l);

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
	float c = ((cir1->getM() + cir2->getM()) / (cir1->getM() * cir2->getM()))*((1+col.getE())*V12_n - k_CC * col.getD());
	
	//���x�̕ύX
	cir1->addV(col.getN()*(c/cir1->getM()));
	cir2->addV(col.getN() * (-c / cir2->getM()));
	return true;
}