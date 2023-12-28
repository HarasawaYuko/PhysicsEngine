#include "Game.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

Game::Game(SceneChanger *changer) 
	:BaseScene(changer)
{}

Game::~Game() 
{}

void Game::Initialize() {
	//画像の読み込み
	Box::loadGraph();
	//初期化
	world.initialize();
	//床の作成
	Line* wall_under = new Line(Vec2(30, 50), Vec2(770, 50), false);
	world.add(wall_under);
	//円の配置
	Circle* cir1 = new Circle(300, 500, 50);
	world.add(cir1);
	cir1 = new Circle(400, 300, 70, 0, 0, false);
	world.add(cir1);
	//長方形の配置
	Box* box1 = new Box(400, 500, 60, 70);
	world.add(box1);
}

//円の並進運動
void Game::Update() {
	//入力状態の取得
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	//停止用
	static bool stop;
	if (KeyBoard::instance()->hitNow(KEY_INPUT_S)) {
		stop = !stop;
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_C)) {
		m_sceneChanger->ChangeScene(Scene_TEST_REC);
	}

	//シミュレーション
	if (!stop) {
		Rand* rand = Rand::instance();
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			world.add(new Circle(rand->get(100, 700), 500, rand->get(10, 80) , rand->get(-20, 20) , rand->get(-20, 20)));
		}
		else if (Mouse::instance()->getClickNow(RIGHT_CLICK)) {
			world.add(new Box(rand->get(100, 700), 500, rand->get(40, 60), rand->get(40, 60)));
		}
		world.physicsSimulate();
	}

	if (KeyBoard::instance()->hitNow(KEY_INPUT_LEFT)) {
		m_sceneChanger->ChangeScene(Scene_Menu);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_RIGHT)) {
		m_sceneChanger->ChangeScene(Scene_Result);
	}
}

void Game::Draw() {
	//printfDx("DrawSize:%d\n" , world.objects.size());
	for (Object* obj : world.objects) {
		obj->Draw();
		if (obj->getType() == CIRCLE) {
			//printfDx("%f , %f \n", obj->getC().x, obj->getC().y);
		}
	}
}

void Game::Finalize() {
	for (Object* obj : world.objects) {
		delete obj;
	}
}

//画像、音声のメモリ解放
void Game::deleteMem() {
}