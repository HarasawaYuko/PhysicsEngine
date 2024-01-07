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

//�~�̕��i�^��
void Setting::Update() {
	//���͏�Ԃ̎擾
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

//�摜�A�����̃��������
void Setting::deleteMem() {
}