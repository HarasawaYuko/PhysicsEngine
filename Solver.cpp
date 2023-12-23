#include "Solver.h"

static const float e_CC = 0.8f; //円と円の反発係数
static float k_CC;//バネ係数

void Solver::initialize(const float timeStep) {
	k_CC = (float)(1 / (timeStep));
}

bool Solver::circle_line(Collision &col) {
	//Circle* cir = static_cast<Circle*>(col.getObj1());
	//Line* line = static_cast<Line*>(col.getObj2());
	////相対速度を取得
	//Vec2 V12 = Vec2(line->getV().x - cir->getV().x, line->getV().y - cir->getV().y);
	////相対速度の法線成分
	//float V12_n = V12.dot(col.getN());
	////撃力の係数を求める
	//float c;
	//if (V12.dot(col.getN()) > 0) {
	//	c = -cir->getM()/2 * ((col.getE() + 1) * (k_CC * col.getD()));
	//}
	//else {
	//	c = cir->getM()/2 * ((col.getE() + 1) * (V12.dot(col.getN()) - k_CC * col.getD()));
	//}
	////速度の変更
	//cir->addV(col.getN() * (c / cir->getM()));
	//line->addV(col.getN() * (-c / line->getM()));
	return true;
}

bool Solver::circle_circle(Collision &col ) {
	//Circle* cir1 = static_cast<Circle*>(col.getObj1());
	//Circle* cir2 = static_cast<Circle*>(col.getObj2());
	////相対速度を取得
	//Vec2 V12 = Vec2(cir2->getV().x - cir1->getV().x , cir2->getV().y - cir1->getV().y);
	////相対速度の法線成分
	//float V12_n = V12.dot(col.getN());
	////撃力の係数を求める
	//float c;
	//if (V12.dot(col.getN()) > 0) {
	//	c = ((cir1->getM() * cir2->getM()) / (cir1->getM() + cir2->getM()))*(-k_CC * col.getD());
	//}
	//else {
	//	c = ((cir1->getM() * cir2->getM()) / (cir1->getM() + cir2->getM()))*((1+col.getE())*V12_n - k_CC * col.getD());
	//}
	////速度の変更
	//cir1->addV(col.getN()*(c/cir1->getM()));
	//cir2->addV(col.getN() * (-c / cir2->getM()));
	return true;
}

void Solver::solve(const std::vector<Object*>& objects ,std::vector<Collision>& cols) {
	//ソルバーボディを作成
	SolverBody* solverBodies;
	solverBodies = new SolverBody[objects.size()];
	for (int i = 0; i < objects.size(); i++) {
		Object* obj = objects[i];
		if (obj->isActive()) {
			solverBodies[i] = SolverBody(obj->getAngle(), 1.f/obj->getM(), 1.f/obj->getI());
		}
		else {
			//動かない物体は m,I = ∞として計算
			solverBodies[i] = SolverBody(obj->getAngle(), 0 ,0);
		}
	}

	//拘束を設定
	for (int i = 0; i < cols.size(); i++) {
		//プロキシを作成
		const Collision& col = cols[i];//衝突

		Object* objA = cols[i].getObj1();
		SolverBody bobyA = solverBodies[objA->getIndex()];
		Object* objB = cols[i].getObj2();
		SolverBody bodyB = solverBodies[objB->getIndex()];

		for (int j = 0; j < col.getContactNum(); j++) {
			ContactPoint cp = col.getCp(j);

			//相対速度(ワールド座標)を計算
			Vec2 vA = Vec2();//ワールド座標での衝突点に置ける速度
			//並進速度を計算
			vA = vA + objA->getV();
			//回転速度を計算
			//float rotaV = cp.pointA.norm() * objA->getAngV();//大きさ
			//if (objA->getAngV() > 0) {
			//	//向きを決定
			//}
			//else {

			//}
		}
	}

	delete[] solverBodies;
}