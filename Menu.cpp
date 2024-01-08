#include "Menu.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

//メニュー画面

//UIデザイン用定数
static const int ButtonWidth = 250;
static const int StartButtonY = 180;
static const int SetButtonY = 280;

Menu::Menu(SceneChanger* changer)
	:BaseScene(changer)
{}

Menu::~Menu()
{}

void Menu::Initialize() {
	//画像・音声のロード
	backPic = LoadGraph("pic/Menu/Back.png");
	bgm = LoadSoundMem("snd/Menu/bgm.mp3");
	int startPic = LoadGraph("pic/Menu/StartButton.png");
	int startPicOn = LoadGraph("pic/Menu/StartButtonOn.png");
	int startSnd = LoadSoundMem("snd/Menu/StartButton.mp3");
	int setPic = LoadGraph("pic/Menu/SettingButton.png");
	int setPicOn = LoadGraph("pic/Menu/SettingButtonOn.png");
	int setSnd = LoadSoundMem("snd/Menu/SettingButton.mp3");
	
	//BGMを再生
	PlaySoundMem(bgm , DX_PLAYTYPE_BACK, true);

	//ボタンの作成
	startButton = Button(startPic , startPicOn ,startSnd , StartButtonY , ButtonWidth );
	setButton = Button(setPic , setPicOn , setSnd ,SetButtonY , ButtonWidth);

}

void Menu::Update() {
	//入力状態の取得
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	//ボタンのupdate
	startButton.update();
	setButton.update();

	if (startButton.isPush()) {
		m_sceneChanger->ChangeScene(Scene_Game);
	}
	if (setButton.isPush()) {
		m_sceneChanger->ChangeScene(Scene_Setting);
	}
}

void Menu::Draw() {
	//描画モード
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//背景の描画
	DrawExtendGraph(0, 0, WIN_SIZE_X, WIN_SIZE_Y, backPic, true);
	
	//ボタンの描画
	startButton.draw();
	setButton.draw();
}

void Menu::Finalize() {
	//BGMの停止
	StopSoundMem(bgm);
	//画像削除
	deleteMem();
	//ボタンのFinalize
	startButton.finalize();
	setButton.finalize();
}

//画像、音声のメモリ解放
void Menu::deleteMem() {
	DeleteSoundMem(bgm);
	DeleteGraph(backPic);
}