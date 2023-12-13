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
	//�摜�̓ǂݍ���
	Box::loadGraph();
	//������
	world.initialize();
	//���̍쐬
	Line* wall_under = new Line(Vec2(30, 50), Vec2(770, 50), false);
	world.add(wall_under);
	//�����`�̔z�u
	Box* box1 = new Box(400, 500, 60, 70);
	world.add(box1);
}

//�~�̕��i�^��
void Rec::Update() {
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
			world.add(new Box(rand->get(100, 700), 500, rand->get(40, 60), rand->get(40, 60)));
		}
		world.physicsSimulate();
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

//�摜�A�����̃��������
void Rec::deleteMem() {
}