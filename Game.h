#pragma once
#include <functional>

#include "BaseScene.h"
#include "SceneChanger.h"
#include "World.h"
#include "UIMaterial.h"

//�Q�[�����

class Game :public BaseScene {
private:
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