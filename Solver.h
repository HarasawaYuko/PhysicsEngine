#pragma once
#include "Circle.h"
#include "Line.h"
#include "Collision.h"
#include "SolvetBody.h"
#include "Convex.h"
#include "World.h"

namespace Solver {
	void initialize(const float);
	void solve(const std::vector<Object*>& , std::vector<Collision>&);
	void solve(World*);

	bool circle_circle(Collision &);
	bool circle_line(Collision &);
}