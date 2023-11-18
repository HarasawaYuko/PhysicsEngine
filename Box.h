#pragma once

#include "Object.h"
#include "UIMaterial.h"

//’·•ûŒ`ƒNƒ‰ƒX
class Box :public Object {
private:
	Vec2 points[4];
	float height;//‚‚³
	float width;//•
	static int fig;
	static int figX;
	static int figY;
	double angle;
public:
	Box(const float cen_x, const float cen_y, const float h  , const float w , const float v_x = 0, const float v_y = 0,const double ang = 0);
	static void loadGraph();
	void updatePos(const float step)override;
	void Draw()const override;
	bool isValid()const override;
	std::string toString()const override;
};