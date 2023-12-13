#include "Box.h"


int Box::fig;
int Box::figX;
int Box::figY;

Box::Box(const float cen_x, const float cen_y, const float h = 40.0f, const float w = 40.0f, const float v_x , const float v_y , const float ang )
	:height(h) , width(w) ,angle(ang) , Object(BOX)
{
	center.set(cen_x, cen_y);
	velocity.set(v_x, v_y);
	//���[�J�����W�̒ǉ�
	pointsL[0].set(-width/2 , -height/2);
	pointsL[1].set(width / 2, -height / 2);
	pointsL[2].set(width / 2, height / 2);
	pointsL[3].set(-width / 2, height / 2);
	//�_�̒ǉ�
	pointsW[0].set(center.x - width/2 , center.y - height/2);
	pointsW[1].set(center.x - width / 2, center.y + height / 2);
	pointsW[2].set(center.x + width / 2, center.y - height / 2);
	pointsW[3].set(center.x + width / 2, center.y + height / 2);

	angle_v = 0.5f;
}

void Box::loadGraph(){
	//�摜�̃��[�h�A�T�C�Y�̎擾
	fig = LoadGraph("pic/box.png");
	GetGraphSize(fig , &figX , &figY);
}

void Box::updatePos(const float step) {
	//�����Ȃ����̂̏ꍇ�������Ȃ�
	if (!active) return;
	center = center + (velocity * step);
	angle = angle + (angle_v * step);
	for (int i = 0; i < 4; i++) {
		pointsW[i] = pointsW[i] + (velocity * step);
		//angle�̕���]

	}
}

void Box::Draw() const{
	DrawBoxP(center , figX/2 , figY/2 , angle , fig , height , width ,figX , figY );
}

bool Box::isValid() const {
	//�ő�l�ƍŏ��l���擾
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
	//��ʊO������
	if (max_x < 0.f || max_y < 0.f || min_x > WIN_SIZE_X) {
		return false;
	}
	return true;
}

std::string Box::toString()const {
	return "Box";
}