#include "Box.h"


int Box::fig;
int Box::figX;
int Box::figY;

Box::Box(const float cen_x, const float cen_y, const float h = 40.0f, const float w = 40.0f, const float v_x , const float v_y , const double ang )
	:height(h) , width(w) ,angle(ang) , Object(BOX)
{
	center.set(cen_x, cen_y);
	velocity.set(v_x, v_y);
	//点の追加（回転考慮せず）
	points[0].set(center.x - width/2 , center.y - height/2);
	points[1].set(center.x - width / 2, center.y + height / 2);
	points[2].set(center.x + width / 2, center.y - height / 2);
	points[3].set(center.x + width / 2, center.y + height / 2);
}

void Box::loadGraph(){
	//画像のロード、サイズの取得
	fig = LoadGraph("pic/box.png");
	GetGraphSize(fig , &figX , &figY);
}

void Box::updatePos(const float step) {
	//動かない物体の場合何もしない
	if (!active) return;
	center = center + (velocity * step);
	for (int i = 0; i < 4; i++) {
		points[i] = points[i] + (velocity * step);
	}
}

void Box::Draw() const{
	DrawBoxP(center , center , angle , fig , height , width ,figX , figY );
}

bool Box::isValid() const {
	//最大値と最小値を取得
	float max_x = points[0].x, max_y = points[0].y, min_x = points[0].x;
	for (int i = 1;  i < 4; i++) {
		if (points[i].x > max_x) {
			max_x = points[i].x;
		}
		if (points[i].y > max_y) {
			max_y = points[i].y;
		}
		if (points[i].x < min_x) {
			min_x = points[i].x;
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