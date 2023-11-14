#pragma once
#include "Object.h"
#include "UIMaterial.h"

//‰~ƒNƒ‰ƒX
class Circle :public Object{
private:
	float r;//”¼Œa
public:
	Circle(const float cen_x = 0 , const float cec_y = 0 , const float r = 10.0f , const float v_x = 0, const float v_y = 0);
	void Draw()const override;
	bool isValid()const override;
};