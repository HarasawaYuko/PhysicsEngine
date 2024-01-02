#include "Result.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

Result::Result(SceneChanger* changer)
	:BaseScene(changer)
{}

Result::~Result()
{}

void Result::Initialize() {
}

//円の並進運動
void Result::Update() {
	//入力状態の取得
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	if (KeyBoard::instance()->hitNow(KEY_INPUT_RIGHT)) {
		m_sceneChanger->ChangeScene(Scene_Game);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_LEFT)) {
		m_sceneChanger->ChangeScene(Scene_Game);
	}
}

void Result::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "Scene Result", COLOR_BLACK);
}

void Result::Finalize() {
	for (Object* obj : world.objects) {
		delete obj;
	}
}

//画像、音声のメモリ解放
void Result::deleteMem() {
}