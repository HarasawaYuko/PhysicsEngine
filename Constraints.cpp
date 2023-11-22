#include "Constraints.h"

bool Constraint::circle_line(Object* c, Object* l) {
	Circle* cir = static_cast<Circle*>(c);
	Line* line = static_cast<Line*>(l);

	return true;
}

bool Constraint::circle_circle(Object* c1, Object* c2) {
	Circle* cir1 = static_cast<Circle*>(c1);
	Circle* cir2 = static_cast<Circle*>(c2);
	return true;
}