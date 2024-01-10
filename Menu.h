#pragma once
#include <functional>

#include "BaseScene.h"
#include "SceneChanger.h"
#include "World.h"
#include "UIMaterial.h"
#include "Circle.h"

#include "Pair.h"

//ÉQÅ[ÉÄâÊñ 

class Menu :public BaseScene {
private:
	int backPic;//îwåi
	int bgm;//BGM
	Button startButton;
	Button setButton;
	Button finButton;
public:
	//ä÷êî
	void deleteMem();

	Menu(SceneChanger*);
	~Menu();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};