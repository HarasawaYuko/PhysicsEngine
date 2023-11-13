#include "Circle.h"

Circle::Circle() {

}

void Circle::Draw() {
	DrawCircleAA(center.getX(), center.getY(), r, 20, COLOR_RED, true);
}

