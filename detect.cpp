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
	float r = circle->getR();
	Vec2 center = circle->getC();

	//円の中心と直線の最短距離を求める
	Vec2 NormalSeg = lineSeg.normalize();
	float dis = std::abs(NormalSeg.cross(StoC));
	//半径より離れていれば接触していない
	if (dis > circle->getR()) {
		return false;
	}

	//線分が円の内部にあるか確認
	float dotS = lineSeg.dot(StoC);//始点からのベクトルとの内積
	float dotE = lineSeg.dot(EtoC);//終点からのベクトルとの内積
	if (dotS * dotE < 0) {
		//通常の接触
		//貫通深度
		*depth = circle->getR() - dis;
		//法線ベクトルを求める
		n->set(-NormalSeg.y , NormalSeg.x);
		//向きを確認
		if (NormalSeg.cross(*n) * NormalSeg.cross(StoC) > 0) {
			n->set(NormalSeg.y , -NormalSeg.x);
		}
		//printfDx("法線%s \n", n->toString().c_str());
		//衝突座標を求める
		*coord = center + *n * r;
		return true;
	}

	//線分の端点が円の内部にあるか
	float disS = line->getS().distance(center);
	float disE = line->getE().distance(center);
	if (r >  disS|| r > disE) {
		//端点で接触している
		//円の中心に近い端点を求める
		Vec2 point;
		float disC;
		if (disS < disE) {
			point = line->getS();
			disC = disS;
		}
		else {
			point = line->getE();
			disC = disE;
		}
		//貫通深度
		*depth = r - disC;
		//法線ベクトル
		*n = (point - center).normalize();
		//接触点
		*coord = center + (*n * r);
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
		//衝突ベクトル c1->c2(正規化)
		Vec2 nVec = Vec2(c2->getC().x - c1->getC().x, c2->getC().y - c1->getC().y).normalize();
		*n = nVec;
		nVec = nVec * cir1->getR();//大きさを半径に合わせる
		//衝突座標 c1が最もc2にめり込んでいる点 (c1の中心からnの方向にr1進んだ点)
		coord->set(c1->getC().x + nVec.x, c1->getC().y + nVec.y);
		return true;
	}
	return false;
}