#include "DetectTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "detect.h"
#include "Convex.h"
#include "DEBUG.h"

//Õ“ËŒŸ’mƒeƒXƒg
static int mode = 0;

//Convex vs Convex mode =  0
static std::vector<Convex> convexes;
static std::vector<Vec2> points;
static std::vector<Collision> collisions;
static Vec2 contactP[2];

DetectTest::DetectTest(SceneChanger* changer)
	:BaseScene(changer)
{}

DetectTest::~DetectTest()
{}

void DetectTest::Initialize() {
}

void DetectTest::Update() {
	//“ü—Íó‘Ô‚Ìæ“¾
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
		//“Ê•ï‚Ìì¬
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
						contactP[0] = LtoW(cp.pointA, convexes[0].getC(), convexes[0].getAngle());
						contactP[1] = LtoW(cp.pointB, convexes[1].getC(), convexes[1].getAngle());
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
	switch (mode) {
	case 0:
		Rand * rand = Rand::instance();
		DrawString(0 , 25 , "“Ê•ï‚Æ“Ê•ï‚ÌÕ“Ë\nLeftClick->point’Ç‰Á L->pointClear A->all clear enter->make \nConvex D->detect\n" , COLOR_BLACK);
		//“Ê•ï‚Ì•`‰æ
		int i = 0;
		for (auto con : convexes) {
			con.Draw(con.getColor());
			for (int j = 0; j < con.getPointNum(); j++) {
				DrawPoint(con.getPointW(j) , COLOR_ORANGE);
			}
			DrawStrP(con.getC() , std::to_string(i), COLOR_BLUE);
			i++;
		}
		//point‚Ì•`‰æ
		for (auto p : points) {
			DrawPoint(p, COLOR_RED);
		}
		//Õ“Ë‚Ì•`‰æ
		if (collisions.size() > 0) {
			DrawString(0 , 100 , "Detect!" ,COLOR_RED);
		}
		for (auto col : collisions) {
			ContactPoint cp = col.contactPoints[0];
			DrawFormatString(300, 150, COLOR_BLACK, "ŠÑ’Ê[“x:%f", cp.depth);
			Vec2 pA = LtoW(cp.pointA , col.getObj1()->getC() , 0);
			Vec2 pB = LtoW(cp.pointB , col.getObj2()->getC() , 0);
			DrawPoint(pA, COLOR_YELLOW);
			SetFontSize(18);
			DrawStrP(pA,"A" , COLOR_YELLOW);
			DrawPoint(pB, COLOR_YELLOW);
			DrawStrP(pB, "B" , COLOR_YELLOW);
			SetFontSize(20);
			Vec2 n = cp.normal * cp.depth;
			n = n + pB;
			DrawSegment(Segment(n  , pB)  , COLOR_RED);
			DrawString(20 , 400 , contactP[0].toString().c_str(), COLOR_RED);
			DrawString(20, 430, contactP[1].toString().c_str(), COLOR_RED);
		}
		//‚»‚Ì‘¼•`‰æ
		break;
	}
}

void DetectTest::Finalize() {
}

//‰æ‘œA‰¹º‚Ìƒƒ‚ƒŠ‰ğ•ú
void DetectTest::deleteMem() {
}