#include "DetectTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "Convex.h"

//衝突検知テスト
static int mode = 0;

//Convex vs Convex mode =  0
static std::vector<Convex> convexes;
static std::vector<Vec2> points;

DetectTest::DetectTest(SceneChanger* changer)
	:BaseScene(changer)
{}

DetectTest::~DetectTest()
{}

void DetectTest::Initialize() {
}

void DetectTest::Update() {
	//入力状態の取得
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	if (KeyBoard::instance()->hitNow(KEY_INPUT_P)) {
		mode++;
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_M)) {
		mode--;
	}

	switch (mode) {
	case 0:
		Rand * rand = Rand::instance();
		//凸包の作成
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			points.emplace_back(Mouse::instance()->getX(), Mouse::instance()->getY());
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_L)) {
			points.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_A)) {
			points.clear();
			convexes.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN) && points.size() >= 3) {
			convexes.emplace_back(points);
			convexes.back().setColor(GetColor(rand->get(0,255), rand->get(0, 255), rand->get(0, 255)));
			points.clear();
		}
		break;
	}
}

void DetectTest::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "DetectTest", COLOR_BLACK);
	switch (mode) {
	case 0:
		Rand * rand = Rand::instance();
		DrawString(0 , 25 , "凸包と凸包の衝突\nLeftClick->point追加 L->pointClear A->all clear enter->make Convex\n" , COLOR_BLACK);
		for (auto con : convexes) {
			con.Draw(con.getColor());
		}
		for (auto p : points) {
			DrawPoint(p, COLOR_RED);
		}
		break;
	}
}

void DetectTest::Finalize() {
}

//画像、音声のメモリ解放
void DetectTest::deleteMem() {
}