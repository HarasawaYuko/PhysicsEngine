#pragma once
#pragma once
#include <functional>

#include "BaseScene.h"
#include "SceneChanger.h"
#include "World.h"
#include "UIMaterial.h"
#include "Circle.h"
#include "Box.h"

#include "Pair.h"

//�Q�[�����

class Rec :public BaseScene {
private:
	World world;
public:
	//�֐�
	void deleteMem();

	Rec(SceneChanger*);
	~Rec();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};