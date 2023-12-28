#include "DetectTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "detect.h"
#include "Convex.h"
#include "DEBUG.h"

//Õ“ËŒŸ’mƒeƒXƒg
static int mode = 0;

//Convex vs Convex mode =  0 ŒÅ’è•¨‘Ì“¯m
static std::vector<Convex> convexes;
static std::vector<Vec2> points;
static std::vector<Collision> collisions;
static Vec2 nVec;
static Vec2 contactP[2];

//Convex vs Convex mode = 1 “®‚­•¨‘Ì“¯m
void setObj();
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
	//“ü—Íó‘Ô‚Ìæ“¾
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	if (KeyBoard::instance()->hitNow(KEY_INPUT_P)) {
		mode++;
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_M)) {
		mode--;
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
						nVec = n;
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
	case 1:
		
		if (KeyBoard::instance()->hitNow(KEY_INPUT_S)) {
			setObj();
		}
		if (KeyBoard::instance()->hitNow(KEY_INPUT_G)) {
			move = !move;
		}
		if (move) {
			//printfDx("move\n");
			//d—Í‚ğ‰Á‚¦‚é
			for (auto& con : convexes) {
				con.addV(gravity);
				//printfDx("V %s\n" , con.getV().toString().c_str());
			}
			//printfDx("V %s\n", convexes[0].getV().toString().c_str());
			//Õ“Ë”»’è
			float d;
			Vec2 n;
			Vec2 coord[2];
			detect = false;
			if (Detect::convex_convex(&convexes[0], &convexes[1], &d, &n, coord)) {
				detect = true;
				nVec = n;
				ContactPoint cp = ContactPoint(d, coord[0], coord[1], n);
				//printfDx("contactPoint n %s\n", n.toString().c_str());
				Collision col = Collision(&convexes[0], &convexes[1]);
				col.addContactPoint(cp);
				contactP[0] = LtoW(cp.pointA, convexes[0].getC(), convexes[0].getAngle());
				contactP[1] = LtoW(cp.pointB, convexes[1].getC(), convexes[1].getAngle());
				collisions.push_back(col);
			}

			//S‘©‰ğÁ
			if (detect) {
				move = false;
			}

			collisions.clear();

			//ˆÊ’u‚ğXV
			for (auto& con : convexes) {
				//printfDx("V2 %s\n", con.getV().toString().c_str());
				con.updatePos(1 / 30.f);
				//printfDx("updatePos %s | %s\n" , con.getC().toString().c_str() , con.getV().toString().c_str());
			}
		}
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
		DrawString(0 , 25 , "“Ê•ï‚Æ“Ê•ï‚ÌÕ“Ë\nLeftClick->point’Ç‰Á L->pointClear A->all clear enter->make \nConvex D->detect\n" , COLOR_BLACK);
		//“Ê•ï‚Ì•`‰æ
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
		DrawFormatString(10 , 550 , COLOR_BLUE , "n:%s" , nVec.toString().c_str());
		break;
	case 1:
		DrawString(0, 25, "“Ê•ï‚Æ“Ê•ï‚ÌÕ“Ë(‰Â“®)\nLeftClick->point’Ç‰Á L->pointClear A->all clear enter->make \nConvex D->detect\n", COLOR_BLACK);
		//“Ê•ï‚Ì•`‰æ
		for (auto con : convexes) {
			con.Draw(con.getColor());
		}
		//point‚Ì•`‰æ
		for (auto p : points) {
			DrawPoint(p, COLOR_RED);
		}
		//Õ“Ë‚Ì•`‰æ
		if (collisions.size() > 0) {
			DrawString(0, 100, "Detect!", COLOR_RED);
		}
		for (auto col : collisions) {
			ContactPoint cp = col.contactPoints[0];
			DrawFormatString(300, 150, COLOR_BLACK, "ŠÑ’Ê[“x:%f", cp.depth);
			Vec2 pA = LtoW(cp.pointA, col.getObj1()->getC(), 0);
			Vec2 pB = LtoW(cp.pointB, col.getObj2()->getC(), 0);
			DrawPoint(pA, COLOR_YELLOW);
			SetFontSize(18);
			DrawStrP(pA, "A", COLOR_YELLOW);
			DrawPoint(pB, COLOR_YELLOW);
			DrawStrP(pB, "B", COLOR_YELLOW);
			SetFontSize(20);
			Vec2 n = cp.normal * cp.depth;
			n = n + pB;
			DrawSegment(Segment(n, pB), COLOR_RED);
			DrawString(20, 400, contactP[0].toString().c_str(), COLOR_RED);
			DrawString(20, 430, contactP[1].toString().c_str(), COLOR_RED);
		}
		//‚»‚Ì‘¼•`‰æ
		DrawFormatString(10, 550, COLOR_BLUE, "n:%s", nVec.toString().c_str());
		break;
	}
}

void DetectTest::Finalize() {
}

//‰æ‘œA‰¹º‚Ìƒƒ‚ƒŠ‰ğ•ú
void DetectTest::deleteMem() {
}

void setObj() {
	//OŠpŒ`“ñ‚Â‚ğ–‘O‚Éì¬
	points.emplace_back(200.f, 400);
	points.emplace_back(200.f, 550);
	points.emplace_back(350.f, 400);
	Convex con = Convex(points, 30, 0, 0, 30.f, true);
	con.setIndex(0);
	convexes.push_back(con);
	points.clear();

	//points.emplace_back(350.f, 450);
	//points.emplace_back(350.f, 550);
	//points.emplace_back(450.f, 450);
	//con = new Convex(points, -35, 0, 0, 30.f, true);
	//con->setIndex(1);
	//points.clear();
	//convexes.push_back(con);

	points.emplace_back(100.f, 300);
	points.emplace_back(100.f, 0);
	points.emplace_back(600.f, 300);
	points.emplace_back(600.f, 0);
	Convex con1 = Convex(points, 0, 0, 0, 0, false);
	con1.setIndex(1);
	convexes.push_back(con1);
	points.clear();
}