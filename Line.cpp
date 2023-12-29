#include "Line.h"

Line::Line (const Vec2 s ,const Vec2 e ,bool active , const float v_x ,const float v_y) 
	:Object(Vec2(v_x , v_y), LINE, 10, COLOR_BLACK, false), start(s), end(e)
{
	velocity.set(v_x , v_y);
	setBbox();
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

void Line::setBbox() {
	float xMax = -FLT_MAX;
	float xMin = FLT_MAX;
	float yMax = -FLT_MAX;
	float yMin = FLT_MAX;
	xMax = max(xMax, start.x);
	xMin = min(xMin, start.x);
	yMax = max(yMax, start.y);
	yMin = min(yMin, start.y);
	xMax = max(xMax, end.x);
	xMin = min(xMin, end.x);
	yMax = max(yMax, end.y);
	yMin = min(yMin, end.y);
	bbox.point = Vec2(xMin, yMin);
	bbox.height = yMax - yMin;
	bbox.width = xMax - xMin;
}

void Line::updatePos(const float step) {
	start = start + (velocity * step);
	end = end + (velocity *step);
	setBbox();
}