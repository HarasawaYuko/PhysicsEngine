#include "detect.h"
#include "Circle.h"
#include "Line.h"
#include "Box.h"
#include "Convex.h"
#include "DEBUG.h"
//�v���g�^�C�v�錾
void projection(Vec2 , Box* , float* , float*);
void projection(Vec2, Convex*, float*, float*);
bool getDepth(const float, const float, const float, const float  , float* , float*);
Vec2 getContactPoint(const Vec2& , const Segment&);
bool isCross(const BBox&, const BBox&);

bool Detect::broard(const Object* obj1 ,const Object* obj2) {
	//�o�E���f�B���O�{�b�N�X���擾
	const BBox& bbox1 = obj1->getBbox();
	const BBox& bbox2 = obj2->getBbox();

	if (isCross(bbox1, bbox2)) {
		return true;
	}
	return false;
}

/**�i���[�t�F�[�Y****************/

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
		//�Փˍ��W�����߂�
		coord[0] = center + *n * r;
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
		coord[0] = center + (*n * r);
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
		coord[0] = Vec2(c1->getC().x + nVec.x, c1->getC().y + nVec.y);
		coord[1] = Vec2(c2->getC().x - nVec.x, c2->getC().y - nVec.y);
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
	float max1, min1;//box1�̓��e���W�̍ő�ŏ�
	float max2, min2;//box2�̓��e���W�̍ő�ŏ�
	bool result;//���茋�� �ڐG���Ă��true
	float max_depth = -INF;
	Vec2 axisMax;//���������
	//���_�����_�̃x�N�g���̕���������
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			Vec2 axis = (box1->getPointW(i) - box2->getPointW(j)).normalize();
			projection(axis , box1 , &min1 , &max1);
			projection(axis , box2 , &min2 , &max2);
			float d1, d2;
			if (getDepth(min1, max1, min2, max2, &d1, &d2)) {
				return false;
			}
			//�Փ˂��Ă���ꍇ�A�ђʐ[�x�Ɩ@���x�N�g����ݒ�
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
	//�ӂ̖@���x�N�g���̕���������
	//convex1
	for (int i = 0 ; i < box1->getPointNum(); i++) {
		Vec2 axis = (box1->getPointW(i) - box1->getPointW((i+1)%4)).normalize().normal();
		projection(axis, box1, &min1, &max1);
		projection(axis, box2, &min2, &max2);
		float d1, d2;
		if (getDepth(min1, max1, min2, max2, &d1, &d2)) {
			return false;
		}
		//�Փ˂��Ă���ꍇ�A�ђʐ[�x�Ɩ@���x�N�g����ݒ�
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
		//�Փ˂��Ă���ꍇ�A�ђʐ[�x�Ɩ@���x�N�g����ݒ�
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
	//�ђʐ[�x���̐ݒ�
	*depth = max_depth;
	*n = axisMax;


	//�Փ˓_���擾
	float minDistance = INF;//�ŒZ����
	int minPattern = 0;
	bool  minA = false;
	Vec2 minPoint;
	Segment minEdge;
	//����1���ђʐ[�x���኱���炷
	Vec2 disV = axisMax * (abs(*depth) * 2.f);//���炷�x�N�g��
	box1->move(disV);
	//����1�̒��_���猩���ŒZ����
	for (int i = 0; i < box1->getPointNum();i++) {
		for (int j = 0; j < box2->getPointNum(); j++) {
			int pattern;
			Segment edge = box2->getEdgeW(j);
			float dis = getDistance(box1->getPointW(i), edge , &pattern);
			if (minDistance > dis) {
				//�L�^
				minPattern = pattern;
				minA = true;
				minPoint = box1->getPointW(i);
				minEdge = edge;
			}
		}
	}
	//����2�̒��_���猩���ŒZ����
	for (int i = 0; i < box2->getPointNum(); i++) {
		for (int j = 0; j < box1->getPointNum(); j++) {
			int pattern;
			Segment edge = box1->getEdgeW(j);
			float dis = getDistance(box2->getPointW(i), edge, &pattern);
			if (minDistance > dis) {
				//�L�^
				minPattern = pattern;
				minA = false;
				minPoint = box2->getPointW(i);
				minEdge = edge;
			}
		}
	}
	//�ŒZ�����������g�ݍ��킹�̏Փ˓_�̃��[�J�����W��ݒ�
	if (minA) {//A�����_B���ӂ������ꍇ
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

	//���炵�����߂�
	box1->move(disV * -1);

	return true;
}

bool Detect::convex_convex(Object* c1, Object* c2, float* depth, Vec2* n, Vec2* coord) {
	//�_�E���L���X�g
	Convex* con1 = static_cast<Convex*>(c1);
	Convex* con2 = static_cast<Convex*>(c2);

	//����������
	float max1, min1;//box1�̓��e���W�̍ő�ŏ�
	float max2, min2;//box2�̓��e���W�̍ő�ŏ�
	bool result;//���茋�� �ڐG���Ă��true
	float max_depth = -INF;
	Vec2 axisMax;//���������
	//���_�����_�̃x�N�g���̕���������
	for (int i = 0; i < con1->getPointNum(); i++) {
		for (int j = i; j < con2->getPointNum(); j++) {
			Vec2 axis = (con1->getPointW(i) - con2->getPointW(j)).normalize();
			projection(axis, con1, &min1, &max1);
			projection(axis, con2, &min2, &max2);
			float d1, d2;
			if (getDepth(min1, max1, min2, max2, &d1, &d2)) {
				return false;
			}
			//�Փ˂��Ă���ꍇ�A�ђʐ[�x�Ɩ@���x�N�g����ݒ�
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
	//�ӂ̖@���x�N�g���̕���������
	//convex1
	for (int i = 0; i < con1->getPointNum(); i++) {
		Vec2 axis = (con1->getPointW(i) - con1->getPointW((i + 1) % con1->getPointNum())).normalize().normal();
		projection(axis, con1, &min1, &max1);
		projection(axis, con2, &min2, &max2);
		float d1, d2;
		if (getDepth(min1, max1, min2, max2, &d1, &d2)) {
			return false;
		}
		//�Փ˂��Ă���ꍇ�A�ђʐ[�x�Ɩ@���x�N�g����ݒ�
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
		//�Փ˂��Ă���ꍇ�A�ђʐ[�x�Ɩ@���x�N�g����ݒ�
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
	//�ђʐ[�x���̐ݒ�
	*depth = max_depth;
	*n = axisMax;


	//�Փ˓_���擾
	float minDistance = INF;//�ŒZ����
	bool  minA = false;
	int minPointIndex = -1;
	//����1���ђʐ[�x���኱���炷
	Vec2 disV = axisMax * (abs(*depth) * 2.f);//���炷�x�N�g��
	con1->move(disV);
	//����1�̒��_���猩���ŒZ����
	for (int i = 0; i < con1->getPointNum(); i++) {
		for (int j = 0; j < con2->getPointNum(); j++) {
			Segment edge = con2->getEdgeW(j);
			float dis = getDistance(con1->getPointW(i), edge);
			if (minDistance > dis) {
				//�L�^
				minA = true;
				minDistance = dis;
				minPointIndex = i;
			}
		}
	}
	//����2�̒��_���猩���ŒZ����
	for (int i = 0; i < con2->getPointNum(); i++) {
		for (int j = 0; j < con1->getPointNum(); j++) {
			int pattern;
			Segment edge = con1->getEdgeW(j);
			float dis = getDistance(con2->getPointW(i), edge);
			if (minDistance > dis) {
				//�L�^
				minA = false;
				minDistance = dis;
				minPointIndex = i;
			}
		}
	}
	
	//���炵�����߂�
	con1->move(disV * -1);

	//�ŒZ�����������g�ݍ��킹�̏Փ˓_�̃��[�J�����W��ݒ�
	Vec2 minPoint;
	Segment minEdge;
	if (minA) {//A�����_B���ӂ������ꍇ
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

//axis��box(convex)�𓊉e���čő�ƍŏ���Ԃ�
void projection(Vec2 axis , Box* box, float* min , float* max) {
	float min_ = INF;
	float max_ = -INF;
	//�S�Ă̒��_�𓊉e
	for (int i = 0; i < box->getPointNum(); i++) {
		float dot;
		dot = axis.dot(box->getPointW(i));
		min_ = min(min_ , dot);
		max_ = max(max_, dot);
	}
	*min = min_;
	*max = max_;
}

//axis��box(convex)�𓊉e���čő�ƍŏ���Ԃ�
void projection(Vec2 axis, Convex* con, float* min, float* max) {
	float min_ = INF;
	float max_ = -INF;
	//�S�Ă̒��_�𓊉e
	for (int i = 0; i < con->getPointNum(); i++) {
		float dot;
		dot = axis.dot(con->getPointW(i));
		min_ = min(min_, dot);
		max_ = max(max_, dot);
	}
	*min = min_;
	*max = max_;
}

//�����e�̌��ʁA�����������邩���肷��@�������Ă��Ȃ�(d>0)�̎���true
bool getDepth(const float min1 , const float max1 ,const float min2 , const float max2  , float* d1 , float* d2) {
	//�ђʐ[�x�����߂āA�����Ŕ��肷��
	*d1 = min1 - max2;
	*d2 = min2 - max1;
	if (*d1  > 0 || *d2 > 0) {
		return true;
	}
	return false;
}

Vec2 getContactPoint(const Vec2& point , const Segment& edge) {
	//�Ӄx�N�g���̐��K��
	Vec2 edgeVec =(edge.end - edge.start).normalize();
	Vec2 StoP = point - edge.start;
	//�n�_����̋��������߂�
	float dis = StoP.dot(edgeVec);
	return edge.start + (edgeVec * dis);
}


bool isCross(const BBox& b1, const BBox& b2) {
	//x���𒲂ׂ�
	if (b1.point.x + b1.width <= b2.point.x || b2.point.x + b2.width <= b1.point.x) {
		return false;
	}
	//y���𒲂ׂ�
	if (b1.point.y + b1.height <= b2.point.y || b2.point.y + b2.height <= b1.point.y) {
		return false;
	}
	return true;
}