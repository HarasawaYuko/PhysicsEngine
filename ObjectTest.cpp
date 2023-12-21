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
	if (KeyBoard::instance()->hitNow(KEY_INPUT_C)) {
		m_sceneChanger->ChangeScene(Scene_TEST_Math);
	}

	switch (mode) {
	case 0:
		Rand * rand = Rand::instance();
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
	}
}

void ObjectTest::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "ObjectTest", COLOR_BLACK);
	switch (mode) {
	case 0:
		Rand * rand = Rand::instance();
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
	}
}

void ObjectTest::Finalize() {
}

//ζAΉΊΜπϊ
void ObjectTest::deleteMem() {
}