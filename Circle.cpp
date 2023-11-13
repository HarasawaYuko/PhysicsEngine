#include "Circle.h"

Circle::Circle(const float cen_x, const float cen_y, const float r, const float v_x, const float v_y) {
	center.set(cen_x, cen_y);
	velocity.set(v_x , v_y);
	this->r = r;
}

void Circle::Draw() {
	DrawCircleP(center.getX(), center.getY(), r, 20, COLOR_RED, true);
}

