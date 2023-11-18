#include "Circle.h"

Circle::Circle(const float cen_x, const float cen_y, const float r, const float v_x, const float v_y) 
	:r(r) , Object(CIRCLE)
{
	center.set(cen_x, cen_y);
	velocity.set(v_x , v_y);
}

void Circle::Draw() const{
	DrawCircleP(center.x, center.y, r , COLOR_RED, true);
}

bool Circle::isValid()const {
	//äÆëSÇ…âÊñ äOÇ…èoÇΩÇÁ
	if ((center.y  + r) < 0.f || (center.x + r) < 0.f || (center.x - r) > WIN_SIZE_X) {
		return false;
	}
	return true;
}

std::string Circle::toString()const {
	return "Circle";
}