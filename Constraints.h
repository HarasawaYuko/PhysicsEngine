#pragma once
#include "Object.h"
#include "Circle.h"
#include "Line.h"
#include "Collision.h"

namespace Constraint {
	bool circle_circle(Collision &);
	bool circle_line(Object* , Object*);
}