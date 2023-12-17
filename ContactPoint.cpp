#include "ContactPoint.h"

ContactPoint::ContactPoint(const float d , const Vec2 pA ,const Vec2 pB , const Vec2 n) 
	:depth(d) , pointA(pA) , pointB(pB) , normal(n)
{
}