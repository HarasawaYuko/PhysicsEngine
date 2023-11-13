#include "Game.h"


Game::Game(SceneChanger *changer) 
	:BaseScene(changer)
{}

Game::~Game() 
{}

void Game::Initialize() {
	Circle* cir1 = new Circle(300 , 300 , 20 );
	world.add(cir1);
}


void Game::Update() {
	world.physicsSimulate();
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