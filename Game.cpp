#include "Game.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "Share.h"

#include "Convex.h"
#include "Circle.h"

//�Q�[�����

//UI�f�U�C���p�萔
//�Q�[���E�B���h�E
static const int window_x1 = 20;
static const int window_y1 = 20;
static const int window_x2 = 420;
static const int window_y2 = 580;
static const int window_width = 400;
//�}�`�I��p�{�^��
static const int SelectNum = 3;
static const int SelectWidth = 120;
static const int SelectInterval = 5;
static const int SelectY = 530;
static const int SelectX = 425;
static const int SelectCenX[3] = {485 , 610 , 735};
static const int SelectCenY = 470;
//�I���{�^��
static const int FinButtonWidth = 50;
static const int FinButtonY = 590;
static const int FinButtonX = 740;
//�X�R�A�\��
static const int score_x1 = 500;
static const int score_y1 = 100;
static const int score_x2 = 780;
static const int score_y2 = 20;
//�Q�[��world�p�ϐ�
//��
static const float FloorSideMargin = 20.f;
static const float FloorHeight = 40.f;
static const float FloorWidth = 360.f;

//���[�h
static bool selectMode = true;
//�I�����ꂽ�}�`
static Object* obj;
static const float MoveDis = 3.f;//1�t���[���ňړ����鋗��
static const float RotaAng = Pi / 36.f;
static int ScrollY = 0;
static const int InitY = 300;
static int CorreY = 0;
static int DisMinY = 200;
static uint16_t recentId;

static const int BasicKind = 8;//��b�}�`�̎��

//�v���g�^�C�v�錾
Object* getObj(const int);

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
	windowFramePic = LoadGraph("pic/Game/WindowFrame.png");
	scorePic = LoadGraph("pic/Game/Score.png");
	int selectPic = LoadGraph("pic/Game/Select.png");
	int selectPicOn = LoadGraph("pic/Game/SelectOn.png");
	int selectSnd = LoadSoundMem("snd/Game/Select.mp3");
	int finPic = LoadGraph("pic/Game/FinButton.png");
	int finPicOn = LoadGraph("pic/Game/FinButtonOn.png");

	//�{�^���̍쐬
	for (int i = 0; i < SelectNum; i++) {
		selectButton[i] = Button(selectPic , selectPicOn , selectSnd , SelectX +(i * (SelectWidth + SelectInterval)), SelectY, SelectWidth, SelectWidth);
	}
	finButton = Button(finPic, finPicOn, -1, FinButtonX, FinButtonY, FinButtonWidth, FinButtonWidth);

	objNum = 0;
	ScrollY = 0;
	CorreY = 0;
	recentId = 1;

	rand = Rand::instance();

	//���[���h���쐬
	initWorld();

	//�����}�`���쐬
	initSelect();

	//BGM���Đ�
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, true);
}

void Game::Update() {
	//���͏�Ԃ̎擾
	KeyBoard::instance()->update();
	Mouse::instance()->update();
	//�{�^����update
	for (int i = 0; i < SelectNum; i++) {
		selectButton[i].update();
	}
	finButton.update();

	if (finButton.isPush()) {
		m_sceneChanger->ChangeScene(Scene_Menu);
	}

	int scrollKeep = ScrollY;
	//�X�N���[���ʂ��v�Z
	ScrollY += Mouse::instance()->getWheel() * 2;
	//�X�N���[���ʂ��N�����v
	ScrollY = max(ScrollY, 0);

	//�}�`�I�����[�h
	if (selectMode) {

		int maxY = -INT_MIN;
		for (int i = 0; i < world.objects.size(); i++) {
			int y = (int)(world.objects[i]->getBbox().point.y + world.objects[i]->getBbox().height);
			maxY = max(maxY, y);
		}
		CorreY = 0;
		int diff = InitY - maxY;
		if (diff < DisMinY) {
			CorreY = DisMinY - diff;
		}

		//�{�^���������ꂽ���̏���
		for (int i = 0; i < SelectNum; i++) {
			if (selectButton[i].isPush()) {
				//���O�ŗ��Ƃ����}�`�������������m�F����
				Object* obj_ = world.getObj(recentId);
				if (obj_->isActive() && !obj_->isTouch()) {
					break;
				}
				obj = Objects[i];
				obj->move(Vec2(200 , InitY + CorreY));
				//���W�̐ݒ�
				selectMode = false;
				Objects[i] = getBasicObj();
			}
		}
	}
	//�}�`�������[�h
	else {
		if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN)) {
			recentId = world.add(obj);
			selectMode = true;
			//�_���v�Z
			score = 0;
			for (int i = 0; i < world.objects.size(); i++) {
				if (!world.objects[i]->isActive()) {
					continue;
				}
				score += (int)(world.objects[i]->getM() / 100.f);
			}
		}
		//���ړ�
		if (KeyBoard::instance()->getState(KEY_INPUT_A)) {
			//BBox�𗘗p���Ĉړ��ł��邩�m�F
			if (0.f < obj->getBbox().point.x - MoveDis ) {
				obj->move(Vec2(-MoveDis , 0));
			}
		}
		if (KeyBoard::instance()->getState(KEY_INPUT_D)) {
			//BBox�𗘗p���Ĉړ��ł��邩�m�F
			if (obj->getBbox().point.x + obj->getBbox().width + MoveDis < window_width) {
				obj->move(Vec2(MoveDis, 0));
			}
		}
		//��]
		if (KeyBoard::instance()->getState(KEY_INPUT_W)) {
			//�[�ɗ]�T������ꍇ�̂݉�]�ł���
			if (0.f < obj->getBbox().point.x - 5.f && obj->getBbox().point.x+ obj->getBbox().width + 5.f < window_width) {
				obj->rotation(RotaAng);
			}
		}
		if (KeyBoard::instance()->getState(KEY_INPUT_S)) {
			//�[�ɗ]�T������ꍇ�̂݉�]�ł���
			if (0.f < obj->getBbox().point.x - 5.f && obj->getBbox().point.x + obj->getBbox().width + 5.f < window_width) {
				obj->rotation(-RotaAng);
			}
		}
		obj->move(Vec2(0 ,scrollKeep - ScrollY ));
	}



	world.physicsSimulate();

	//�Q�[���I�����m�F
	if (objNum > world.objects.size()) {
		//�I�u�W�F�N�g������������
		m_sceneChanger->ChangeScene(Scene_Result);
		return;
	}
	objNum = world.objects.size();
}

void Game::Draw() {
	//�`�惂�[�h
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//�w�i�̕`��
	DrawExtendGraph(0, 0, WIN_SIZE_X, WIN_SIZE_Y, backPic, true);
	//�Q�[���E�B���h�E�̕`��
	DrawExtendGraph(window_x1, window_y1, window_x2, window_y2, windowPic, true);
	//�{�^���̕`��
	for (int i = 0; i < 3; i++) {
		selectButton[i].draw();
		BBox bbox = Objects[i]->getBbox();
		float x = bbox.width / 2.f + bbox.point.x;
		float y = bbox.height / 2.f + bbox.point.y;
		Vec2 cen = Objects[i]->getC();
		Objects[i]->Draw(SelectCenX[i] -(x - cen.x), SelectCenY -(y - cen.y));
	}
	finButton.draw();

	//�X�R�A�g�̕\��
	DrawExtendGraph(score_x1, WIN_SIZE_Y - score_y1, score_x2, WIN_SIZE_Y - score_y2, scorePic, true);
	//�X�R�A�̕\��
	SetFontSize(50);
	std::string scoreStr = std::to_string(score);
	int width = GetDrawStringWidth(scoreStr.c_str(), scoreStr.length());
	DrawFormatString(score_x1 + (score_x2 - score_x1)/2 - width/2 , WIN_SIZE_Y -(score_y1+ ((score_y2 - score_y1)/2 + 50/2)) , COLOR_BLACK ,"%s", scoreStr.c_str() );


	if (selectMode) {

	}
	else {
		obj->Draw(window_x1, window_y1);
	}
	//�Q�[���{�̂̕`��
	SetDrawArea(window_x1 , WIN_SIZE_Y - window_y1 ,window_x2 , WIN_SIZE_Y - window_y2);
	world.Draw(window_x1 , window_y1 - ScrollY);
	SetDrawArea(0,0, WIN_SIZE_X, WIN_SIZE_Y);
	//�Q�[���E�B���h�E�g�̕`��
	DrawExtendGraph(window_x1, window_y1, window_x2, window_y2, windowFramePic, true);
}

void Game::Finalize() {
	//���[�h��ʂ̕\��
	DrawExtendGraph(0, 0, WIN_SIZE_X, WIN_SIZE_Y, Share::loadPic, true);
	//BGM�̒�~
	StopSoundMem(bgm);
	//�摜�폜
	deleteMem();
	Share::score = score;
}

//�摜�A�����̃��������
void Game::deleteMem() {
	DeleteSoundMem(bgm);
	DeleteGraph(backPic);
}

void Game::initWorld() {
	world.initialize();
	//���̍쐬
	std::vector<Vec2> points;
	points.push_back(Vec2(FloorSideMargin ,FloorHeight));
	points.push_back(Vec2(FloorSideMargin + FloorWidth , -50.f));
	points.push_back(Vec2(FloorSideMargin , -50.f));
	points.push_back(Vec2(FloorSideMargin + FloorWidth, FloorHeight));

	Convex* con = new Convex(points);
	con->setColor(COLOR_GRAY);
	world.add(con);
}

//�����}�`�̍쐬
void Game::initSelect() {
	for (int i = 0; i < 3; i++) {
		Object* obj = getObj(i);
		obj->changeSize(4000.f);
		Objects[i] = obj;
	}
}

//��{�}�`���w�肳�ꂽ�͈͓��Ő������ĕԂ�
//�}�`�̑傫���𗐐��Ō��肷��
//BBox�ŁA�{�^���Ɏ��܂邩�m�F���āA�C������
Object* Game::getBasicObj() const{
	Object* result;
	int kind = rand->get(0 , 6);
	result = getObj(kind);
	int size = rand->get(2000, 5000);
	result->changeSize(size);
	//�傫���𒲂ׂ�
	BBox bbox = result->getBbox();
	while (bbox.width > SelectWidth - 10 && bbox.height > SelectWidth - 10) {
		size = (int)((float)size * 0.95f);
		result->changeSize(size);
		bbox = result->getBbox();
	}
	result->setColor(getColorRand());
	return result;
}

/*�}�`�쐬*/
Object* getObj(const int p) {
	std::vector<Vec2> points;
	Object* obj;
	switch (p) {
	case 0:
		//�����`
		points.emplace_back(30.f, 20.f);
		points.emplace_back(30.f, -20.f);
		points.emplace_back(-30.f, 20.f);
		points.emplace_back(-30.f, -20.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	case 1:
		//���O�p�`
		points.emplace_back(0.f, 20.f);
		points.emplace_back(-17.32f, -10.f);
		points.emplace_back(17.32f, -10.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	case 2:
		//�����`
		points.emplace_back(-20.f, -20.f);
		points.emplace_back(-20.f, 20.f);
		points.emplace_back(20.f, 20.f);
		points.emplace_back(20.f, -20.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	case 3:
		//���p�O�p�`
		points.emplace_back(-40.f, 30.f);
		points.emplace_back(-40.f, -30.f);
		points.emplace_back(40.f, -30.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		obj->move(obj->getC() * -1);
		break;
	case 4:
		//�~
		obj = new Circle();
		break;
	case 5:
		//5�p�`
		points.emplace_back(10.f, 0.f);
		points.emplace_back(3.0901f, 9.51056f);
		points.emplace_back(-8.0901f, 5.877f);
		points.emplace_back(-8.0901f, -5.877f);
		points.emplace_back(3.0901f, -9.51056f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		obj->move(obj->getC() * -1);
		break;
	case 6:
		//�����`
		points.emplace_back(40.f, 10.f);
		points.emplace_back(40.f, -10.f);
		points.emplace_back(-40.f, 10.f);
		points.emplace_back(-40.f, -10.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	case 7:
		//���O�p�`
		points.emplace_back(0.f, 40.f);
		points.emplace_back(-17.32f, -10.f);
		points.emplace_back(17.32f, -10.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	default:
		//���O�p�`
		points.emplace_back(0.f, 60.f);
		points.emplace_back(-52.f, -30.f);
		points.emplace_back(52.f, -30.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	}
	obj->setColor(getColorRand());
	return obj;
}