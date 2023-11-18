#include "Line.h"

Line::Line (const Vec2 s ,const Vec2 e ,const bool active , const float v_x ,const float v_y) 
	:Object(LINE , false) , start(s) , end(e)
{
	velocity.set(v_x , v_y);
}

Vec2 Line::getS()const {
	return start;
}

Vec2 Line::getE()const {
	return end;
}

void Line::Draw() const{
	DrawLineAA(start.x ,WIN_SIZE_Y - start.y , end.x, WIN_SIZE_Y - end.y , COLOR_BLACK , 5.0f);
}

bool Line::isValid() const {
	if (max(start.y, end.y) < 0.f || max(start.x, end.x) <0.f || min(start.x, end.x)>WIN_SIZE_X) {
		return false;
	}
	return true;
}

std::string Line::toString()const {
	return "Line";
}