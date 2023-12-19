#include "Convex.h"

int partition(std::vector<std::pair<Vec2, float>>& , const int , const int);
void quick_sort(std::vector<std::pair<Vec2 , float>>& , const int  , const int);

Convex::Convex(const std::vector<Vec2> &points ,const float v_x, const float v_y, const float ang, const float ang_v, const bool act)
	:Object(Vec2(v_x , v_y), CONVEX, 10.f, COLOR_BLACK, act, ang, ang_v)
{
	//重心を取得
	Vec2 cen = Vec2(0, 0);
	for (int i = 0; i < points.size(); i++) {
		cen = cen + points[i];
	}
	cen = cen / (float)points.size();
	center = cen;
	pointNum = points.size();
	
	//点を重心からソート
	std::vector<std::pair<Vec2, float>> pointAng;
	//点と重心となす角をpairで保存
	pointAng.push_back(std::make_pair(points[0] , 0));
	for (int i = 1; i < points.size(); i++) {
		pointAng.push_back(std::make_pair(points[i] , getTheta(cen , points[0] , points[i])));
	}
	quick_sort(pointAng , 0 , pointAng.size());

	//ソート順にローカル座標とワールド座標を設定
	for (int i = 0; i < pointNum; i++) {
		pointsL.push_back(pointAng[i].first - cen);
		pointsW.push_back(pointAng[i].first);
	}
}

void Convex::loadGraph() {
	//画像のロード、サイズの取得
}

void Convex::updatePos(const float step) {
	//動かない物体の場合何もしない
	if (!active) {
		return;
	}
	center = center + (velocity * step);
	angle = angle + (angle_v * step);
	for (int i = 0; i < 4; i++) {
		//回転後のローカル座標を求める
		pointsL[i] = pointsL[i].rotation(angle);
		//ワールド座標に反映
		pointsW[i] = center + pointsL[i];
	}
}

void Convex::Draw() const {
	for (int i = 0; i < pointNum;i++) {
		DrawTriP(center , pointsW[i] , pointsW[(i+1)%pointNum] , COLOR_YELLOW , 0 ,3);
	}
}

//テスト用描画関数
void Convex::Draw(const unsigned int color) const{
	for (int i = 0; i < pointNum; i++) {
		Segment edge = getEdgeW(i);
		DrawSegment(edge , color);
	}
}

bool Convex::isValid() const {
	//最大値と最小値を取得
	float max_x = pointsW[0].x, max_y = pointsW[0].y, min_x = pointsW[0].x;
	for (int i = 1; i < 4; i++) {
		if (pointsW[i].x > max_x) {
			max_x = pointsW[i].x;
		}
		if (pointsW[i].y > max_y) {
			max_y = pointsW[i].y;
		}
		if (pointsW[i].x < min_x) {
			min_x = pointsW[i].x;
		}
	}
	//printfDx("max_x %f min_x %f max_y %f\n" , max_x , min_x , max_y);
	//画面外か判定
	if (max_x < 0.f || max_y < 0.f || min_x > WIN_SIZE_X) {
		return false;
	}

	return true;
}

std::string Convex::toString()const {
	return "Box";
}

Vec2 Convex::getPointW(const int i) const {
	if (i < 0 || pointsW.size() <= i) {
		return Vec2();
	}
	return pointsW[i];
}

int Convex::getPointNum() const {
	return pointNum;
}

//Vec2方向にローカル座標とワールド座標を移動する
void Convex::move(Vec2 vec) {
	for (int i = 0; i < pointNum; i++) {
		pointsL[i] = vec + pointsL[i];
		pointsW[i] = vec + pointsW[i];
	}
}

//ワールド座標の辺を返す
Segment Convex::getEdgeW(const int& i) const {
	return Segment(pointsW[i], pointsW[(i + 1) % pointNum]);
}

//クイックソートに用いるパーテーション
int partition(std::vector<std::pair<Vec2, float>>& v, const int s, const int e) {
	int i = s - 1;//pivot以下のindex
	float pivot = v[e - 1].second;
	for (int j = s; j < e;j++) {
		if (v[j].second <= pivot) {
			i++;
			auto tmp = v[j];
			v[j] = v[i];
			v[i] = tmp;
		}
	}
	return i;
}

void  quick_sort(std::vector<std::pair<Vec2, float>>& v, const int s, const int e) {
	if (s < e) {
		int p = partition(v, s, e);
		quick_sort(v, s, p );
		quick_sort(v, p + 1, e);
	}
}