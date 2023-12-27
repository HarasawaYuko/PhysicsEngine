#include "ConstraintTest.h"
#include "Solver.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "detect.h"
#include "Convex.h"
#include "DEBUG.h"

//�Փˌ��m�e�X�g
static int mode = 0;

//Convex vs Convex mode =  0
static std::vector<Object*> convexes;
static std::vector<Vec2> points;
static std::vector<Collision> collisions;
static Vec2 contactP[2];
static bool move = false;
static bool detect = false;
static Vec2 gravity = Vec2(0.f, -5.f);

ConstraintTest::ConstraintTest(SceneChanger* changer)
	:BaseScene(changer)
{}

ConstraintTest::~ConstraintTest()
{}

void ConstraintTest::Initialize() {
	//�O�p�`������O�ɍ쐬
	points.emplace_back(200.f , 400);
	points.emplace_back(200.f, 550);
	points.emplace_back(350.f, 400);
	Convex* con = new Convex(points , 0 , 0 , 30.f , 0 , true);
	con->setIndex(0);
	convexes.push_back(con);
	points.clear();
	/*
	points.emplace_back(350.f, 450);
	points.emplace_back(350.f, 550);
	points.emplace_back(450.f, 450);
	con = new Convex(points, -35, 0, 0, 0, true);
	con->setIndex(1);
	points.clear();
	convexes.push_back(con);*/

	points.emplace_back(100.f, 200);
	points.emplace_back(100.f, 250);
	points.emplace_back(600.f, 200);
	points.emplace_back(600.f, 250);
	con = new Convex(points, 0, 0, 0, 0, false);
	con->setIndex(1);
	convexes.push_back(con);
	points.clear();
}

void ConstraintTest::Update() {
	//���͏�Ԃ̎擾
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	if (KeyBoard::instance()->hitNow(KEY_INPUT_P)) {
		mode++;
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_M)) {
		mode--;
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_C)) {
		m_sceneChanger->ChangeScene(Scene_TEST_Math);
	}

	switch (mode) {
	case 0:
		Rand * rand = Rand::instance();
		//�ʕ�̍쐬
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			points.emplace_back(Mouse::instance()->getX(), Mouse::instance()->getY());
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_L)) {
			points.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_A)) {
			points.clear();
			convexes.clear();
			collisions.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN) && points.size() >= 3) {
			Convex* con = new Convex(points ,0,0,0,0,true);
			convexes.push_back((Object*)con);
			convexes.back()->setColor(GetColor(rand->get(0, 255), rand->get(0, 255), rand->get(0, 255)));
			points.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_G)) {
			move = !move;
		}
		if (move) {
			//�d�͂�������
			for (auto con: convexes) {
				con->addV(gravity);
			}
			//�Փ˔���
			float d;
			Vec2 n;
			Vec2 coord[2];
			detect = false;
			if (Detect::convex_convex(convexes[0], convexes[1], &d, &n, coord)) {
				detect = true;
				ContactPoint cp = ContactPoint(d, coord[0], coord[1], n);
				printfDx("contactPoint n %s\n" , n.toString().c_str());
				Collision col = Collision(convexes[0], convexes[1]);
				col.addContactPoint(cp);
				contactP[0] = LtoW(cp.pointA, convexes[0]->getC(), convexes[0]->getAngle());
				contactP[1] = LtoW(cp.pointB, convexes[1]->getC(), convexes[1]->getAngle());
				collisions.push_back(col);
			}
			
			//�S������
			if(detect)Solver::solve(convexes , collisions);

			collisions.clear();

			//�ʒu���X�V
			for (auto con : convexes) {
				con->updatePos(1/30.f);
			}

		}
		break;
	}
}

void ConstraintTest::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "ConstraintTest", COLOR_BLACK);
	switch (mode) {
	case 0:
		Rand * rand = Rand::instance();
		DrawString(0, 25, "�ʕ�Ɠʕ�̍S������\nLeftClick->point�ǉ� L->pointClear A->all clear enter->make \nConvex D->detect\n", COLOR_BLACK);
		//�ʕ�̕`��
		for (auto con : convexes) {
			((Convex*)con)->Draw(con->getColor());
		}
		//point�̕`��
		for (auto p : points) {
			DrawPoint(p, COLOR_RED);
		}
		if (detect) {
			DrawString(700 , 400 , "DETECT"  , COLOR_RED);
		}
		//���̑��`��

		break;
	}
}

void ConstraintTest::Finalize() {
}

//�摜�A�����̃��������
void ConstraintTest::deleteMem() {
}