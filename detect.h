#pragma once
#include "Object.h"
#include "Circle.h"
#include "Line.h"
#include "Box.h"

namespace Detect {
	bool circle_line(Object*, Object* ,float* , Vec2* , Vec2*);
	bool circle_circle(Object*, Object*, float*, Vec2*, Vec2*);
	bool box_box(Object*, Object*, float*, Vec2*, Vec2*);
}