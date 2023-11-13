#pragma once
#include <functional>

#include "BaseScene.h"
#include "SceneChanger.h"
#include "World.h"
#include "UIMaterial.h"

//ƒQ[ƒ€‰æ–Ê

class Game :public BaseScene {
private:
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