#pragma once

#include "Object.h"
#include "UIMaterial.h"

//�����`�N���X
class Box :public Object {
private:
	Vec2 pointsL[4];//���[�J�����W�ł̈ʒu(���ォ�玞�v����)
	Vec2 pointsW[4];//���[���h���W�ł̈ʒu
	float height;//����
	float width;//��
	static int fig;
	static int figX;
	static int figY;
	float angle_v;
	float angle;
	float inertiaTensor;//�����e���\��

public:
	Box(const float cen_x, const float cen_y, const float h  , const float w , const float v_x = 0, const float v_y = 0,const float ang = 0 , const float ang_v = 0);
	static void loadGraph();
	void updatePos(const float step)override;
	void Draw()const override;
	bool isValid()const override;
	std::string toString()const override;
};