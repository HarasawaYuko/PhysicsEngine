#include "Game.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

#include "Convex.h"
#include "Circle.h"

//ゲーム画面

//UIデザイン用定数
//ゲームウィンドウ
static const int window_x1 = 20;
static const int window_y1 = 20;
static const int window_x2 = 420;
static const int window_y2 = 580;
static const int window_width = 400;
//図形選択用ボタン
static const int SelectNum = 3;
static const int SelectWidth = 120;
static const int SelectInterval = 5;
static const int SelectY = 550;
static const int SelectX = 425;
static const int SelectCenX[3] = {485 , 610 , 735};
static const int SelectCenY = 490;
//スコア表示
static const int score_x1 = 500;
static const int score_y1 = 100;
static const int score_x2 = 780;
static const int score_y2 = 20;
//ゲームworld用変数
//床
static const float FloorSideMargin = 20.f;
static const float FloorHeight = 40.f;
static const float FloorWidth = 360.f;

//モード
static bool selectMode = true;
//選択された図形
static Object* obj;
static const float MoveDis = 3.f;//1フレームで移動する距離

//プロトタイプ宣言
Object* getObj(const int);

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
	windowFramePic = LoadGraph("pic/Game/WindowFrame.png");
	scorePic = LoadGraph("pic/Game/Score.png");
	int selectPic = LoadGraph("pic/Game/Select.png");
	int selectPicOn = LoadGraph("pic/Game/SelectOn.png");
	int selectSnd = LoadSoundMem("snd/Game/Select.mp3");

	//ボタンの作成
	for (int i = 0; i < SelectNum; i++) {
		selectButton[i] = Button(selectPic , selectPicOn , selectSnd , SelectX +(i * (SelectWidth + SelectInterval)), SelectY, SelectWidth, SelectWidth);
	}
	//ワールドを作成
	initWorld();

	//初期図形を作成
	initSelect();

	//BGMを再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, true);
}

void Game::Update() {
	//入力状態の取得
	KeyBoard::instance()->update();
	Mouse::instance()->update();
	//ボタンのupdate
	for (int i = 0; i < SelectNum; i++) {
		selectButton[i].update();
	}
	//図形選択モード
	if (selectMode) {
		//ボタンが押された時の処理
		for (int i = 0; i < SelectNum; i++) {
			if (selectButton[i].isPush()) {
				obj = Objects[i];
				obj->move(Vec2(200 , 470));
				//座標の設定
				selectMode = false;
				Objects[i] = getObj(1);
				Objects[i]->changeSize(4000.f);
			}
		}
	}
	//図形落下モード
	else {
		if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN)) {
			world.add(obj);
			selectMode = true;
		}
		if (KeyBoard::instance()->getState(KEY_INPUT_A)) {
			//BBoxを利用して移動できるか確認
			if (0.f < obj->getBbox().point.x - MoveDis ) {
				obj->move(Vec2(-MoveDis , 0));
			}
		}
		if (KeyBoard::instance()->getState(KEY_INPUT_D)) {
			//BBoxを利用して移動できるか確認
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

	//点数計算
	score = 0;
	for (int i = 0; i < world.objects.size(); i++) {
		if (!world.objects[i]->isActive()) {
			continue;
		}
		score += (int)(world.objects[i]->getM() / 100.f);
	}
}

void Game::Draw() {
	//描画モード
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//背景の描画
	DrawExtendGraph(0, 0, WIN_SIZE_X, WIN_SIZE_Y, backPic, true);
	//ゲームウィンドウの描画
	DrawExtendGraph(window_x1, window_y1, window_x2, window_y2, windowPic, true);
	//ボタンの描画
	for (int i = 0; i < 1; i++) {
		selectButton[i].draw();
		Objects[i]->Draw(/*SelectCenX[i] , SelectCenY*/);
	}
	//スコア枠の表示
	DrawExtendGraph(score_x1, WIN_SIZE_Y - score_y1, score_x2, WIN_SIZE_Y - score_y2, scorePic, true);
	//スコアの表示
	SetFontSize(50);
	std::string scoreStr = std::to_string(score) + "pt";
	int width = GetDrawStringWidth(scoreStr.c_str(), scoreStr.length());
	DrawFormatString(score_x1 + (score_x2 - score_x1)/2 - width/2 , WIN_SIZE_Y -(score_y1+ ((score_y2 - score_y1)/2 + 50/2)) , COLOR_BLACK ,"%s", scoreStr.c_str() );


	if (selectMode) {

	}
	else {
		obj->Draw(/*window_x1, window_y1*/);
	}
	//ゲーム本体の描画
	//SetDrawArea(window_x1 , WIN_SIZE_Y - window_y1 ,window_x2 , WIN_SIZE_Y - window_y2);
	//world->Draw(window_x1 , window_y1);
	for (auto& obj : world.objects) {
		obj->DrawEdge();
		//obj->getBbox().Draw();
	}
	SetDrawArea(0,0, WIN_SIZE_X, WIN_SIZE_Y);
	//ゲームウィンドウ枠の描画
	DrawExtendGraph(window_x1, window_y1, window_x2, window_y2, windowFramePic, true);
}

void Game::Finalize() {
	//delete world;
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

void Game::initWorld() {
	//world = new World(1.f/(float)FPS /*, window_x2 - window_x1 , window_y2 - window_y1*/);
	world.initialize();
	//床の作成
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

//初期図形の作成
void Game::initSelect() {
	for (int i = 0; i < 1; i++) {
		Object* obj = getObj(1);
		obj->changeSize(4000.f);
		Objects[i] = obj;
	}
}

/*図形作成*/
Object* getObj(const int p) {
	std::vector<Vec2> points;
	Object* obj;
	switch (p) {
	case 0:
		//長方形
		points.emplace_back(30.f, 20.f);
		points.emplace_back(30.f, -20.f);
		points.emplace_back(-30.f, 20.f);
		points.emplace_back(-30.f, -20.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	case 1:
		//正三角形
		/*points.emplace_back(0.f, 55.f);
		points.emplace_back(-48.f, -27.f);
		points.emplace_back(48.f, -27.f);*/
		points.emplace_back(0.f, 15.f);
		points.emplace_back(-17.f, -15.f);
		points.emplace_back(17.f, -15.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	case 2:
		//正方形
		points.emplace_back(-20.f, -20.f);
		points.emplace_back(-20.f, 20.f);
		points.emplace_back(20.f, 20.f);
		points.emplace_back(20.f, -20.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	case 3:
		//直角三角形
		points.emplace_back(-40.f, 30.f);
		points.emplace_back(-40.f, -30.f);
		points.emplace_back(40.f, -30.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	case 4:
		//円
		obj = new Circle();
	default:
		//正三角形
		points.emplace_back(0.f, 60.f);
		points.emplace_back(-52.f, -30.f);
		points.emplace_back(52.f, -30.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	}
	obj->setColor(getColorRand());
	return obj;
}