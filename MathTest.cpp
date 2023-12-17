#include "MathTest.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Rand.h"

static Segment line;
static Vec2 point;
static bool start = true;

MathTest::MathTest(SceneChanger* changer)
	:BaseScene(changer)
{}

MathTest::~MathTest()
{}

void MathTest::Initialize() {
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

void MathTest::Update() {
	//���͏�Ԃ̎擾
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	//��~�p
	static bool stop;
	if (KeyBoard::instance()->hitNow(KEY_INPUT_S)) {
		line.start = Vec2();
		line.end = Vec2();
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_C)) {
		m_sceneChanger->ChangeScene(Scene_Game);
	}

	if (!stop) {
		Rand* rand = Rand::instance();
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			if (start) {
				line.start.set(Mouse::instance()->getX(), Mouse::instance()->getY());
			}
			else {
				line.end.set(Mouse::instance()->getX(), Mouse::instance()->getY());
			}
			start = !start;
		}
		else if (Mouse::instance()->getClickNow(RIGHT_CLICK)) {
			point.set(Mouse::instance()->getX(), Mouse::instance()->getY());
		}
		world.physicsSimulate();
	}
}

void MathTest::Draw() {
	SetFontSize(20);
	DrawString(640, 0, "MathTest", COLOR_BLACK);
	
	DrawSegment(line , COLOR_BLUE);
	DrawPoint(point , COLOR_RED);
}

void MathTest::Finalize() {
	for (Object* obj : world.objects) {
		delete obj;
	}
}

//�摜�A�����̃��������
void MathTest::deleteMem() {
}