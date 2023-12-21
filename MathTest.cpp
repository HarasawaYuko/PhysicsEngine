#include "MathTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "Convex.h"

//���l�v�Z���e�X�g�p
static int mode = 0;

//�_�ƒ����̋���
static Segment line;
static Vec2 point;
static Vec2 contactPoint;
static bool start = true;
static float dis;
static int  pattern;

//�Ȃ��p
static bool p0set = true;
static Vec2 center =Vec2(400 ,300);
static Vec2 p0;
static Vec2 p1;
static float theta;

//Convex�R���X�g���N�^
static std::vector<Vec2> points;
static Convex* convex;
static bool make =  false;

MathTest::MathTest(SceneChanger* changer)
	:BaseScene(changer)
{}

MathTest::~MathTest()
{}

void MathTest::Initialize() {
	//�摜�̓ǂݍ���
	Box::loadGraph();
}

void MathTest::Update() {
	//���͏�Ԃ̎擾
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	if (KeyBoard::instance()->hitNow(KEY_INPUT_S)) {
		line.start = Vec2();
		line.end = Vec2();
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_C)) {
		m_sceneChanger->ChangeScene(Scene_TEST_Detect);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_P)) {
		mode++;
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_M)) {
		mode--;
	}

	switch (mode) {
	case 0:
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			if (start) {
				line.start.set(Mouse::instance()->getX(), Mouse::instance()->getY());
			}
			else {
				line.end.set(Mouse::instance()->getX(), Mouse::instance()->getY());
			}
			start = !start;
		}
		else if (Mouse::instance()->getClickNow(RIGHT_CLICK)) {
			point.set(Mouse::instance()->getX(), Mouse::instance()->getY());
		}
		{
			if (KeyBoard::instance()->hitNow(KEY_INPUT_D)) {
				dis = getDistance(point, line, &pattern);
				Vec2 edgeVec = (line.end - line.start).normalize();
				Vec2 StoP = point - line.start;
				//�n�_����̋��������߂�
				float dis_ = StoP.dot(edgeVec);
				contactPoint = line.start + (edgeVec * dis_);
			}
		}
		break;
		//�Ȃ��p
	case 1:
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			
			p0.set(Mouse::instance()->getX(), Mouse::instance()->getY());
		}
		else if (Mouse::instance()->getClickNow(RIGHT_CLICK)) {
			p1.set(Mouse::instance()->getX(), Mouse::instance()->getY());
		}
		theta = getDegree(getTheta(center , p0 , p1));
		break;
	case 2:
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			points.emplace_back(Mouse::instance()->getX(), Mouse::instance()->getY());
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_L)) {
			delete convex;
			make = false;
			points.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN)) {
			convex = new Convex(points);
			make = true;
		}
	}
}

void MathTest::Draw() {
	SetFontSize(20);
	DrawFormatString(640, 0, COLOR_BLACK, "MathTest %d",mode );
	DrawString(640, 23, "S->Reset" , COLOR_BLACK);

	switch (mode) {
	case 0:
		DrawString(0, 23, "�_�ƒ����̋���", COLOR_BLACK);
		DrawSegment(line, COLOR_BLUE);
		DrawPoint(point, COLOR_RED);
		DrawPoint(contactPoint, COLOR_GREEN);
		SetFontSize(30);
		DrawFormatString(0, 300 , COLOR_RED , "����:%f" , dis);
		DrawFormatString(0, 330, COLOR_RED, "�p�^�[��:%d", pattern);
		SetFontSize(20);
		break;
	case 1:
		DrawString(0 , 23 , "rightClick->�� leftClick->��", COLOR_BLACK);
		DrawString(0, 50, "�Ȃ��p ����΂܂Ŕ����v����\n", COLOR_BLACK);
		DrawPoint(center , COLOR_RED);
		DrawSegment(Segment(center , p0) ,  COLOR_BLUE);
		DrawSegment(Segment(center , p1) , COLOR_GREEN);
		SetFontSize(40);
		DrawFormatString(0 , 70 ,COLOR_BLACK,"Theta = %f" ,theta );
		break;
	case 2:
		DrawString(0, 23, "leftClick->�_�̒ǉ� L->�N���A Enter->Convex�쐬", COLOR_BLACK);
		DrawString(0, 50, "Convex�R���X�g���N�^\n", COLOR_BLACK);
		for (int i = 0; i < points.size(); i++) {
			DrawPoint(points[i] , COLOR_RED);
		}
		if (make) {
			convex->Draw();
			DrawPoint(convex->getC() , COLOR_ORANGE);
			for (int i = 0; i < convex->getPointNum(); i++) {
				Vec2 p = convex->getPointW(i);
				DrawFormatString(p.x, WIN_SIZE_Y - p.y, COLOR_BLUE, "%d", i);
			}
		}
		break;
	}


}

void MathTest::Finalize() {
	for (Object* obj : world.objects) {
		delete obj;
	}
}

//�摜�A�����̃��������
void MathTest::deleteMem() {
}