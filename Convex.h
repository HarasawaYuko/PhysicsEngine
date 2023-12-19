#pragma once

#include "Object.h"
#include "UIMaterial.h"

//長方形クラス
class Convex :public Object {
private:
	std::vector<Vec2> pointsL;//ローカル座標
	std::vector<Vec2> pointsW;//ワールド座標
	float height;//高さ
	float width;//幅
	int pointNum;

public:
	Convex(const std::vector<Vec2>& points , const float v_x = 0, const float v_y = 0, const float ang = 0, const float ang_v = 0, const bool act = false);
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
