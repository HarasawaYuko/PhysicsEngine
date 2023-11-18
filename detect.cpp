#include "detect.h"

//円と線の衝突判定
bool circle_line(Object* c , Object* l) {
	//それぞれの型へダウンキャスト
	Circle* circle = static_cast<Circle*>(c);
	Line* line = static_cast<Line*>(l);
	//ベクトルを取得
	Vec2 lineSeg = line->getE() - line->getS();
	Vec2 StoC = circle->getC() - line->getS();
	Vec2 EtoC = circle->getC() - line->getE();

	//円の中心と直線の最短距離を求める
	Vec2 NormalSeg = lineSeg.normalize();
	//半径より離れていれば接触していない
	if (std::abs(NormalSeg.cross(StoC)) > circle->getR()) {
		return false;
	}

	//線分が円の内部にあるか確認
	float dotS = lineSeg.dot(StoC);//始点からのベクトルとの内積
	float dotE = lineSeg.dot(EtoC);//終点からのベクトルとの内積
	if (dotS * dotE < 0) {
		return true;
	}

	//線分の端点が円の内部にあるか
	float r = circle->getR();
	Vec2 center = circle->getC();
	if (r > line->getS().distance(center) || r > line->getE().distance(center)) {
		return true;
	}
	else {
		return false;
	}
}