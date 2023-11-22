#include "Constraints.h"

static const float e_CC = 0.8f; //‰~‚Æ‰~‚Ì”½”­ŒW”
static float k_CC;//ƒoƒlŒW”

void Constraint::initialize(const float timeStep) {
	k_CC = 1 / (timeStep * 2);
}

bool Constraint::circle_line(Object* c, Object* l) {
	Circle* cir = static_cast<Circle*>(c);
	Line* line = static_cast<Line*>(l);

	return true;
}

bool Constraint::circle_circle(Collision &col ) {
	Circle* cir1 = static_cast<Circle*>(col.getObj1());
	Circle* cir2 = static_cast<Circle*>(col.getObj2());
	//‘Š‘Î‘¬“x‚ğæ“¾
	Vec2 V12 = Vec2(cir2->getV().x - cir1->getV().x , cir2->getV().y - cir1->getV().y);
	//Œ‚—Í‚ÌŒW”‚ğ‹‚ß‚é
	float c = ((cir1->getM() + cir2->getM()) / (cir1->getM() * cir2->getM()));
	return true;
}