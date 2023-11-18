#pragma once
#include "Object.h"
#include "UIMaterial.h"

class Line :public Object {
private:
	Vec2 start;//始点
	Vec2 end;//終点
public:
	Line(const Vec2 ,const Vec2 , const bool active = true ,const float v_x = 0, const float v_y = 0 );
	void Draw()const override;
	bool isValid()const override;
	std::string toString()const override;
};