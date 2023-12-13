#pragma once

#include "Object.h"
#include "UIMaterial.h"

//長方形クラス
class Box :public Object {
private:
	Vec2 pointsL[4];//ローカル座標での位置(左上から時計周り)
	Vec2 pointsW[4];//ワールド座標での位置
	float height;//高さ
	float width;//幅
	static int fig;
	static int figX;
	static int figY;
	float angle_v;
	float angle;
	float inertiaTensor;//慣性テンソル

public:
	Box(const float cen_x, const float cen_y, const float h  , const float w , const float v_x = 0, const float v_y = 0,const float ang = 0);
	static void loadGraph();
	void updatePos(const float step)override;
	void Draw()const override;
	bool isValid()const override;
	std::string toString()const override;
};