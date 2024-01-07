#pragma once
#include "include.h"
#include "Math.h"
#include <functional>

bool isIn(const int, const int, const int, const int);

//色
typedef unsigned int Color;
const Color COLOR_GREEN = GetColor(0x10, 0xB5, 0x67);
const Color COLOR_BLUE = GetColor(0, 30, 150);
const Color COLOR_LBLUE = GetColor(101, 187, 233);
const Color COLOR_ORANGE = GetColor(0xFF, 0x99, 0x33);
const Color COLOR_WHITE = GetColor(230 , 230 ,230);
const Color COLOR_BLACK = GetColor(20, 20, 20);
const Color COLOR_RED = GetColor(220, 45, 35);
const Color COLOR_GRAY = GetColor(120, 120, 120);
const Color COLOR_YELLOW = GetColor(255 , 217 ,0);

class Button {
private:
	//画像
	int pic;//通常の画像
	int onPic;//カーソルが合っている時の画像
	int offPic;//無効時の画像
	//音声
	int sound;
	//左上の点
	int x;
	int y;
	//大きさ
	int width;
	int height;
	bool isOn;//カーソルが合っているか
	bool active = true;//ボタンが有効か
	bool push = false;//押されたら

public:
	Button() {};
	Button(const int pic, const int onPic, const int sound ,const int x, const int y, const int width , const int height , const int offPic = 0);
	Button(const int pic, const int onPic, const int sound, const int y, const int width ,const int offPic = 0);
	void update();
	void draw();
	void act(const bool);
	bool isPush();
	void finalize();
};

class RadioButton {
private:
	int num;
	int x;
	int y;
	int space;
	int size;
	int fontsize;
	
	std::vector<std::string> strs;
	int select;
	int on;
public:
	RadioButton(){}
	RadioButton(const int , const int , const int ,const int, const int ,const int,const std::vector<std::string>);
	void update(bool*);
	void draw()const;
	int getSelect() const;
};

class SlideBar {
private:
	int length;
	int x;
	int y;
	int size;
	int selectX;
	bool on;
public:
	SlideBar(){}
	SlideBar(const int , const int , const int , const int);
	void update(bool*);
	void draw() const;
	float getRate()const;
};

//Y軸反転の描画関数
int DrawCircleP(const float , const float , const float , const unsigned int, const int FillFrag = 1, const float LineThickness = 1.0f);
int DrawBoxP(const Vec2 cen, const int , const int , const double angle, const int graph, const float h, const float w, const int size_x, const int size_y, const int transFlag = 0, const int turnFlag = 0);
int DrawSegment(const Segment& , const unsigned int);
int DrawSegment(const Vec2& s, const Vec2& e, const unsigned int);
int DrawPoint(const Vec2& , const unsigned int);
int DrawTriP(const Vec2& ,const Vec2& , const Vec2& ,const unsigned int color = COLOR_BLACK , const int fill = 1 , const float thick = 1.f);
int DrawStrP(const Vec2& , const std::string , const unsigned int color = COLOR_BLACK);

//float値の桁数変換
std::string FtoStr(const float);