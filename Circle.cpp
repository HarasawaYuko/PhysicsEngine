#include "Circle.h"

Circle::Circle(const float cen_x, const float cen_y, const float r, const float v_x, const float v_y , const bool act) 
	:r(r) , Object( Vec2(v_x , v_y), CIRCLE, (10 * r * r * 3.14) / 1600, COLOR_RED, act)
{
	center.set(cen_x, cen_y);
}

float Circle::getR() const{
	return r;
}

void Circle::Draw() const{
	DrawCircleP(center.x, center.y, r, color, true);
}

void Circle::DrawEdge()const {
	DrawCircleP(center.x, center.y, r, color, true ,3.f);
}

bool Circle::isValid()const {
	//完全に画面外に出たら
	if ((center.y  + r) < 0.f || (center.x + r) < 0.f || (center.x - r) > WIN_SIZE_X) {
		return false;
	}
	return true;
}

std::string Circle::toString()const {
	return "Circle";
}

void Circle::setBbox() {
	bbox.point = center + r;
	bbox.height = 2 * r;
	bbox.width = 2 * r;
}

void Circle::updatePos(const float step) {
	center = center + (velocity * step);
	setBbox();
}