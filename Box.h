#pragma once

#include "Object.h"
#include "UIMaterial.h"

//長方形クラス
class Box :public Object {
private:
	std::vector<Vec2> pointsL;//ローカル座標での位置(左上から時計周り)
	std::vector<Vec2> pointsW;//ワールド座標での位置
	float height;//高さ
	float width;//幅
	static int fig;
	static int figX;
	static int figY;
	static int fig2;
	int pointNum;


public:
	Box(const float cen_x, const float cen_y, const float h  , const float w , const float v_x = 0, const float v_y = 0,const float ang = 0 , const float ang_v = 0 , const bool act = true);
	static void loadGraph();
	void updatePos(const float step)override;
	void Draw()const override;
	bool isValid()const override;
	std::string toString()const override;
	Vec2 getPointW(const int)const;
	int getPointNum()const;
	void move(Vec2);
	Segment getEdgeW(const int&)const;
};