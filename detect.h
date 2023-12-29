#pragma once
#include "Object.h"

namespace Detect {
	//ブロードフェーズ
	bool broard(const Object* ,const Object*);

	//ナローフェーズ
	bool circle_line(Object*, Object* ,float* , Vec2* , Vec2*);
	bool circle_circle(Object*, Object*, float*, Vec2*, Vec2*);
	bool box_box(Object*, Object*, float*, Vec2*, Vec2*);
	bool convex_convex(Object*, Object*, float* depth, Vec2* n, Vec2* coord);
}