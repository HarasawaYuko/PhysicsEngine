#pragma once

#include "BaseScene.h"
#include "SceneChanger.h"
#include "World.h"
#include "UIMaterial.h"

//ƒQ[ƒ€‰æ–Ê

class Game :public BaseScene {
private:
	int backPic;
	int bgm;
	int windowPic;
	World world;
public:
	//ŠÖ”
	void deleteMem();

	Game(SceneChanger*);
	~Game();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};