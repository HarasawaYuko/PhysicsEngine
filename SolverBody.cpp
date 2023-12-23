#include "SolvetBody.h"

SolverBody::SolverBody(const float ang , const float mInv , const float iInv) 
	:deltaLinearV(Vec2(0.f , 0.f)) , deltaRotaV(0.f) , angle(ang) , massInv(mInv) , inertiaInv(iInv)
{}