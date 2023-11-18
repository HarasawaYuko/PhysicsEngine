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
	//�摜�̓ǂݍ���
	Box::loadGraph();
	//������
	world.initialize();
}


void Game::Update() {
	//���͏�Ԃ̎擾
	KeyBoard::instance()->update();
	Mouse::instance()->update();

	//��~�p
	static bool stop;
	if (KeyBoard::instance()->hitNow(KEY_INPUT_S)) {
		stop = !stop;
	}

	//�V�~�����[�V����
	if (!stop) {
		Rand* rand = Rand::instance();
		if (Mouse::instance()->getClickNow(LEFT_CLICK)) {
			world.add(new Circle(rand->get(100, 700), 500, rand->get(10, 80)));
		}
		else if (Mouse::instance()->getClickNow(RIGHT_CLICK)) {
			world.add(new Box(rand->get(100, 700), 500, rand->get(40, 60), rand->get(40, 60)));
		}
		world.physicsSimulate();
	}
}

void Game::Draw() {
	for (Object* obj : world.objects) {
		obj->Draw();
	}
}

void Game::Finalize() {
	for (Object* obj : world.objects) {
		delete obj;
	}
}

//�摜�A�����̃��������
void Game::deleteMem() {
}