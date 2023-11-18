#pragma once
#include "Math.h"
#include "Object.h"

enum Pair : uint16_t {
	CIRCLE_CIRCLE = 0b0000'0000'0000'0001,
	CIRCLE_LINE   = 0b0000'0000'0000'0011,
	CIRCLE_BOX    = 0b0000'0000'0000'0101,
	LINE_LINE     = 0b0000'0000'0000'0010,
	LINE_BOX      = 0b0000'0000'0000'0110,
	BOX_BOX       = 0b0000'0000'0000'0100
};

class ObjectPair {
private:
public:
	ObjectPair();
};