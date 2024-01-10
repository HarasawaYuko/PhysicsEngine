#pragma once

#include <functional>

#include "BaseScene.h"
#include "SceneChanger.h"
#include "World.h"
#include "UIMaterial.h"

//ÉQÅ[ÉÄâÊñ 

class Result :public BaseScene {
private:
	World world;
	int backPic;
	int bgm;
	Button nextButton;
	Button retryButton;
public:
	//ä÷êî
	void deleteMem();

	Result(SceneChanger*);
	~Result();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};