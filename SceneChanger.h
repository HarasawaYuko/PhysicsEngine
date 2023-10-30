#pragma once

//シーン用列挙型
enum Scene{
	Scene_Menu,
	Scene_Game,
	Scene_Result,
	Scene_Fin,
	Scene_None
};

//シーン変更用インターフェース
class SceneChanger {
public:
	virtual void ChangeScene(Scene next) = 0;
};