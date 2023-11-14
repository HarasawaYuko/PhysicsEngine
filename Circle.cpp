#include "Circle.h"

Circle::Circle(const float cen_x, const float cen_y, const float r, const float v_x, const float v_y) {
	center.setV(cen_x, cen_y);
	velocity.setV(v_x , v_y);
	this->r = r;
}

void Circle::Draw() const{
	DrawCircleP(center.x, center.y, r , COLOR_RED, true);
}

bool Circle::isValid()const {
	//Š®‘S‚É‰æ–ÊŠO‚Éo‚½‚ç
	if ((center.y  + r) < 0.f || (center.x + r) < 0.f || (center.x - r) > WIN_SIZE_X) {
		return false;
	}
	return true;
}