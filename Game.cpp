#include "Game.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "Share.h"

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
static const int SelectY = 530;
static const int SelectX = 425;
static const int SelectCenX[3] = {485 , 610 , 735};
static const int SelectCenY = 470;
//終了ボタン
static const int FinButtonWidth = 50;
static const int FinButtonY = 590;
static const int FinButtonX = 740;
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
static const float RotaAng = Pi / 36.f;
static int ScrollY = 0;
static const int InitY = 300;
static int CorreY = 0;
static int DisMinY = 200;
static uint16_t recentId;

static const int BasicKind = 8;//基礎図形の種類

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
	int finPic = LoadGraph("pic/Game/FinButton.png");
	int finPicOn = LoadGraph("pic/Game/FinButtonOn.png");

	//ボタンの作成
	for (int i = 0; i < SelectNum; i++) {
		selectButton[i] = Button(selectPic , selectPicOn , selectSnd , SelectX +(i * (SelectWidth + SelectInterval)), SelectY, SelectWidth, SelectWidth);
	}
	finButton = Button(finPic, finPicOn, -1, FinButtonX, FinButtonY, FinButtonWidth, FinButtonWidth);

	objNum = 0;
	ScrollY = 0;
	CorreY = 0;
	recentId = 1;

	rand = Rand::instance();

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
	finButton.update();

	if (finButton.isPush()) {
		m_sceneChanger->ChangeScene(Scene_Menu);
	}

	int scrollKeep = ScrollY;
	//スクロール量を計算
	ScrollY += Mouse::instance()->getWheel() * 2;
	//スクロール量をクランプ
	ScrollY = max(ScrollY, 0);

	//図形選択モード
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

		//ボタンが押された時の処理
		for (int i = 0; i < SelectNum; i++) {
			if (selectButton[i].isPush()) {
				//直前で落とした図形が落下したか確認する
				Object* obj_ = world.getObj(recentId);
				if (obj_->isActive() && !obj_->isTouch()) {
					break;
				}
				obj = Objects[i];
				obj->move(Vec2(200 , InitY + CorreY));
				//座標の設定
				selectMode = false;
				Objects[i] = getBasicObj();
			}
		}
	}
	//図形落下モード
	else {
		if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN)) {
			recentId = world.add(obj);
			selectMode = true;
			//点数計算
			score = 0;
			for (int i = 0; i < world.objects.size(); i++) {
				if (!world.objects[i]->isActive()) {
					continue;
				}
				score += (int)(world.objects[i]->getM() / 100.f);
			}
		}
		//横移動
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
		//回転
		if (KeyBoard::instance()->getState(KEY_INPUT_W)) {
			//端に余裕がある場合のみ回転できる
			if (0.f < obj->getBbox().point.x - 5.f && obj->getBbox().point.x+ obj->getBbox().width + 5.f < window_width) {
				obj->rotation(RotaAng);
			}
		}
		if (KeyBoard::instance()->getState(KEY_INPUT_S)) {
			//端に余裕がある場合のみ回転できる
			if (0.f < obj->getBbox().point.x - 5.f && obj->getBbox().point.x + obj->getBbox().width + 5.f < window_width) {
				obj->rotation(-RotaAng);
			}
		}
		obj->move(Vec2(0 ,scrollKeep - ScrollY ));
	}



	world.physicsSimulate();

	//ゲーム終了を確認
	if (objNum > world.objects.size()) {
		//オブジェクト数が減ったら
		m_sceneChanger->ChangeScene(Scene_Result);
		return;
	}
	objNum = world.objects.size();
}

void Game::Draw() {
	//描画モード
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//背景の描画
	DrawExtendGraph(0, 0, WIN_SIZE_X, WIN_SIZE_Y, backPic, true);
	//ゲームウィンドウの描画
	DrawExtendGraph(window_x1, window_y1, window_x2, window_y2, windowPic, true);
	//ボタンの描画
	for (int i = 0; i < 3; i++) {
		selectButton[i].draw();
		BBox bbox = Objects[i]->getBbox();
		float x = bbox.width / 2.f + bbox.point.x;
		float y = bbox.height / 2.f + bbox.point.y;
		Vec2 cen = Objects[i]->getC();
		Objects[i]->Draw(SelectCenX[i] -(x - cen.x), SelectCenY -(y - cen.y));
	}
	finButton.draw();

	//スコア枠の表示
	DrawExtendGraph(score_x1, WIN_SIZE_Y - score_y1, score_x2, WIN_SIZE_Y - score_y2, scorePic, true);
	//スコアの表示
	SetFontSize(50);
	std::string scoreStr = std::to_string(score);
	int width = GetDrawStringWidth(scoreStr.c_str(), scoreStr.length());
	DrawFormatString(score_x1 + (score_x2 - score_x1)/2 - width/2 , WIN_SIZE_Y -(score_y1+ ((score_y2 - score_y1)/2 + 50/2)) , COLOR_BLACK ,"%s", scoreStr.c_str() );


	if (selectMode) {

	}
	else {
		obj->Draw(window_x1, window_y1);
	}
	//ゲーム本体の描画
	SetDrawArea(window_x1 , WIN_SIZE_Y - window_y1 ,window_x2 , WIN_SIZE_Y - window_y2);
	world.Draw(window_x1 , window_y1 - ScrollY);
	SetDrawArea(0,0, WIN_SIZE_X, WIN_SIZE_Y);
	//ゲームウィンドウ枠の描画
	DrawExtendGraph(window_x1, window_y1, window_x2, window_y2, windowFramePic, true);
}

void Game::Finalize() {
	//ロード画面の表示
	DrawExtendGraph(0, 0, WIN_SIZE_X, WIN_SIZE_Y, Share::loadPic, true);
	//BGMの停止
	StopSoundMem(bgm);
	//画像削除
	deleteMem();
	Share::score = score;
}

//画像、音声のメモリ解放
void Game::deleteMem() {
	DeleteSoundMem(bgm);
	DeleteGraph(backPic);
}

void Game::initWorld() {
	world.initialize();
	//床の作成
	std::vector<Vec2> points;
	points.push_back(Vec2(FloorSideMargin ,FloorHeight));
	points.push_back(Vec2(FloorSideMargin + FloorWidth , -50.f));
	points.push_back(Vec2(FloorSideMargin , -50.f));
	points.push_back(Vec2(FloorSideMargin + FloorWidth, FloorHeight));

	Convex* con = new Convex(points);
	con->setColor(COLOR_GRAY);
	world.add(con);
}

//初期図形の作成
void Game::initSelect() {
	for (int i = 0; i < 3; i++) {
		Object* obj = getObj(i);
		obj->changeSize(4000.f);
		Objects[i] = obj;
	}
}

//基本図形を指定された範囲内で生成して返す
//図形の大きさを乱数で決定する
//BBoxで、ボタンに収まるか確認して、修正する
Object* Game::getBasicObj() const{
	Object* result;
	int kind = rand->get(0 , 6);
	result = getObj(kind);
	int size = rand->get(2000, 5000);
	result->changeSize(size);
	//大きさを調べる
	BBox bbox = result->getBbox();
	while (bbox.width > SelectWidth - 10 && bbox.height > SelectWidth - 10) {
		size = (int)((float)size * 0.95f);
		result->changeSize(size);
		bbox = result->getBbox();
	}
	result->setColor(getColorRand());
	return result;
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
		points.emplace_back(0.f, 20.f);
		points.emplace_back(-17.32f, -10.f);
		points.emplace_back(17.32f, -10.f);
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
		obj->move(obj->getC() * -1);
		break;
	case 4:
		//円
		obj = new Circle();
		break;
	case 5:
		//5角形
		points.emplace_back(10.f, 0.f);
		points.emplace_back(3.0901f, 9.51056f);
		points.emplace_back(-8.0901f, 5.877f);
		points.emplace_back(-8.0901f, -5.877f);
		points.emplace_back(3.0901f, -9.51056f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		obj->move(obj->getC() * -1);
		break;
	case 6:
		//長方形
		points.emplace_back(40.f, 10.f);
		points.emplace_back(40.f, -10.f);
		points.emplace_back(-40.f, 10.f);
		points.emplace_back(-40.f, -10.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	case 7:
		//正三角形
		points.emplace_back(0.f, 40.f);
		points.emplace_back(-17.32f, -10.f);
		points.emplace_back(17.32f, -10.f);
		obj = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
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