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
	//画像・音声のロード
	backPic = LoadGraph("pic/Game/Back.png");
	bgm = LoadSoundMem("snd/Game/bgm.mp3");
	windowPic = LoadGraph("pic/Game/Window.png");

	//BGMを再生
	PlaySoundMem(bgm, DX_PLAYTYPE_BACK, true);
}

//円の並進運動
void Game::Update() {
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

void Game::Draw() {
	//描画モード
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//背景の描画
	DrawExtendGraph(0, 0, WIN_SIZE_X, WIN_SIZE_Y, backPic, true);
	//ゲームウィンドウの描画

}

void Game::Finalize() {
	//BGMの停止
	StopSoundMem(bgm);
	//画像削除
	deleteMem();
}

//画像、音声のメモリ解放
void Game::deleteMem() {
	DeleteSoundMem(bgm);
	DeleteGraph(backPic);
}