#pragma once
#include "Object.h"

namespace Detect {
	bool circle_line(Object*, Object* ,float* , Vec2* , Vec2*);
	bool circle_circle(Object*, Object*, float*, Vec2*, Vec2*);
	bool box_box(Object*, Object*, float*, Vec2*, Vec2*);
	bool convex_convex(Object*, Object*, float*, Vec2*, Vec2*);
}