#include "Setting.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

Setting::Setting(SceneChanger* changer)
	:BaseScene(changer)
{}

Setting::~Setting()
{}

void Setting::Initialize() {
}

//円の並進運動
void Setting::Update() {
	//入力状態の取得
	KeyBoard::instance()->update();
	Mouse::instance()->update();


	if (KeyBoard::instance()->hitNow(KEY_INPUT_LEFT)) {
		m_sceneChanger->ChangeScene(Scene_Menu);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_RIGHT)) {
		m_sceneChanger->ChangeScene(Scene_Result);
	}
}

void Setting::Draw() {
}

void Setting::Finalize() {
}

//画像、音声のメモリ解放
void Setting::deleteMem() {
}