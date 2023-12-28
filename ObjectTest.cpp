#include "ObjectTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "detect.h"
#include "Convex.h"
#include "DEBUG.h"

//}`eXg
static int mode = 0;

//ΚοeXg mode = 0
static std::vector<Vec2> points;
static Convex* convex;
static bool make = false;

//Κορ]
static bool rotation = false;
static Vec2 vel;
static float angV = Pi/2;
static float dot;

ObjectTest::ObjectTest(SceneChanger* changer)
	:BaseScene(changer)
{}

ObjectTest::~ObjectTest()
{}

void ObjectTest::Initialize() {
}

void ObjectTest::Update() {
	//όΝσΤΜζΎ
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	if (KeyBoard::instance()->hitNow(KEY_INPUT_P)) {
		mode++;
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_M)) {
		mode--;
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_LEFT)) {
		m_sceneChanger->ChangeScene(Scene_TEST_REC);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_RIGHT)) {
		m_sceneChanger->ChangeScene(Scene_TEST_Detect);
	}

	Rand* rand = Rand::instance();
	switch (mode) {
	case 0:
		//ΚοΜμ¬
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			points.emplace_back(Mouse::instance()->getX(), Mouse::instance()->getY());
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_L)) {
			points.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_A)) {
			delete convex;
			make = false;
			points.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN) && points.size() >= 3) {
			delete convex;
			convex = new Convex(points);
			convex->setColor(GetColor(rand->get(0, 255), rand->get(0, 255), rand->get(0, 255)));
			points.clear();
			make = true;
		}
		break;
	case 1:
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			points.emplace_back(Mouse::instance()->getX(), Mouse::instance()->getY());
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_L)) {
			points.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_A)) {
			delete convex;
			make = false;
			rotation = false;
			points.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN) && points.size() >= 3) {
			delete convex;
			convex = new Convex(points,0,0,0,0,true);
			convex->setColor(GetColor(rand->get(0, 255), rand->get(0, 255), rand->get(0, 255)));
			points.clear();
			((Object*)convex)->setAngV(angV);
			make = true;
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_R)) {
			rotation = !rotation;
		}
		if (rotation) {
			convex->updatePos(0.1f);
			vel = convex->getCirV(convex->getPointL(0));
			dot = (convex->getPointW(0)-convex->getC()).dot(vel);
		}
		break;
	}
}

void ObjectTest::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "ObjectTest", COLOR_BLACK);
	DrawString(600 , 22 ,"P->modeπiίι M->modeπί·" , COLOR_BLACK);
	switch (mode) {
	case 0:
		DrawString(0, 0, "ΚοΖΚοΜΆ¬\nLeftClick->pointΗΑ L->pointClear A->all clear enter->make \nConvex D->detect\n", COLOR_BLACK);
		//point
		for (auto p : points) {
			DrawPoint(p , COLOR_RED);
		}
		//ΚοΜ`ζ
		if (make) {
			convex->Draw(convex->getColor());
			DrawFormatString(0, 80, COLOR_RED, "΅«e\:%f", convex->getI());
			DrawFormatString(0, 110, COLOR_RED, "ΏΚ:%f", convex->getM());
		}
		break;
	case 1:
		DrawString(0, 0, "ΚοΜρ]\nLeftClick->pointΗΑ L->pointClear A->all clear enter->make \nConvex R->ρ]\n", COLOR_BLACK);
		//point
		for (auto p : points) {
			DrawPoint(p, COLOR_RED);
		}
		//ΚοΜ`ζ
		if (make) {
			convex->Draw(convex->getColor());
			DrawFormatString(0, 80, COLOR_RED, "p¬x rad:%f fre:%f", convex->getAngV() , getDegree(convex->getAngV()));
			DrawFormatString(0, 110, COLOR_RED, "ΰΟ %f", dot);
			DrawFormatString(0, 140, COLOR_BLACK, "ε«³ %f", vel.norm());
			//printfDx("%f \n", convex->getPointL(0).toString().c_str());
			//printfDx("vel %s\n" , vel.toString().c_str());
			//¬xxNgΜ`ζ
			Segment vSeg = Segment(convex->getPointW(0) , (convex->getPointW(0)+vel));
			DrawSegment(vSeg, COLOR_RED);
			DrawSegment(Segment(convex->getC() , convex->getPointW(0)), COLOR_BLACK);
		}
		break;
	}

}

void ObjectTest::Finalize() {
}

//ζAΉΊΜπϊ
void ObjectTest::deleteMem() {
}