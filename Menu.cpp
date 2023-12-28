#include "Menu.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

Menu::Menu(SceneChanger* changer)
	:BaseScene(changer)
{}

Menu::~Menu()
{}

void Menu::Initialize() {
}

//円の並進運動
void Menu::Update() {
	//入力状態の取得
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	if (KeyBoard::instance()->hitNow(KEY_INPUT_RIGHT)) {
		m_sceneChanger->ChangeScene(Scene_Game);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_LEFT)) {
		m_sceneChanger->ChangeScene(Scene_TEST_Constraint);
	}
}

void Menu::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "Scene Menu", COLOR_BLACK);
}

void Menu::Finalize() {
}

//画像、音声のメモリ解放
void Menu::deleteMem() {
}