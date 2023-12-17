#include "DetectTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

DetectTest::DetectTest(SceneChanger* changer)
	:BaseScene(changer)
{}

DetectTest::~DetectTest()
{}

void DetectTest::Initialize() {
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

//円の並進運動
void DetectTest::Update() {
	//入力状態の取得
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	//停止用
	static bool stop;
	if (KeyBoard::instance()->hitNow(KEY_INPUT_S)) {
		stop = !stop;
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_C)) {
		m_sceneChanger->ChangeScene(Scene_Game);
	}

	//シミュレーション
	if (!stop) {
		Rand* rand = Rand::instance();
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			world.add(new Circle(rand->get(100, 700), 500, rand->get(10, 80), rand->get(-20, 20), rand->get(-20, 20)));
		}
		else if (Mouse::instance()->getClickNow(RIGHT_CLICK)) {
			world.add(new Box(rand->get(100, 700), 500, rand->get(40, 200), rand->get(40, 200), 0, 0, 0, 0 ));
		}
		world.physicsSimulate();
	}
}

void DetectTest::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "DetectTest", COLOR_BLACK);
	//printfDx("DrawSize:%d\n" , world.objects.size());
	for (Object* obj : world.objects) {
		obj->Draw();
	}
	for (Collision col : world.collisions) {
		col.Draw();
	}

	//LtoWテスト用
	Vec2 testPoint = Vec2(-200 , -100);
	Vec2 testCenter = Vec2(400 , 300);
	DrawCircle(testPoint.x, WIN_SIZE_Y - testPoint.y , 4, COLOR_GREEN);
	Vec2 rotaed = LtoW(testPoint , testCenter , 0);
	DrawCircle(rotaed.x, WIN_SIZE_Y - rotaed.y, 4, COLOR_GREEN);
	DrawLine(testPoint.x, WIN_SIZE_Y - testPoint.y , rotaed.x, WIN_SIZE_Y - rotaed.y ,COLOR_GREEN , 3.f);
}

void DetectTest::Finalize() {
	for (Object* obj : world.objects) {
		delete obj;
	}
}

//画像、音声のメモリ解放
void DetectTest::deleteMem() {
}