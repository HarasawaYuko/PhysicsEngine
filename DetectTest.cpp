#include "DetectTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "detect.h"
#include "Convex.h"
#include "DEBUG.h"

//衝突検知テスト
static int mode = 0;

//mode =  0 固定物体同士の衝突判定
static std::vector<Object*> objects;
static std::vector<Vec2> points;
static std::vector<Collision> collisions;
static Vec2 contactP[2];
static float r;
static Vec2 cirCenter;
static bool makeCon = true;

//Convex vs Convex mode = 1 動く物体同士
static bool move = false;
static bool detect = false;
static Vec2 gravity = Vec2(0.f, -5.f);

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
		/*mode++;
		points.clear();*/
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_M)) {
		/*mode--;
		points.clear();*/
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_LEFT)) {
		m_sceneChanger->ChangeScene(Scene_TEST_Object);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_RIGHT)) {
		m_sceneChanger->ChangeScene(Scene_TEST_Math);
	}
	Rand* rand = Rand::instance();
	switch (mode) {
	case 0:
		//作成図形の変更(Switch)
		if (KeyBoard::instance()->hitNow(KEY_INPUT_S)) {
			makeCon = !makeCon;
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_L)) {
			points.clear();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_A)) {
			cirCenter = Vec2();
			r = 0.f;
			points.clear();
			objects.clear();
			collisions.clear();
		}
		//凸包の作成
		if (makeCon) {
			if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
				points.emplace_back(Mouse::instance()->getX(), Mouse::instance()->getY());
			}
			if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN) && points.size() >= 3) {
				Object* obj = (Object*)(new Convex(points));
				objects.emplace_back();
				objects.back()->setColor(GetColor(rand->get(0, 255), rand->get(0, 255), rand->get(0, 255)));
				points.clear();
			}
		}
		//円作成
		else {
			if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
				cirCenter = Vec2(Mouse::instance()->getX(), Mouse::instance()->getY());
			}
			if (Mouse::instance()->getClickNow(RIGHT_CLICK)) {
				r = cirCenter.distance(Vec2(Mouse::instance()->getX(), Mouse::instance()->getY()));
			}
			if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN) && points.size() >= 3) {
				objects.emplace_back();
				objects.back()->setColor(GetColor(rand->get(0, 255), rand->get(0, 255), rand->get(0, 255)));
				points.clear();
			}
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_D)) {
			for (int i = 0; i < objects.size(); i++) {
				for (int j = i + 1; j < objects.size(); j++) {
					float d;
					Vec2 n;
					Vec2 coord[2];
					Vec2 coord_[2];
					if (Detect::convex_convex(objects[i], objects[j], &d, &n, coord, coord_)) {
						ContactPoint cp;
						cp.depth = d;
						cp.pointA = coord[0];
						cp.pointB = coord[1];
						cp.pointA_ = coord_[0];
						cp.pointB_ = coord_[1];
						cp.normal = n;
						Collision col = Collision(objects[i], objects[j]);
						col.addCp(cp);
						contactP[0] = LtoW(cp.pointA, objects[0]->getC(), objects[0]->getAngle());
						contactP[1] = LtoW(cp.pointB, objects[1]->getC(), objects[1]->getAngle());
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
	DrawSegment(Segment(Vec2(0 , 300 ),Vec2(800 , 300)),COLOR_BLACK);
	DrawSegment(Segment(Vec2(400, 0), Vec2(400, 600)), COLOR_BLACK);
	Rand* rand = Rand::instance();
	int i = 0;
	switch (mode) {
	case 0:
		SetFontSize(30);
		DrawString(0 , 0 , "凸包と凸包の衝突\n" , COLOR_BLACK);
		SetFontSize(20);
		DrawString(0, 30, "LeftClick->point追加 L->pointClear A->all clear enter->make \nConvex D->detect\n", COLOR_BLACK);
		//図形の描画
		for (auto obj : objects) {
			obj->DrawEdge();
		}
		//pointの描画
		for (auto p : points) {
			DrawPoint(p, COLOR_RED);
		}
		//衝突の描画
		if (collisions.size() > 0) {
			DrawString(0 , 100 , "Detect!" ,COLOR_RED);
			Collision col = collisions[0];
			//衝突点を取得
			ContactPoint cp = col.getCp(0);
			//貫通深度を描画
			DrawFormatString(300, 150, COLOR_BLACK, "貫通深度:%f", cp.depth);
			//衝突点を取得
			Vec2 pA = LtoW(cp.pointA , col.getObj1()->getC() , 0);
			Vec2 pB = LtoW(cp.pointB , col.getObj2()->getC() , 0);
			//衝突点を描画
			DrawPoint(pA, COLOR_YELLOW);
			SetFontSize(18);
			DrawStrP(pA,"A" , COLOR_YELLOW);
			DrawPoint(pB, COLOR_YELLOW);
			DrawStrP(pB, "B" , COLOR_YELLOW);
			//法線ベクトルの描画
			SetFontSize(20);
			Vec2 n = cp.normal * cp.depth;
			n = n + pB;
			DrawSegment(Segment(n  , pB)  , COLOR_RED);
		}
		break;
	}
}

void DetectTest::Finalize() {
	//メモリの解法
}