#pragma once
#include "Object.h"
#include "Circle.h"
#include "Line.h"

namespace Detect {
	bool circle_line(Object*, Object*);
	bool circle_circle(Object*, Object*);
}