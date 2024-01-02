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
}

//‰~‚Ì•Ài‰^“®
void Game::Update() {
	//“ü—Íó‘Ô‚Ìæ“¾
	KeyBoard::instance()->update();
	Mouse::instance()->update();


	if (KeyBoard::instance()->hitNow(KEY_INPUT_LEFT)) {
		m_sceneChanger->ChangeScene(Scene_Menu);
	}
	if (KeyBoard::instance()->hitNow(KEY_INPUT_RIGHT)) {
		m_sceneChanger->ChangeScene(Scene_Result);
	}
}

void Game::Draw() {
}

void Game::Finalize() {
}

//‰æ‘œA‰¹º‚Ìƒƒ‚ƒŠ‰ğ•ú
void Game::deleteMem() {
}