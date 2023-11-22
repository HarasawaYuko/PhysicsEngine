#include "Constraints.h"

bool Constraint::circle_line(Object* c, Object* l) {
	Circle* cir = static_cast<Circle*>(c);
	Line* line = static_cast<Line*>(l);

	return true;
}

bool Constraint::circle_circle(Collision &col) {
	Circle* cir1 = static_cast<Circle*>(col.getObj1());
	Circle* cir2 = static_cast<Circle*>(col.getObj2());
	return true;
}