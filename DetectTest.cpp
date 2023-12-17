#include "DetectTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

DetectTest::DetectTest(SceneChanger* changer)
	:BaseScene(changer)
{}

DetectTest::~DetectTest()
{}

void DetectTest::Initialize() {
	//�摜�̓ǂݍ���
	Box::loadGraph();
	//������
	world.initialize();
	//���̍쐬
	Box* wall_under = new Box(400, 25, 50, 800, 0, 0, 0, 0, false);
	world.add(wall_under);
	//�����`�̔z�u
	Box* box1 = new Box(400, 500, 60, 70);
	world.add(box1);
	box1 = new Box(300, 300, 200, 100, 0, 0, 0, 0, false);
	world.add(box1);
}

//�~�̕��i�^��
void DetectTest::Update() {
	//���͏�Ԃ̎擾
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	//��~�p
	static bool stop;
	if (KeyBoard::instance()->hitNow(KEY_INPUT_S)) {
		stop = !stop;
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_C)) {
		m_sceneChanger->ChangeScene(Scene_Game);
	}

	//�V�~�����[�V����
	if (!stop) {
		Rand* rand = Rand::instance();
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			world.add(new Circle(rand->get(100, 700), 500, rand->get(10, 80), rand->get(-20, 20), rand->get(-20, 20)));
		}
		else if (Mouse::instance()->getClickNow(RIGHT_CLICK)) {
			world.add(new Box(rand->get(100, 700), 500, rand->get(40, 200), rand->get(40, 200), 0, 0, 0, 0 ));
		}
		world.physicsSimulate();
	}
}

void DetectTest::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "DetectTest", COLOR_BLACK);
	//printfDx("DrawSize:%d\n" , world.objects.size());
	for (Object* obj : world.objects) {
		obj->Draw();
	}
	for (Collision col : world.collisions) {
		col.Draw();
	}

	//LtoW�e�X�g�p
	Vec2 testPoint = Vec2(-200 , -100);
	Vec2 testCenter = Vec2(400 , 300);
	DrawCircle(testPoint.x, WIN_SIZE_Y - testPoint.y , 4, COLOR_GREEN);
	Vec2 rotaed = LtoW(testPoint , testCenter , 0);
	DrawCircle(rotaed.x, WIN_SIZE_Y - rotaed.y, 4, COLOR_GREEN);
	DrawLine(testPoint.x, WIN_SIZE_Y - testPoint.y , rotaed.x, WIN_SIZE_Y - rotaed.y ,COLOR_GREEN , 3.f);
}

void DetectTest::Finalize() {
	for (Object* obj : world.objects) {
		delete obj;
	}
}

//�摜�A�����̃��������
void DetectTest::deleteMem() {
}