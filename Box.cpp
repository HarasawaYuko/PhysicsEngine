#include "Box.h"


int Box::fig;
int Box::fig2;
int Box::figX;
int Box::figY;

Box::Box(const float cen_x, const float cen_y, const float h = 40.0f, const float w = 40.0f, const float v_x , const float v_y , const float ang  , const float ang_v , const bool act)
	:height(h) , width(w) ,angle(ang) ,angle_v(ang_v), Object(BOX ,10.f ,COLOR_BLACK , act)
{
	center.set(cen_x, cen_y);
	velocity.set(v_x, v_y);
	//ローカル座標の追加
	pointsL.emplace_back( - width / 2, -height / 2);
	pointsL.emplace_back(width / 2, -height / 2);
	pointsL.emplace_back(width / 2, height / 2);
	pointsL.emplace_back(-width / 2, height / 2);
	//点の追加
	pointsW.emplace_back(center.x - width/2 , center.y - height/2);
	pointsW.emplace_back(center.x - width / 2, center.y + height / 2);
	pointsW.emplace_back(center.x + width / 2, center.y - height / 2);
	pointsW.emplace_back(center.x + width / 2, center.y + height / 2);

	pointNum = pointsW.size();
}

void Box::loadGraph(){
	//画像のロード、サイズの取得
	fig = LoadGraph("pic/box.png");
	fig2 = LoadGraph("pic/boxTouch.png");
	GetGraphSize(fig , &figX , &figY);
}

void Box::updatePos(const float step) {
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
		pointsW[i]= center + pointsL[i];
	}
	printfDx("L %s \n", pointsL[0].toString().c_str());
	printfDx("W %s \n" ,pointsW[0].toString().c_str());
}

void Box::Draw() const {
	if (touch) {
		DrawBoxP(center, figX / 2, figY / 2, angle, fig2, height, width, figX, figY);
	}
	else {
		DrawBoxP(center, figX / 2, figY / 2, angle, fig, height, width, figX, figY);
	}
}

bool Box::isValid() const {
	printfDx("Box isValid()\n");
	//最大値と最小値を取得
	float max_x = pointsW[0].x, max_y = pointsW[0].y, min_x = pointsW[0].x;
	for (int i = 1;  i < 4; i++) {
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

std::string Box::toString()const {
	return "Box";
}

float Box::getAngle()const {
	return angle;
}

Vec2 Box::getPointW(const int i) const{
	if (i < 0 || pointsW.size() <= i) {
		return Vec2();
	}
	return pointsW[i];
}

int Box::getPointNum() const{
	return pointNum;
}

//Vec2方向にローカル座標とワールド座標を移動する
void Box::move(Vec2 vec){
	for (int i = 0; i < pointNum; i++) {
		pointsL[i] = vec + pointsL[i];
		pointsW[i] = vec + pointsW[i];
	}
}

//ワールド座標の辺を返す
Segment Box::getEdgeW(const int &i) const{
	return Segment(pointsW[i] , pointsW[(i+1) % pointNum]);
}