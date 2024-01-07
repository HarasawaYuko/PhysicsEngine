#pragma once

#include "BaseScene.h"
#include "SceneChanger.h"
#include "World.h"
#include "UIMaterial.h"

//�Q�[�����

class Game :public BaseScene {
private:
	int backPic;
	int bgm;
	int windowPic;
	World world;
public:
	//�֐�
	void deleteMem();

	Game(SceneChanger*);
	~Game();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};