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

//ÉQÅ[ÉÄâÊñ 

class Rec :public BaseScene {
private:
	World world;
public:
	//ä÷êî
	void deleteMem();

	Rec(SceneChanger*);
	~Rec();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};