#include "Pair.h"

Pair::Pair(Object* obj1 , Object* obj2) {
	//ƒL[‚ðÝ’è
	uint32_t id1 = (uint32_t)obj1->getId();
	uint32_t id2 = (uint32_t)obj2->getId();
	if (id1 < id2) {
		id2 = id2 << 8;
	}
	else {
		id1 = id1 << 8;
	}
	key = id1 | id2;
	kind = (Kind)(obj1->getType() | obj2->getType());
	obj[0] = obj1;
	obj[1] = obj2;

	collision = new Collision();
}

Kind Pair::getKind()const {
	return kind;
}

PairType Pair::getType()const {
	return type;
}

uint32_t Pair::getKey()const {
	return key;
}

void Pair::setType(PairType type_) {
	this->type = type_;
}

Object* Pair::getObj0() const{
	return obj[0];
}

Object* Pair::getObj1() const{
	return obj[1];
}

Collision* Pair::getCol()const {
	return collision;
}

std::string Pair::toString()const {
	std::string str;
	//Ží—Þ‚ÌŽæ“¾
	switch (kind) {
	case CIRCLE_CIRCLE:
		str += "Cir vs Cir";
		break;
	case CIRCLE_CONVEX:
		str += "Cir vs Con";
		break;
	case CONVEX_CONVEX:
		str += "Con vs Con";
		break;
	}
	str += "  " + std::to_string(key);
	switch (type) {
	case New:
		str += " New";
		break;
	case Keep:
		str += " Keep";
		break;
	}
	str += "\n";
	
	str += "contactPoint:" + std::to_string(collision->getContactNum()) + "\n";
	for (int i = 0; i < collision->getContactNum();i++) {
		ContactPoint cp = collision->contactPoints[i];
		char tmp[255];
		sprintf_s(tmp, "%6.1f", cp.depth);
		str += std::to_string(i) + " depth:" + std::string(tmp) + " pointA:" + cp.pointA.toString() + " pointB:" + cp.pointB.toString() + " normal" + cp.normal.toString() + "\n";
	}

	return str;
}