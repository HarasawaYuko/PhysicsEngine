#pragma once

#include "Object.h"
#include "UIMaterial.h"

//�����`�N���X
class Box :public Object {
private:
	std::vector<Vec2> pointsL;//���[�J�����W�ł̈ʒu(���ォ�玞�v����)
	std::vector<Vec2> pointsW;//���[���h���W�ł̈ʒu
	float height;//����
	float width;//��
	static int fig;
	static int figX;
	static int figY;
	static int fig2;
	int pointNum;


public:
	Box(const float cen_x, const float cen_y, const float h  , const float w , const float v_x = 0, const float v_y = 0,const float ang = 0 , const float ang_v = 0 , const bool act = true);
	static void loadGraph();
	void updatePos(const float step)override;
	void Draw()const override;
	bool isValid()const override;
	std::string toString()const override;
	Vec2 getPointW(const int)const;
	int getPointNum()const;
	void move(Vec2);
	Segment getEdgeW(const int&)const;
};