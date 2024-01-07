#include "Game.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

static const int window_x1 = 20;
static const int window_y1 = 20;
static const int window_x2 = 400;
static const int window_y2 = 580;


Game::Game(SceneChanger *changer) 
	:BaseScene(changer)
{}

Game::~Game() 
{}

void Game::Initialize() {
	//�摜�E�����̃��[�h
	backPic = LoadGraph("pic/Game/Back.png");
	bgm = LoadSoundMem("snd/Game/bgm.mp3");
	windowPic = LoadGraph("pic/Game/Window.png");

	//BGM���Đ�
	PlaySoundMem(bgm, DX_PLAYTYPE_BACK, true);
}

//�~�̕��i�^��
void Game::Update() {
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

void Game::Draw() {
	//�`�惂�[�h
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//�w�i�̕`��
	DrawExtendGraph(0, 0, WIN_SIZE_X, WIN_SIZE_Y, backPic, true);
	//�Q�[���E�B���h�E�̕`��

}

void Game::Finalize() {
	//BGM�̒�~
	StopSoundMem(bgm);
	//�摜�폜
	deleteMem();
}

//�摜�A�����̃��������
void Game::deleteMem() {
	DeleteSoundMem(bgm);
	DeleteGraph(backPic);
}