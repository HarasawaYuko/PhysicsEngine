#pragma once
#include "Object.h"
#include "UIMaterial.h"

//�~�N���X
class Circle :public Object{
private:
	float r;//���a
public:
	Circle();
	void Draw()override;
};