#include "Result.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "Share.h"

static const int NextButtonY = 210;
static const int RetryButtonY = 290;
static const int ButtonWidth = 250;
static const int ScoreY = 420;

Result::Result(SceneChanger* changer)
	:BaseScene(changer)
{}

Result::~Result()
{}

void Result::Initialize() {
	//�摜�Ɖ����̃��[�h
	backPic = LoadGraph("pic/Result/Back.png");
	bgm = LoadSoundMem("snd/Result/bgm.mp3");
	int nextPic = LoadGraph("pic/Result/next.png");
	int nextOnPic = LoadGraph("pic/Result/nextOn.png");
	int nextSnd = LoadSoundMem("snd/Result/next.mp3");
	int retryPic = LoadGraph("pic/Result/retry.png");
	int retryOnPic = LoadGraph("pic/Result/retryOn.png");
	int retrySnd = LoadSoundMem("snd/Result/retry.mp3");



	//BGM���Đ�
	PlaySoundMem(bgm, DX_PLAYTYPE_BACK, true);
	
	//�{�^���̍쐬
	nextButton = Button(nextPic , nextOnPic ,nextSnd ,NextButtonY ,ButtonWidth);
	retryButton = Button(retryPic , retryOnPic , retrySnd , RetryButtonY , ButtonWidth);
}

//�~�̕��i�^��
void Result::Update() {
	//���͏�Ԃ̎擾
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	//�{�^���̍X�V
	nextButton.update();
	retryButton.update();

	if (nextButton.isPush()) {
		m_sceneChanger->ChangeScene(Scene_Menu);
	}
	if (retryButton.isPush()) {
		m_sceneChanger->ChangeScene(Scene_Game);
	}
}

void Result::Draw() {
	//�w�i�̕`��
	DrawExtendGraph(0, 0, WIN_SIZE_X, WIN_SIZE_Y, backPic, true);

	SetFontSize(20);
	//�{�^���̕`��
	nextButton.draw();
	retryButton.draw();
	
	SetFontSize(90);
	std::string scoreStr = std::to_string(Share::score);
	int length = GetDrawStringWidth(scoreStr.c_str(), scoreStr.length());
	DrawFormatString((WIN_SIZE_X - length)/2 , WIN_SIZE_Y - ScoreY , COLOR_BLACK , "%d" , Share::score);
	SetFontSize(40);
	DrawString(WIN_SIZE_X/2 + length/2 , WIN_SIZE_Y- ( ScoreY - (90-40)), "pt", COLOR_BLACK);
}

void Result::Finalize() {
	//���[�h��ʂ̕\��
	DrawExtendGraph(0, 0, WIN_SIZE_X, WIN_SIZE_Y, Share::loadPic, true);
	//BGM�̒�~
	StopSoundMem(bgm);
	//�������폜
	nextButton.finalize();
	retryButton.finalize();
}

//�摜�A�����̃��������
void Result::deleteMem() {
	DeleteSoundMem(bgm);
	DeleteGraph(backPic);
}