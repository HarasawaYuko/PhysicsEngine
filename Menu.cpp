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

//‰~‚Ì•Ài‰^“®
void Menu::Update() {
	//“ü—Íó‘Ô‚Ìæ“¾
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

//‰æ‘œA‰¹º‚Ìƒƒ‚ƒŠ‰ğ•ú
void Menu::deleteMem() {
}