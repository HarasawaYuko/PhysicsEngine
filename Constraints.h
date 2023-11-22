#pragma once
#include "Object.h"
#include "Circle.h"
#include "Line.h"

namespace Constraint {
	bool circle_circle(Object* , Object*);
	bool circle_line(Object* , Object*);
}