#pragma once
#include "Circle.h"
#include "Collision.h"
#include "SolvetBody.h"
#include "Convex.h"
#include "World.h"

namespace Solver {
	void initialize(const float);
	void solve(const std::vector<Object*>& , std::vector<Collision>&);
	void solve(World*);
}