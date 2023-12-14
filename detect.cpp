#include "detect.h"

//�v���g�^�C�v�錾
void projection(Vec2 , float* , float*);


//�~�Ɛ��̏Փ˔���
bool Detect::circle_line(Object* c , Object* l , float* depth , Vec2* n  , Vec2* coord) {
	//���ꂼ��̌^�փ_�E���L���X�g
	Circle* circle = static_cast<Circle*>(c);
	Line* line = static_cast<Line*>(l);
	//�x�N�g�����擾
	Vec2 lineSeg = line->getE() - line->getS();
	Vec2 StoC = circle->getC() - line->getS();
	Vec2 EtoC = circle->getC() - line->getE();
	float r = circle->getR();
	Vec2 center = circle->getC();

	//�~�̒��S�ƒ����̍ŒZ���������߂�
	Vec2 NormalSeg = lineSeg.normalize();
	float dis = std::abs(NormalSeg.cross(StoC));
	//���a��藣��Ă���ΐڐG���Ă��Ȃ�
	if (dis > circle->getR()) {
		return false;
	}

	//�������~�̓����ɂ��邩�m�F
	float dotS = lineSeg.dot(StoC);//�n�_����̃x�N�g���Ƃ̓���
	float dotE = lineSeg.dot(EtoC);//�I�_����̃x�N�g���Ƃ̓���
	if (dotS * dotE < 0) {
		//�ʏ�̐ڐG
		//�ђʐ[�x
		*depth = circle->getR() - dis;
		//�@���x�N�g�������߂�
		n->set(-NormalSeg.y , NormalSeg.x);
		//�������m�F
		if (NormalSeg.cross(*n) * NormalSeg.cross(StoC) > 0) {
			n->set(NormalSeg.y , -NormalSeg.x);
		}
		//printfDx("�@��%s \n", n->toString().c_str());
		//�Փˍ��W�����߂�
		*coord = center + *n * r;
		return true;
	}

	//�����̒[�_���~�̓����ɂ��邩
	float disS = line->getS().distance(center);
	float disE = line->getE().distance(center);
	if (r >  disS|| r > disE) {
		//�[�_�ŐڐG���Ă���
		//�~�̒��S�ɋ߂��[�_�����߂�
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
		//�ђʐ[�x
		*depth = r - disC;
		//�@���x�N�g��
		*n = (point - center).normalize();
		//�ڐG�_
		*coord = center + (*n * r);
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
		//�Փ˃x�N�g�� c1->c2(���K��)
		Vec2 nVec = Vec2(c2->getC().x - c1->getC().x, c2->getC().y - c1->getC().y).normalize();
		*n = nVec;
		nVec = nVec * cir1->getR();//�傫���𔼌a�ɍ��킹��
		//�Փˍ��W c1���ł�c2�ɂ߂荞��ł���_ (c1�̒��S����n�̕�����r1�i�񂾓_)
		coord->set(c1->getC().x + nVec.x, c1->getC().y + nVec.y);
		return true;
	}
	return false;
}

//�l�p�`�Ǝl�p�`�̏Փ˔���i�ʕ�ɕύX�\��j
bool Detect::box_box(Object* b1, Object* b2, float* depth, Vec2* n, Vec2* coord) {
	//�_�E���L���X�g
	Box* box1 = static_cast<Box*>(b1);
	Box* box2 = static_cast<Box*>(b2);

	//����������
	Vec2 axis;//���������
	float max1, min1;//box1�̓��e���W�̍ő�ŏ�
	float max2, min2;//box2�̓��e���W�̍ő�ŏ�
	//���_�����_�̃x�N�g���̕���������
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			axis = box1->getPointW(i) - box2->getPointW(j);

		}
	}
	return false;
}

//axis��box(convex)�𓊉e���čő�ƍŏ���Ԃ�
void projection() {

}