#include "detect.h"

//円と線の衝突判定
bool Detect::circle_line(Object* c , Object* l) {
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

//円と円の衝突判定
bool Detect::circle_circle(Object* c1 , Object* c2) {
	//ダウンキャスト
	Circle* cir1 = static_cast<Circle*>(c1);
	Circle* cir2 = static_cast<Circle*>(c2);

	//中心間の距離を取得
	float distance = cir1->getC().distance(cir2->getC());
	if (distance < cir1->getR() + cir2->getR()) {
		return true;
	}
	return false;
}