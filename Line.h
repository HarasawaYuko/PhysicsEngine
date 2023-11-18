#pragma once
#include "Object.h"
#include "UIMaterial.h"

class Line :public Object {
private:
	Vec2 start;//�n�_
	Vec2 end;//�I�_
public:
	Line(const Vec2 ,const Vec2 , const bool active = true ,const float v_x = 0, const float v_y = 0 );
	void Draw()const override;
	bool isValid()const override;
	std::string toString()const override;
};