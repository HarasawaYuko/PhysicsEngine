#include "detect.h"

//�~�Ɛ��̏Փ˔���
bool Detect::circle_line(Object* c , Object* l , float* depth , Vec2* n  , Vec2* coord) {
	//���ꂼ��̌^�փ_�E���L���X�g
	Circle* circle = static_cast<Circle*>(c);
	Line* line = static_cast<Line*>(l);
	//�x�N�g�����擾
	Vec2 lineSeg = line->getE() - line->getS();
	Vec2 StoC = circle->getC() - line->getS();
	Vec2 EtoC = circle->getC() - line->getE();

	//�~�̒��S�ƒ����̍ŒZ���������߂�
	Vec2 NormalSeg = lineSeg.normalize();
	//���a��藣��Ă���ΐڐG���Ă��Ȃ�
	if (std::abs(NormalSeg.cross(StoC)) > circle->getR()) {
		return false;
	}

	//�������~�̓����ɂ��邩�m�F
	float dotS = lineSeg.dot(StoC);//�n�_����̃x�N�g���Ƃ̓���
	float dotE = lineSeg.dot(EtoC);//�I�_����̃x�N�g���Ƃ̓���
	if (dotS * dotE < 0) {
		return true;
	}

	//�����̒[�_���~�̓����ɂ��邩
	float r = circle->getR();
	Vec2 center = circle->getC();
	if (r > line->getS().distance(center) || r > line->getE().distance(center)) {
		return true;
	}
	else {
		return false;
	}
}

//�~�Ɖ~�̏Փ˔���
bool Detect::circle_circle(Object* c1 , Object* c2, float* depth, Vec2* n, Vec2* coord) {
	//�_�E���L���X�g
	Circle* cir1 = static_cast<Circle*>(c1);
	Circle* cir2 = static_cast<Circle*>(c2);

	//���S�Ԃ̋������擾
	float distance = cir1->getC().distance(cir2->getC());
	if (distance < cir1->getR() + cir2->getR()) {
		//�Փ˂��Ă���ꍇ�A�Փˏ����v�Z
		//�ђʐ[�x
		*depth = cir1->getR() + cir2->getR() - distance;
		//�Փ˃x�N�g�� c1->c2
		n->set(c2->getC().x - c1->getC().x , c2->getC().y - c1->getC().y);
		//�Փˍ��W c1���ł�c2�ɂ߂荞��ł���_ (c1�̒��S����n�̕�����r1�i�񂾓_)
		Vec2 nTmp = n->normalize() * cir1->getR();
		coord->set(c1->getC().x + nTmp.x, c1->getC().y + nTmp.y);
		return true;
	}
	return false;
}