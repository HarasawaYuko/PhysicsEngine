#include "DetectTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "detect.h"
#include "Convex.h"

//衝突検知テスト
static int mode = 0;

//Convex vs Convex mode =  0
static std::vector<Convex> convexes;
static std::vector<Vec2> points;
static std::vector<Collision> collisions;

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
			collisions.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN) && points.size() >= 3) {
			convexes.emplace_back(points);
			convexes.back().setColor(GetColor(rand->get(0,255), rand->get(0, 255), rand->get(0, 255)));
			points.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_D)) {
			for (int i = 0; i < convexes.size(); i++) {
				for (int j = i + 1; j < convexes.size(); j++) {
					float d;
					Vec2 n;
					Vec2 coord[2];
					if (Detect::convex_convex(&convexes[i], &convexes[j], &d, &n, coord)) {
						ContactPoint cp = ContactPoint(d, coord[0], coord[1], n);
						Collision col = Collision(&convexes[i], &convexes[j]);
						col.addContactPoint(cp);
						collisions.push_back(col);
					}
				}
			}
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
		DrawString(0 , 25 , "凸包と凸包の衝突\nLeftClick->point追加 L->pointClear A->all clear enter->make \nConvex D->detect\n" , COLOR_BLACK);
		//凸包の描画
		for (auto con : convexes) {
			con.Draw(con.getColor());
		}
		//pointの描画
		for (auto p : points) {
			DrawPoint(p, COLOR_RED);
		}
		//衝突の描画
		if (collisions.size() > 0) {
			DrawString(0 , 100 , "Detect!" ,COLOR_RED);
		}
		for (auto col : collisions) {
			ContactPoint cp = col.contactPoints[0];
			DrawFormatString(300, 150, COLOR_BLACK, "貫通深度:%f", cp.depth);
			Vec2 pA = LtoW(cp.pointA , col.getObj1()->getC() , 0);
			Vec2 pB = LtoW(cp.pointB , col.getObj2()->getC() , 0);
			DrawPoint(pA, COLOR_YELLOW);
			DrawPoint(pB, COLOR_YELLOW);
			Vec2 n = cp.normal * cp.depth;
			printfDx("%f\n", n.norm());
			n = n + pA;
			DrawSegment(Segment(pA  , n)  , COLOR_RED);
			DrawSegment(Segment(Vec2(), cp.normal * cp.depth), COLOR_BLACK);
		}
		break;
	}
}

void DetectTest::Finalize() {
}

//画像、音声のメモリ解放
void DetectTest::deleteMem() {
}