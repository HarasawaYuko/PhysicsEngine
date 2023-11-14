#include "Line.h"

Line::Line (const Vec2 s ,const Vec2 e ,const bool active , const float v_x ,const float v_y) {
	start = s;
	end = e;
	this->active = active;
	velocity.setV(v_x , v_y);
}

void Line::Draw() const{
	DrawLineAA(start.x ,WIN_SIZE_Y - start.y , end.x, WIN_SIZE_Y - end.y , COLOR_BlACK , 5.0f);
}

bool Line::isValid() const {
	if (max(start.y, end.y) < 0.f || max(start.x, end.x) <0.f || min(start.x, end.x)>WIN_SIZE_X) {
		return false;
	}
	return true;
}