#include "Pair.h"
#include "detect.h"
#include "World.h"
#include "Solver.h"

World::World(float timeStep)
{
	TIME_STEP = timeStep;
	objNum = 0;
}

void World::initialize() {
	//初期化
	objNum = 0;
	Solver::initialize(TIME_STEP);
	pairs.clear();
	objects.clear();
}

void World::physicsSimulate() {
	static int count = 0;
	count++;
	//外力を加える
	applyForce();

	//衝突検知
	detectCollision();
	
	//拘束の解消
	solveConstraints();
	
	//位置の更新
	integrate();
}

void World::add(Object* obj) {
	objects.push_back(obj);
	objNum++;
	//ユニークなidの割り当て
	totalNum++;
	obj->setId(totalNum);
	//オブジェクト種類によってソート
	std::sort(objects.begin(), objects.end() , [](const Object* a, const Object* b) {
		return (uint16_t)a->getType() < (uint16_t)b->getType();
		});
	//インデックスの振り直し
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->setIndex(i);
	}
}

/***private***/
//力を加える
void World::applyForce() {
	//重力加速度を計算
	float acc = -gravity * TIME_STEP;
	for (Object* obj : objects) {
		obj->addV(Vec2(0, acc));
	}
}

//衝突検知
void World::detectCollision() {
//ブロードフェーズ
	std::vector<Pair> nowPairs;//検出されたペア
	static int count = 0;
	count++;
	for (int i = 0; i < objNum; i++) {
		for (int j = i + 1; j < objNum; j++) {
			//バウンディングボックスによる判定
			if (Detect::broard(objects[i], objects[j])) {
				//見つかったらペアを作成
				nowPairs.emplace_back(objects[i] , objects[j]);
				nowPairs.back().setType(New);
			}
		}
	}
	//前のリストと比較してTypeを設定
	for (int i = 0; i < nowPairs.size(); i++) {
		for (int j = 0; j < pairs.size();j++) {
			//同じ種類が検出されたら
			if (nowPairs[i].getKey() == pairs[j].getKey()) {
				nowPairs[i] = pairs[j];
				nowPairs[i].setType(Keep);
			}
		}
	}
	//ペアの配列を更新
	this->pairs = nowPairs;
	//以前の衝突点の状況を確認し、更新する
	for (int i = 0; i < pairs.size();i++) {
		pairs[i].refreshCp();
	}


//ナローフェーズ
	std::vector<uint32_t> erase;
	for (int i = 0; i < pairs.size(); i++) {
		const Pair& pair = pairs[i];
		float depth;//貫通深度
		Vec2 n;//衝突法線ベクトル
		Vec2 coord[2];//衝突座標
		Vec2 coord_[2];//衝突座標（辺上）
		//衝突した種類で場合分け
		switch (pair.getKind()) {
		case CONVEX_CONVEX:
			if (Detect::convex_convex(pair.getObj0(), pair.getObj1(), &depth, &n, coord ,coord_)) {
				//衝突していたら衝突情報を記録
				ContactPoint cp;
				cp.depth = depth;
				cp.normal = n;
				cp.pointA = coord[0];
				cp.pointB = coord[1];
				cp.pointA_ = coord_[0];
				cp.pointB_ = coord_[1];
				cp.constraint->accumImpulse = 0.f;
				pair.getCol()->addCp(cp);
			}
			else {
				//衝突していなければ
				erase.push_back(pair.getKey());//キーを記録
			}
			break;
		case CIRCLE_CIRCLE:
			if (Detect::circle_circle(pair.getObj0(), pair.getObj1(), &depth, &n, coord, coord_)) {
				//衝突していたら衝突情報を記録
				ContactPoint cp;
				cp.depth = depth;
				cp.normal = n;
				cp.pointA = coord[0];
				cp.pointB = coord[1];
				cp.pointA_ = coord_[0];
				cp.pointB_ = coord_[1];
				cp.constraint->accumImpulse = 0.f;
				pair.getCol()->addCp(cp);
			}
			else {
				//衝突していなければ
				erase.push_back(pair.getKey());//キーを記録
			}
			break;
		case CIRCLE_CONVEX:
			if (Detect::circle_convex(pair.getObj0(), pair.getObj1(), &depth, &n, coord, coord_)) {
				//衝突していたら衝突情報を記録
				ContactPoint cp;
				cp.depth = depth;
				cp.normal = n;
				cp.pointA = coord[0];
				cp.pointB = coord[1];
				cp.pointA_ = coord_[0];
				cp.pointB_ = coord_[1];
				cp.constraint->accumImpulse = 0.f;
				pair.getCol()->addCp(cp);
			}
			else {
				//衝突していなければ
				erase.push_back(pair.getKey());//キーを記録
			}
			break;
		}
	}
	//衝突していなかったペアを削除
	for (int i = 0; i < erase.size(); i++) {
		for (int j = 0; j < pairs.size(); j++) {
			if (pairs[j].getKey() == erase[i]) {
				pairs.erase(pairs.begin() + j);
			}
		}
	}
	//printfDx("world ペア数%d\n", pairs.size());
}


//拘束の解消
void World::solveConstraints() {
	//全てのペアについて
	Solver::solve(this);
}

//位置の更新
void World::integrate() {
	auto itr = objects.begin();
	bool isErase = false;//オブジェクトが削除されたか
	while (itr != objects.end())
	{
		(*itr)->updatePos(TIME_STEP);
 		if (!(*itr)->isValid())
		{
			itr = objects.erase(itr);
			isErase = true;
			objNum--;
		}
		else
		{
			itr++;
		}
	}
	//削除があったら
	if (isErase) {
		//インデックスの振り直し
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->setIndex(i);
		}
	}
}