#include "MathTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

static Segment line;
static Vec2 point;
static bool start = true;

MathTest::MathTest(SceneChanger* changer)
	:BaseScene(changer)
{}

MathTest::~MathTest()
{}

void MathTest::Initialize() {
	//画像の読み込み
	Box::loadGraph();
	//初期化
	world.initialize();
	//床の作成
	Box* wall_under = new Box(400, 25, 50, 800, 0, 0, 0, 0, false);
	world.add(wall_under);
	//長方形の配置
	Box* box1 = new Box(400, 500, 60, 70);
	world.add(box1);
	box1 = new Box(300, 300, 200, 100, 0, 0, 0, 0, false);
	world.add(box1);
}

void MathTest::Update() {
	//入力状態の取得
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	//停止用
	static bool stop;
	if (KeyBoard::instance()->hitNow(KEY_INPUT_S)) {
		line.start = Vec2();
		line.end = Vec2();
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_C)) {
		m_sceneChanger->ChangeScene(Scene_Game);
	}

	if (!stop) {
		Rand* rand = Rand::instance();
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
		world.physicsSimulate();
	}
}

void MathTest::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "MathTest", COLOR_BLACK);
	
	DrawSegment(line , COLOR_BLUE);
	DrawPoint(point , COLOR_RED);
}

void MathTest::Finalize() {
	for (Object* obj : world.objects) {
		delete obj;
	}
}

//画像、音声のメモリ解放
void MathTest::deleteMem() {
}