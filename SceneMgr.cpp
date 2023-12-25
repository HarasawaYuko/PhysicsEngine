#include "SceneMgr.h"
#include "Game.h"
#include "Rec.h"
#include "DetectTest.h"
#include "MathTest.h"
#include "ObjectTest.h"

SceneMgr::SceneMgr() {
	m_scene = (BaseScene*)new MathTest(this);
}

void SceneMgr::Initialize() {
	m_next_scene = Scene_None;
	m_scene->Initialize();
}

void SceneMgr::Finalize() {
	m_scene->Finalize();
}

void SceneMgr::Update() {
	if (m_next_scene != Scene_None) {
		//現在のシーンの終了処理
		m_scene->Finalize();
		//メモリの解法
		delete m_scene;
		switch (m_next_scene) {
			break;
		case Scene_Game:
			m_scene = (BaseScene*) new Game(this);
			break;
		case Scene_TEST_REC:
			m_scene = (BaseScene*) new Rec(this);
			break;
		case Scene_TEST_Detect:
			m_scene = (BaseScene*) new DetectTest(this);
			break;
		case Scene_TEST_Math:
			m_scene = (BaseScene*) new MathTest(this);
			break;
		}
		m_next_scene = Scene_None;
		m_scene->Initialize();
	}
	m_scene->Update();
}

void SceneMgr::Draw() {
	m_scene->Draw();
}

void SceneMgr::ChangeScene(Scene next) {
	if (next == Scene_Fin) fin = true;
	m_next_scene = next;
}