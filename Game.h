#pragma once

#include "BaseScene.h"
#include "SceneChanger.h"
#include "World.h"
#include "UIMaterial.h"

//ゲーム画面

class Game :public BaseScene {
private:
	int backPic;
	int bgm;
	int windowPic;
	int windowFramePic;
	int scorePic;
	int score = 0;
	Button selectButton[3];
	World world;
	Object* Objects[3];
public:
	//関数
	void deleteMem();

	Game(SceneChanger*);
	~Game();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	void initWorld();
	void initSelect();
};