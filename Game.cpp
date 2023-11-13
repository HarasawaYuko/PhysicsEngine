#include "Game.h"


Game::Game(SceneChanger *changer) 
	:BaseScene(changer)
{}

Game::~Game() 
{}

void Game::Initialize() {
	
}


void Game::Update() {
	world.physicsSimulate();
}

void Game::Draw() {
	for (auto obj : world.objects) {
		obj.Draw();
	}
}

void Game::Finalize() {
	
}

//�摜�A�����̃��������
void Game::deleteMem() {
}