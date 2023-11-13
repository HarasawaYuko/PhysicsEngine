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

//‰æ‘œA‰¹º‚Ìƒƒ‚ƒŠ‰ğ•ú
void Game::deleteMem() {
}