#pragma once
#include <functional>

#include "BaseScene.h"
#include "SceneChanger.h"
#include "World.h"
#include "UIMaterial.h"
#include "Circle.h"

#include "Pair.h"

//�Q�[�����

class Menu :public BaseScene {
private:
	int backPic;//�w�i
	int bgm;//BGM
	Button startButton;
	Button setButton;
	Button finButton;
public:
	//�֐�
	void deleteMem();

	Menu(SceneChanger*);
	~Menu();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};