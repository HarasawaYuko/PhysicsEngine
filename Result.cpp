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

//‰~‚Ì•Ài‰^“®
void Result::Update() {
	//“ü—Íó‘Ô‚Ìæ“¾
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	if (KeyBoard::instance()->hitNow(KEY_INPUT_RIGHT)) {
		m_sceneChanger->ChangeScene(Scene_TEST_REC);
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

//‰æ‘œA‰¹º‚Ìƒƒ‚ƒŠ‰ğ•ú
void Result::deleteMem() {
}