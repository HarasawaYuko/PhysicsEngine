#include "Rec.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

Rec::Rec(SceneChanger* changer)
	:BaseScene(changer)
{}

Rec::~Rec()
{}

void Rec::Initialize() {
	//画像の読み込み
	Box::loadGraph();
	//初期化
	world.initialize();
	//床の作成
	Box* wall_under = new Box( 400 ,25 ,50 , 800 , 0,0,0,0,false);
	world.add(wall_under);
	//長方形の配置
	Box* box1 = new Box(400, 500, 60, 70);
	world.add(box1);
	box1 = new Box(300 ,300 ,200 , 100  , 0 ,0,0,0 ,false);
	world.add(box1);
}

//円の並進運動
void Rec::Update() {
	//入力状態の取得
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	//停止用
	static bool stop;
	if (KeyBoard::instance()->hitNow(KEY_INPUT_S)) {
		stop = !stop;
	}

	//シミュレーション
	if (!stop) {
		Rand* rand = Rand::instance();
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			world.add(new Circle(rand->get(100, 700), 500, rand->get(10, 80), rand->get(-20, 20), rand->get(-20, 20)));
		}
		else if (Mouse::instance()->getClickNow(RIGHT_CLICK)) {
			world.add(new Box(rand->get(100, 700), 500, rand->get(40, 200), rand->get(40, 200) , rand->get(-20, 20), 0, 0, rand->get(-5, 5) / 10));
		}
		world.physicsSimulate();
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_LEFT)) {
		m_sceneChanger->ChangeScene(Scene_Result);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_RIGHT)) {
		m_sceneChanger->ChangeScene(Scene_TEST_Object);
	}
}

void Rec::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "Scene Rec", COLOR_BLACK);
	//printfDx("DrawSize:%d\n" , world.objects.size());
	for (Object* obj : world.objects) {
		obj->Draw();
		if (obj->getType() == CIRCLE) {
			//printfDx("%f , %f \n", obj->getC().x, obj->getC().y);
		}
	}
}

void Rec::Finalize() {
	for (Object* obj : world.objects) {
		delete obj;
	}
}

//画像、音声のメモリ解放
void Rec::deleteMem() {
}