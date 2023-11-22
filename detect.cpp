#include "detect.h"

//円と線の衝突判定
bool Detect::circle_line(Object* c , Object* l , float* depth , Vec2* n  , Vec2* coord) {
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
bool Detect::circle_circle(Object* c1 , Object* c2, float* depth, Vec2* n, Vec2* coord) {
	//ダウンキャスト
	Circle* cir1 = static_cast<Circle*>(c1);
	Circle* cir2 = static_cast<Circle*>(c2);

	//中心間の距離を取得
	float distance = cir1->getC().distance(cir2->getC());
	if (distance < cir1->getR() + cir2->getR()) {
		//衝突している場合、衝突情報を計算
		//貫通深度
		*depth = cir1->getR() + cir2->getR() - distance;
		//衝突ベクトル c1->c2
		n->set(c2->getC().x - c1->getC().x , c2->getC().y - c1->getC().y);
		//衝突座標 c1が最もc2にめり込んでいる点 (c1の中心からnの方向にr1進んだ点)
		Vec2 nTmp = n->normalize() * cir1->getR();
		coord->set(c1->getC().x + nTmp.x, c1->getC().y + nTmp.y);
		return true;
	}
	return false;
}