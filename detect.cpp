#include "detect.h"
#include "Circle.h"
#include "Line.h"
#include "Box.h"
#include "Convex.h"
#include "DEBUG.h"
//プロトタイプ宣言
void projection(Vec2 , Box* , float* , float*);
void projection(Vec2, Convex*, float*, float*);
bool getDepth(const float, const float, const float, const float  , float* , float*);
Vec2 getContactPoint(const Vec2& , const Segment&);
bool isCross(const BBox&, const BBox&);

bool Detect::broard(const Object* obj1 ,const Object* obj2) {
	//バウンディングボックスを取得
	const BBox& bbox1 = obj1->getBbox();
	const BBox& bbox2 = obj2->getBbox();

	if (isCross(bbox1, bbox2)) {
		return true;
	}
	return false;
}

/**ナローフェーズ****************/

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
		//衝突座標を求める
		coord[0] = center + *n * r;
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
		coord[0] = center + (*n * r);
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
		coord[0] = Vec2(c1->getC().x + nVec.x, c1->getC().y + nVec.y);
		coord[1] = Vec2(c2->getC().x - nVec.x, c2->getC().y - nVec.y);
		return true;
	}
	return false;
}

//四角形と四角形の衝突判定（凸包に変更予定）
bool Detect::box_box(Object* b1, Object* b2, float* depth, Vec2* n, Vec2* coord) {
	//ダウンキャスト
	Box* box1 = static_cast<Box*>(b1);
	Box* box2 = static_cast<Box*>(b2);

	//分離軸判定
	float max1, min1;//box1の投影座標の最大最小
	float max2, min2;//box2の投影座標の最大最小
	bool result;//判定結果 接触してればtrue
	float max_depth = -INF;
	Vec2 axisMax;//分離軸候補
	//頂点→頂点のベクトルの分離軸判定
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			Vec2 axis = (box1->getPointW(i) - box2->getPointW(j)).normalize();
			projection(axis , box1 , &min1 , &max1);
			projection(axis , box2 , &min2 , &max2);
			float d1, d2;
			if (getDepth(min1, max1, min2, max2, &d1, &d2)) {
				return false;
			}
			//衝突している場合、貫通深度と法線ベクトルを設定
			assert(d1 <= 0 && d2 <= 0);
			if (max_depth < d1) {
				max_depth = d1;
				axisMax = axis;
			}
			if (max_depth < d2) {
				max_depth = d2;
				axisMax = axis * -1;
			}
		}
	}
	//辺の法線ベクトルの分離軸判定
	//convex1
	for (int i = 0 ; i < box1->getPointNum(); i++) {
		Vec2 axis = (box1->getPointW(i) - box1->getPointW((i+1)%4)).normalize().normal();
		projection(axis, box1, &min1, &max1);
		projection(axis, box2, &min2, &max2);
		float d1, d2;
		if (getDepth(min1, max1, min2, max2, &d1, &d2)) {
			return false;
		}
		//衝突している場合、貫通深度と法線ベクトルを設定
		assert(d1 <= 0 && d2 <= 0);
		if (max_depth < d1) {
			max_depth = d1;
			axisMax = axis;
		}
		if (max_depth < d2) {
			max_depth = d2;
			axisMax = axis * -1;
		}
	}
	//convex2
	for (int i = 0 ; i < box2->getPointNum(); i++) {
		Vec2 axis = (box2->getPointW(i) - box2->getPointW((i + 1) % 4)).normalize().normal();
		projection(axis, box1, &min1, &max1);
		projection(axis, box2, &min2, &max2);
		float d1, d2;
		if (getDepth(min1, max1, min2, max2, &d1, &d2)) {
			return false;
		}
		//衝突している場合、貫通深度と法線ベクトルを設定
		assert(d1 <= 0 && d2 <= 0);
		if (max_depth < d1) {
			max_depth = d1;
			axisMax = axis;
		}
		if (max_depth < d2) {
			max_depth = d2;
			axisMax = axis * -1;
		}
	}
	//貫通深度等の設定
	*depth = max_depth;
	*n = axisMax;


	//衝突点を取得
	float minDistance = INF;//最短距離
	int minPattern = 0;
	bool  minA = false;
	Vec2 minPoint;
	Segment minEdge;
	//物体1を貫通深度より若干ずらす
	Vec2 disV = axisMax * (abs(*depth) * 2.f);//ずらすベクトル
	box1->move(disV);
	//物体1の頂点から見た最短距離
	for (int i = 0; i < box1->getPointNum();i++) {
		for (int j = 0; j < box2->getPointNum(); j++) {
			int pattern;
			Segment edge = box2->getEdgeW(j);
			float dis = getDistance(box1->getPointW(i), edge , &pattern);
			if (minDistance > dis) {
				//記録
				minPattern = pattern;
				minA = true;
				minPoint = box1->getPointW(i);
				minEdge = edge;
			}
		}
	}
	//物体2の頂点から見た最短距離
	for (int i = 0; i < box2->getPointNum(); i++) {
		for (int j = 0; j < box1->getPointNum(); j++) {
			int pattern;
			Segment edge = box1->getEdgeW(j);
			float dis = getDistance(box2->getPointW(i), edge, &pattern);
			if (minDistance > dis) {
				//記録
				minPattern = pattern;
				minA = false;
				minPoint = box2->getPointW(i);
				minEdge = edge;
			}
		}
	}
	//最短距離だった組み合わせの衝突点のローカル座標を設定
	if (minA) {//Aが頂点Bが辺だった場合
		coord[0] = WtoL(minPoint , box1->getC() , box1->getAngle());
		switch (minPattern) {
		case 0:
			coord[1] = WtoL(minEdge.start , box2->getC() , box2->getAngle());
			break;
		case 1:
			coord[1] = WtoL(minEdge.end , box2->getC(), box2->getAngle());
			break;
		case 2:
			coord[1] = WtoL(getContactPoint(minPoint  , minEdge) , box2->getC(), box2->getAngle());
			break;
		default:
			assert(false);
			break;
		}
	}
	else {
		coord[1] = WtoL(minPoint, box2->getC(), box2->getAngle());
		switch (minPattern) {
		case 0:
			coord[0] = WtoL(minEdge.start, box1->getC(), box1->getAngle());
			break;
		case 1:
			coord[0] = WtoL(minEdge.end, box1->getC(), box1->getAngle());
			break;
		case 2:
			coord[0] = WtoL(getContactPoint(minPoint, minEdge), box1->getC(), box1->getAngle());
			break;
		default:
			assert(false);
			break;
		}
	}

	//ずらした分戻す
	box1->move(disV * -1);

	return true;
}

bool Detect::convex_convex(Object* c1, Object* c2, float* depth, Vec2* n, Vec2* coord) {
	//ダウンキャスト
	Convex* con1 = static_cast<Convex*>(c1);
	Convex* con2 = static_cast<Convex*>(c2);

	//分離軸判定
	float max1, min1;//box1の投影座標の最大最小
	float max2, min2;//box2の投影座標の最大最小
	bool result;//判定結果 接触してればtrue
	float max_depth = -INF;
	Vec2 axisMax;//分離軸候補
	//頂点→頂点のベクトルの分離軸判定
	for (int i = 0; i < con1->getPointNum(); i++) {
		for (int j = i; j < con2->getPointNum(); j++) {
			Vec2 axis = (con1->getPointW(i) - con2->getPointW(j)).normalize();
			projection(axis, con1, &min1, &max1);
			projection(axis, con2, &min2, &max2);
			float d1, d2;
			if (getDepth(min1, max1, min2, max2, &d1, &d2)) {
				return false;
			}
			//衝突している場合、貫通深度と法線ベクトルを設定
			assert(d1 <= 0 && d2 <= 0);
			if (max_depth < d1) {
				max_depth = d1;
				axisMax = axis;
			}
			if (max_depth < d2) {
				max_depth = d2;
				axisMax = axis * -1;
			}
		}
	}
	//辺の法線ベクトルの分離軸判定
	//convex1
	for (int i = 0; i < con1->getPointNum(); i++) {
		Vec2 axis = (con1->getPointW(i) - con1->getPointW((i + 1) % con1->getPointNum())).normalize().normal();
		projection(axis, con1, &min1, &max1);
		projection(axis, con2, &min2, &max2);
		float d1, d2;
		if (getDepth(min1, max1, min2, max2, &d1, &d2)) {
			return false;
		}
		//衝突している場合、貫通深度と法線ベクトルを設定
		assert(d1 <= 0 && d2 <= 0);
		if (max_depth < d1) {
			max_depth = d1;
			axisMax = axis;
		}
		if (max_depth < d2) {
			max_depth = d2;
			axisMax = axis * -1;
		}
	}
	//convex2
	for (int i = 0; i < con2->getPointNum(); i++) {
		Vec2 axis = (con2->getPointW(i) - con2->getPointW((i + 1) % con2->getPointNum())).normalize().normal();
		projection(axis, con1, &min1, &max1);
		projection(axis, con2, &min2, &max2);
		float d1, d2;
		if (getDepth(min1, max1, min2, max2, &d1, &d2)) {
			return false;
		}
		//衝突している場合、貫通深度と法線ベクトルを設定
		assert(d1 <= 0 && d2 <= 0);
		if (max_depth < d1) {
			max_depth = d1;
			axisMax = axis;
		}
		if (max_depth < d2) {
			max_depth = d2;
			axisMax = axis * -1;
		}
	}
	//貫通深度等の設定
	*depth = max_depth;
	*n = axisMax;


	//衝突点を取得
	float minDistance = INF;//最短距離
	bool  minA = false;
	int minPointIndex = -1;
	//物体1を貫通深度より若干ずらす
	Vec2 disV = axisMax * (abs(*depth) * 2.f);//ずらすベクトル
	con1->move(disV);
	//物体1の頂点から見た最短距離
	for (int i = 0; i < con1->getPointNum(); i++) {
		for (int j = 0; j < con2->getPointNum(); j++) {
			Segment edge = con2->getEdgeW(j);
			float dis = getDistance(con1->getPointW(i), edge);
			if (minDistance > dis) {
				//記録
				minA = true;
				minDistance = dis;
				minPointIndex = i;
			}
		}
	}
	//物体2の頂点から見た最短距離
	for (int i = 0; i < con2->getPointNum(); i++) {
		for (int j = 0; j < con1->getPointNum(); j++) {
			int pattern;
			Segment edge = con1->getEdgeW(j);
			float dis = getDistance(con2->getPointW(i), edge);
			if (minDistance > dis) {
				//記録
				minA = false;
				minDistance = dis;
				minPointIndex = i;
			}
		}
	}
	
	//ずらした分戻す
	con1->move(disV * -1);

	//最短距離だった組み合わせの衝突点のローカル座標を設定
	Vec2 minPoint;
	Segment minEdge;
	if (minA) {//Aが頂点Bが辺だった場合
		minPoint = con1->getPointW(minPointIndex);
		coord[0] = WtoL(minPoint, con1->getC(), con1->getAngle());
		coord[1] = WtoL(minPoint, con2->getC(), con2->getAngle());
		//minEdge = con2->getEdgeW(minEdgeIndex);
		//switch (minPattern) {
		//case 0:
		//	coord[1] = WtoL(minEdge.start, con2->getC(), con2->getAngle());
		//	break;
		//case 1:
		//	coord[1] = WtoL(minEdge.end, con2->getC(), con2->getAngle());
		//	break;
		//case 2:
		//	coord[1] = WtoL(getContactPoint(minPoint, minEdge), con2->getC(), con2->getAngle());
		//	break;
		//default:
		//	assert(false);
		//	break;
		//}
	}
	else {
		minPoint = con2->getPointW(minPointIndex);
		coord[1] = WtoL(minPoint, con2->getC(), con2->getAngle());
		coord[0] = WtoL(minPoint, con1->getC(), con1->getAngle());
		/*minEdge = con1->getEdgeW(minEdgeIndex);
		switch (minPattern) {
		case 0:
			coord[0] = WtoL(minEdge.start, con1->getC(), con1->getAngle());
			break;
		case 1:
			coord[0] = WtoL(minEdge.end, con1->getC(), con1->getAngle());
			break;
		case 2:
			coord[0] = WtoL(getContactPoint(minPoint, minEdge), con1->getC(), con1->getAngle());
			break;
		default:
			assert(false);
			break;
		}*/
	}


	//DEBUG
	Debug* debug = Debug::instance();
	debug->minPointA = minPoint;
	debug->minEdgeB = minEdge;


	return true;
}

/**************************************************************/

//axisにbox(convex)を投影して最大と最小を返す
void projection(Vec2 axis , Box* box, float* min , float* max) {
	float min_ = INF;
	float max_ = -INF;
	//全ての頂点を投影
	for (int i = 0; i < box->getPointNum(); i++) {
		float dot;
		dot = axis.dot(box->getPointW(i));
		min_ = min(min_ , dot);
		max_ = max(max_, dot);
	}
	*min = min_;
	*max = max_;
}

//axisにbox(convex)を投影して最大と最小を返す
void projection(Vec2 axis, Convex* con, float* min, float* max) {
	float min_ = INF;
	float max_ = -INF;
	//全ての頂点を投影
	for (int i = 0; i < con->getPointNum(); i++) {
		float dot;
		dot = axis.dot(con->getPointW(i));
		min_ = min(min_, dot);
		max_ = max(max_, dot);
	}
	*min = min_;
	*max = max_;
}

//軸投影の結果、分離軸があるか判定する　交差していない(d>0)の時はtrue
bool getDepth(const float min1 , const float max1 ,const float min2 , const float max2  , float* d1 , float* d2) {
	//貫通深度を求めて、正負で判定する
	*d1 = min1 - max2;
	*d2 = min2 - max1;
	if (*d1  > 0 || *d2 > 0) {
		return true;
	}
	return false;
}

Vec2 getContactPoint(const Vec2& point , const Segment& edge) {
	//辺ベクトルの正規化
	Vec2 edgeVec =(edge.end - edge.start).normalize();
	Vec2 StoP = point - edge.start;
	//始点からの距離を求める
	float dis = StoP.dot(edgeVec);
	return edge.start + (edgeVec * dis);
}


bool isCross(const BBox& b1, const BBox& b2) {
	//x軸を調べる
	if (b1.point.x + b1.width <= b2.point.x || b2.point.x + b2.width <= b1.point.x) {
		return false;
	}
	//y軸を調べる
	if (b1.point.y + b1.height <= b2.point.y || b2.point.y + b2.height <= b1.point.y) {
		return false;
	}
	return true;
}