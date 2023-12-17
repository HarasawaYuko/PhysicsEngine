#pragma once
#include "Math.h"

//衝突点の情報を保持する構造体
struct ContactPoint {
	ContactPoint(const float , const Vec2 , const Vec2, const Vec2 );
	float depth;
	Vec2 pointA;//Aの衝突点ローカル座標
	Vec2 pointB;//Bの衝突点ローカル座標
	Vec2 normal;//衝突法線ベクトル
};