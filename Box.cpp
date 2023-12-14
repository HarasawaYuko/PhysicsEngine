#include "Box.h"


int Box::fig;
int Box::figX;
int Box::figY;

Box::Box(const float cen_x, const float cen_y, const float h = 40.0f, const float w = 40.0f, const float v_x , const float v_y , const float ang  , const float ang_v)
	:height(h) , width(w) ,angle(ang) ,angle_v(ang_v), Object(BOX)
{
	center.set(cen_x, cen_y);
	velocity.set(v_x, v_y);
	//ローカル座標の追加
	pointsL[0].set(-width/2 , -height/2);
	pointsL[1].set(width / 2, -height / 2);
	pointsL[2].set(width / 2, height / 2);
	pointsL[3].set(-width / 2, height / 2);
	//点の追加
	pointsW[0].set(center.x - width/2 , center.y - height/2);
	pointsW[1].set(center.x - width / 2, center.y + height / 2);
	pointsW[2].set(center.x + width / 2, center.y - height / 2);
	pointsW[3].set(center.x + width / 2, center.y + height / 2);
}

void Box::loadGraph(){
	//画像のロード、サイズの取得
	fig = LoadGraph("pic/box.png");
	GetGraphSize(fig , &figX , &figY);
}

void Box::updatePos(const float step) {
	printfDx("Box UpdatePos()\n");
	//動かない物体の場合何もしない
	if (!active) {
		return;
	}
	center = center + (velocity * step);
	printfDx("angle_v:%f\n", angle_v);
	angle = angle + (angle_v * step);
	for (int i = 0; i < 4; i++) {
		//回転後のローカル座標を求める
		float rad = getRad(angle);
		float x = pointsL[i].x * cos(rad) - pointsL[i].y * sin(rad);
		float y = pointsL[i].x * sin(rad) + pointsL[i].y * cos(rad);
		//ワールド座標に反映
		pointsW[i].set(x ,y);
	}
}

void Box::Draw() const{
	DrawBoxP(center , figX/2 , figY/2 , angle , fig , height , width ,figX , figY );
}

bool Box::isValid() const {
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
	//画面外か判定
	if (max_x < 0.f || max_y < 0.f || min_x > WIN_SIZE_X) {
		return false;
	}
	return true;
}

std::string Box::toString()const {
	return "Box";
}