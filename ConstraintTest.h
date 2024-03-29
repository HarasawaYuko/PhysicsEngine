#pragma once
#include <functional>

#include "BaseScene.h"
#include "SceneChanger.h"
#include "World.h"

//ゲーム画面

class ConstraintTest :public BaseScene {
private:
	World world;
public:
	//関数
	void deleteMem();

	ConstraintTest(SceneChanger*);
	~ConstraintTest();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};