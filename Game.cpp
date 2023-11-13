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

//‰æ‘œA‰¹º‚Ìƒƒ‚ƒŠ‰ğ•ú
void Game::deleteMem() {
}