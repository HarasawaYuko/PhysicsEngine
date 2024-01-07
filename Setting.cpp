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

//‰~‚Ì•Ài‰^“®
void Setting::Update() {
	//“ü—Íó‘Ô‚Ìæ“¾
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

//‰æ‘œA‰¹º‚Ìƒƒ‚ƒŠ‰ğ•ú
void Setting::deleteMem() {
}