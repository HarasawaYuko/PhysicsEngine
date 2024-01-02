#include "DetectTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "detect.h"
#include "Convex.h"
#include "DEBUG.h"

//ÕËmeXg
static int mode = 0;

//mode =  0 Åè¨Ì¯mÌÕË»è
static std::vector<Object*> objects;
static std::vector<Vec2> points;
static std::vector<Collision> collisions;
static Vec2 contactP[2];
static float r;
static Vec2 cirCenter;
static bool makeCon = true;

//Convex vs Convex mode = 1 ®­¨Ì¯m
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
	//üÍóÔÌæ¾
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
		//ì¬}`ÌÏX(Switch)
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
		//ÊïÌì¬
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
		//~ì¬
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
		DrawString(0 , 0 , "ÊïÆÊïÌÕË\n" , COLOR_BLACK);
		SetFontSize(20);
		DrawString(0, 30, "LeftClick->pointÇÁ L->pointClear A->all clear enter->make \nConvex D->detect\n", COLOR_BLACK);
		//}`Ì`æ
		for (auto obj : objects) {
			obj->DrawEdge();
		}
		//pointÌ`æ
		for (auto p : points) {
			DrawPoint(p, COLOR_RED);
		}
		//ÕËÌ`æ
		if (collisions.size() > 0) {
			DrawString(0 , 100 , "Detect!" ,COLOR_RED);
			Collision col = collisions[0];
			//ÕË_ðæ¾
			ContactPoint cp = col.getCp(0);
			//ÑÊ[xð`æ
			DrawFormatString(300, 150, COLOR_BLACK, "ÑÊ[x:%f", cp.depth);
			//ÕË_ðæ¾
			Vec2 pA = LtoW(cp.pointA , col.getObj1()->getC() , 0);
			Vec2 pB = LtoW(cp.pointB , col.getObj2()->getC() , 0);
			//ÕË_ð`æ
			DrawPoint(pA, COLOR_YELLOW);
			SetFontSize(18);
			DrawStrP(pA,"A" , COLOR_YELLOW);
			DrawPoint(pB, COLOR_YELLOW);
			DrawStrP(pB, "B" , COLOR_YELLOW);
			//@üxNgÌ`æ
			SetFontSize(20);
			Vec2 n = cp.normal * cp.depth;
			n = n + pB;
			DrawSegment(Segment(n  , pB)  , COLOR_RED);
		}
		break;
	}
}

void DetectTest::Finalize() {
	//Ìð@
}