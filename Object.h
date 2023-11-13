#pragma once
#include "Math.h"

//Objectクラス　演算対象の図形は必ず継承する
enum Type {
	CIRCLE
};

class Object {
protected:
	Vec2 center;//重心座標
	Vec2 force;//力
	Vec2 acceleration;//加速度
	Vec2 velocity;//速度
	Object(){}
public:
	virtual void Draw();
	Type type;
};