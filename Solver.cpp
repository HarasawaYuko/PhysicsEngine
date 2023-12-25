#include "Solver.h"

static const float e_CC = 0.8f; //円と円の反発係数
static float k_CC;//バネ係数

//プロトタイプ宣言
Matrix getRtilda(const Vec2&);

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
			Vec2 vB = Vec2();
			//並進速度を計算
			vA = vA + objA->getV();
			vB = vB + objB->getV();
			//回転速度を計算
			vA = vA + objA->getCirV(cp.pointA);
			vB = vB + objB->getCirV(cp.pointB);
			//相対速度
			Vec2 Vab = vA - vB;

			//行列Kを計算
			Matrix K = Matrix(2, 2);
			float mSum = 1.f / objA->getM() + 1.f / objB->getM();
			Matrix mMat = Matrix(2 , 2);
			mMat.identity();
			K = K + (mMat * mSum);
			Matrix rAmat = getRtilda(cp.pointA) * (1.f/objA->getI());
			Matrix rBmat = getRtilda(cp.pointB) * (1.f/objB->getI());
			K = (K - rAmat) - rBmat;
		}
	}

	delete[] solverBodies;
}

Matrix getRtilda(const Vec2& r) {
	Matrix mat = Matrix(2 ,2);
	mat.matrix[0][0] = r.y * r.y;
	mat.matrix[1][0] = -1 * r.y * r.x;
	mat.matrix[0][1] = -1 * r.y * r.x;
	mat.matrix[1][1] = r.x * r.x;
	return mat;
}