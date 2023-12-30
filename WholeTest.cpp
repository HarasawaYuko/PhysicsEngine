#include "WholeTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"
#include "Convex.h"

//プロトタイプ宣言
Convex* getCon(const int);

static bool move = false;
static Rand* rand_;

WholeTest::WholeTest(SceneChanger* changer)
	:BaseScene(changer)
{}

WholeTest::~WholeTest()
{}

void WholeTest::Initialize() {
	world.initialize();
	rand_ = Rand::instance();
	Convex* con = getCon(2);
	con->setColor(GetColor(rand_->get(0, 155), rand_->get(0, 155), rand_->get(0, 155)));
	//床を設置
	world.add(con);

	//三角形を設置
	con = getCon(1);
	con->setColor(GetColor(rand_->get(0, 155), rand_->get(0, 155), rand_->get(0, 155)));
	con->setAngV(Pi/1.f);
	//con->setV(Vec2(30 , 0));
	//con->setAngV(Pi/12.f);
	con->move(Vec2(350.f , 500.f));
	//printfDx("%s\n" , con->getC().toString().c_str());
	world.add(con);

	//四角形を設置
	con = getCon(0);
	con->setColor(GetColor(rand_->get(0, 155), rand_->get(0, 155), rand_->get(0, 155)));
	con->setV(Vec2(20.f , 0.f));
	//con->setAngV(Pi / 6.f);
	con->move(Vec2(550.f , 500.f));
	world.add(con);

	//四角形を設置
	con = getCon(0);
	con->setColor(GetColor(rand_->get(0, 155), rand_->get(0, 155), rand_->get(0, 155)));
	con->setV(Vec2(0.f, -20.f));
	con->setAngV(Pi / 6.f);
	con->move(Vec2(450.f, 500.f));
	world.add(con);

}

//円の並進運動
void WholeTest::Update() {
	//入力状態の取得
	KeyBoard::instance()->update();
	Mouse::instance()->update();
	//シーン切り替え
	if (KeyBoard::instance()->hitNow(KEY_INPUT_RIGHT)) {
		m_sceneChanger->ChangeScene(Scene_Menu);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_LEFT)) {
		m_sceneChanger->ChangeScene(Scene_TEST_Constraint);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_SPACE)) {
		move = !move;
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_RETURN)) {
		Finalize();
		Initialize();
	}

  	if(move)world.physicsSimulate();
	if (!move && Mouse::instance()->getClickNow(RIGHT_CLICK)) {
		world.physicsSimulate();
	}
}

void WholeTest::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "Scene WholeTest", COLOR_BLACK);
	for (auto& obj : world.objects) {
		obj->Draw();
	}
/*その他描画*/
	//ペアの衝突情報
	if (world.pairs.size()!= 0) {
		DrawString(0 , 20 ,"Detect!" , COLOR_RED);
		DrawFormatString(0 , 40 ,COLOR_BLUE, "%s" ,world.pairs[0].toString().c_str());
	}
	DrawFormatString(150 , 200 , COLOR_BLACK,"ペア数 %d\n" , world.pairs.size());
	//三角形の速度
	if (world.objects.size() == 2) {
		DrawFormatString(world.objects[1]->getC().x + 40 , WIN_SIZE_Y - world.objects[1]->getC().y ,COLOR_GREEN , "%s" , world.objects[1]->getV().toString().c_str());
	}
}

void WholeTest::Finalize() {
	for (int i = 0; i < world.objects.size(); i++) {
		delete world.objects[i];
	}
}

//画像、音声のメモリ解放
void WholeTest::deleteMem() {
}

//テスト用の図形取得
Convex* getCon(const int p) {
	std::vector<Vec2> points;
	Convex* con;
	switch (p) {
	case 0:
		//四角形
		points.emplace_back(30.f , 20.f);
		points.emplace_back(30.f , -20.f);
		points.emplace_back(-30.f , 20.f);
		points.emplace_back(-30.f , -20.f);
		con = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	case 1:
		//三角形
		points.emplace_back(0.f, 60.f);
		points.emplace_back(-52.f, -30.f);
		points.emplace_back(52.f, -30.f);
		con = new Convex(points, 0.f, 0.f, 0.f, 0.f, true);
		break;
	case 2:
		//床
		points.emplace_back(0.f, 0.f);
		points.emplace_back((float)WIN_SIZE_X, 0.f);
		points.emplace_back(0.f, 200.f);
		points.emplace_back((float)WIN_SIZE_X, 200.f);
		con = new Convex(points, 0.f, 0.f, 0.f, 0.f, false);
		break;
	default:
		//床
		points.emplace_back(0.f, 0.f);
		points.emplace_back((float)WIN_SIZE_X, 0.f);
		points.emplace_back(0.f, 50.f);
		points.emplace_back((float)WIN_SIZE_X, 50.f);
		con = new Convex(points, 0.f, 0.f, 0.f, 0.f, false);
		break;
	}
	return con;
}