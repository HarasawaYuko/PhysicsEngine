#include "Game.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

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
static const int SelectY = 550;
static const int SelectX = 425;
static const int SelectCenX[3] = {485 , 610 , 735};
static const int SelectCenY = 490;
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

	//�{�^���̍쐬
	for (int i = 0; i < SelectNum; i++) {
		selectButton[i] = Button(selectPic , selectPicOn , selectSnd , SelectX +(i * (SelectWidth + SelectInterval)), SelectY, SelectWidth, SelectWidth);
	}
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
	//�}�`�I�����[�h
	if (selectMode) {
		//�{�^���������ꂽ���̏���
		for (int i = 0; i < SelectNum; i++) {
			if (selectButton[i].isPush()) {
				obj = Objects[i];
				obj->move(Vec2(200 , 470));
				//���W�̐ݒ�
				selectMode = false;
				Objects[i] = getObj(1);
				Objects[i]->changeSize(4000.f);
			}
		}
	}
	//�}�`�������[�h
	else {
		if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN)) {
			world.add(obj);
			selectMode = true;
		}
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
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_LEFT)) {
		m_sceneChanger->ChangeScene(Scene_TEST_Whole);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_RIGHT)) {
		m_sceneChanger->ChangeScene(Scene_Result);
	}
	world.physicsSimulate();

	//�_���v�Z
	score = 0;
	for (int i = 0; i < world.objects.size(); i++) {
		if (!world.objects[i]->isActive()) {
			continue;
		}
		score += (int)(world.objects[i]->getM() / 100.f);
	}
}

void Game::Draw() {
	//�`�惂�[�h
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//�w�i�̕`��
	DrawExtendGraph(0, 0, WIN_SIZE_X, WIN_SIZE_Y, backPic, true);
	//�Q�[���E�B���h�E�̕`��
	DrawExtendGraph(window_x1, window_y1, window_x2, window_y2, windowPic, true);
	//�{�^���̕`��
	for (int i = 0; i < 1; i++) {
		selectButton[i].draw();
		Objects[i]->Draw(/*SelectCenX[i] , SelectCenY*/);
	}
	//�X�R�A�g�̕\��
	DrawExtendGraph(score_x1, WIN_SIZE_Y - score_y1, score_x2, WIN_SIZE_Y - score_y2, scorePic, true);
	//�X�R�A�̕\��
	SetFontSize(50);
	std::string scoreStr = std::to_string(score) + "pt";
	int width = GetDrawStringWidth(scoreStr.c_str(), scoreStr.length());
	DrawFormatString(score_x1 + (score_x2 - score_x1)/2 - width/2 , WIN_SIZE_Y -(score_y1+ ((score_y2 - score_y1)/2 + 50/2)) , COLOR_BLACK ,"%s", scoreStr.c_str() );


	if (selectMode) {

	}
	else {
		obj->Draw(/*window_x1, window_y1*/);
	}
	//�Q�[���{�̂̕`��
	//SetDrawArea(window_x1 , WIN_SIZE_Y - window_y1 ,window_x2 , WIN_SIZE_Y - window_y2);
	//world->Draw(window_x1 , window_y1);
	for (auto& obj : world.objects) {
		obj->DrawEdge();
		//obj->getBbox().Draw();
	}
	SetDrawArea(0,0, WIN_SIZE_X, WIN_SIZE_Y);
	//�Q�[���E�B���h�E�g�̕`��
	DrawExtendGraph(window_x1, window_y1, window_x2, window_y2, windowFramePic, true);
}

void Game::Finalize() {
	//delete world;
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

void Game::initWorld() {
	//world = new World(1.f/(float)FPS /*, window_x2 - window_x1 , window_y2 - window_y1*/);
	world.initialize();
	//���̍쐬
	std::vector<Vec2> points;
	/*points.push_back(Vec2(FloorSideMargin ,FloorHeight));
	points.push_back(Vec2(FloorSideMargin + FloorWidth , -50.f));
	points.push_back(Vec2(FloorSideMargin , -50.f));
	points.push_back(Vec2(FloorSideMargin + FloorWidth, FloorHeight));*/
	points.emplace_back(0.f, 0.f);
	points.emplace_back((float)WIN_SIZE_X, 0.f);
	points.emplace_back(0.f, 30.f);
	points.emplace_back((float)WIN_SIZE_X, 30.f);
	Convex* con = new Convex(points, 0.f, 0.f, 0.f, 0.f, false);
	//Convex* con = new Convex(points);
	world.add(con);
}

//�����}�`�̍쐬
void Game::initSelect() {
	for (int i = 0; i < 1; i++) {
		Object* obj = getObj(1);
		obj->changeSize(4000.f);
		Objects[i] = obj;
	}
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
		/*points.emplace_back(0.f, 55.f);
		points.emplace_back(-48.f, -27.f);
		points.emplace_back(48.f, -27.f);*/
		points.emplace_back(0.f, 15.f);
		points.emplace_back(-17.f, -15.f);
		points.emplace_back(17.f, -15.f);
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
		break;
	case 4:
		//�~
		obj = new Circle();
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