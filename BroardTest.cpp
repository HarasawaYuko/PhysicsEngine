#include "BroardTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

BroardTest::BroardTest(SceneChanger* changer)
	:BaseScene(changer)
{}

BroardTest::~BroardTest()
{}

void BroardTest::Initialize() {
}

//円の並進運動
void BroardTest::Update() {
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
			world.add(new Box(rand->get(100, 700), 500, rand->get(40, 200), rand->get(40, 200), rand->get(-20, 20), 0, 0, rand->get(-5, 5) / 10));
		}
		world.physicsSimulate();
	}
}

void BroardTest::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "Scene Rec", COLOR_BLACK);
	//printfDx("DrawSize:%d\n" , world.objects.size());
	for (Object* obj : world.objects) {
		obj->Draw();
		if (obj->getType() == CIRCLE) {
			//printfDx("%f , %f \n", obj->getC().x, obj->getC().y);
		}
	}
}

void BroardTest::Finalize() {
	for (Object* obj : world.objects) {
		delete obj;
	}
}

//画像、音声のメモリ解放
void BroardTest::deleteMem() {
}