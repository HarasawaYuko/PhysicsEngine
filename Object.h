#pragma once
#include "Math.h"
#include "UIMaterial.h"
#include "BBox.h"

//Objectクラス　演算対象の図形は必ず継承する
enum Type : uint8_t {
	CIRCLE = 0b0000'0001,
	LINE   = 0b0000'0010,
	BOX    = 0b0000'0100,
	CONVEX = 0b0000'1000
};

class Object {
protected:
	Vec2 center;//重心座標
	Vec2 force;//力
	Vec2 acceleration;//加速度
	Vec2 velocity;//速度
	bool active = true;
	bool touch = false;
	float mass;
	const Type type;
	Color color;
	uint16_t id;//削除されたオブジェクトも含めたインデックス
	int index;
	float friction;//摩擦係数
	float e;//反発係数
	float angle_v;//角速度　ラジアン
	float angle;//回転角　ラジアン
	float inertiaTensor;//慣性テンソル
	static const float MASS_RATE;
	BBox bbox;//バウンディングボックス（ワールド座標）
	Object(Vec2 v , Type ,float mass = 10 ,Color color = COLOR_BLACK ,bool act = true , float ang = 0.f , float ang_v = 0.f);
public:
	virtual void Draw()const = 0;
	float getM();
	Vec2 getC()const;
	Vec2 getV()const;
	void setAngle(const float);
	void setAngV(const float);
	void updateAngle(const float);
	float getAngle()const;
	float getAngV()const;
	bool isActive()const;
	void setMass(const float);
	void addV(const Vec2);
	void addVang(const float);
	void setTouch();
	void unTouch();
	void setId(const uint16_t);
	uint16_t getId()const;
	int getIndex()const;
	void setIndex(const int);
	void setFri(const float);
	float getFri() const;
	void setE(const float);
	float getE()const;
	Type getType()const;
	const BBox& getBbox()const;
	virtual void updatePos(const float) = 0;
	virtual bool isValid()const = 0;
	virtual std::string toString()const = 0;
	virtual void setBbox() = 0;
	virtual void setColor(Color color);
	unsigned int getColor() const;
	float getI()const;
	Vec2 getCirV(const Vec2&)const;
};