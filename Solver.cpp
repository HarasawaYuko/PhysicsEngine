#include "Solver.h"
#include "Pair.h"

static const float e_CC = 0.8f; //�~�Ɖ~�̔����W��
static float k_CC;//�o�l�W��
static float bias = 0.5f;//�S����f��bias

//�v���g�^�C�v�錾
Matrix getRtilda(const Vec2&);

void Solver::initialize(const float timeStep) {
	k_CC = (float)(1 / (timeStep));
}

bool Solver::circle_line(Collision &col) {
	//Circle* cir = static_cast<Circle*>(col.getObj1());
	//Line* line = static_cast<Line*>(col.getObj2());
	////���Α��x���擾
	//Vec2 V12 = Vec2(line->getV().x - cir->getV().x, line->getV().y - cir->getV().y);
	////���Α��x�̖@������
	//float V12_n = V12.dot(col.getN());
	////���͂̌W�������߂�
	//float c;
	//if (V12.dot(col.getN()) > 0) {
	//	c = -cir->getM()/2 * ((col.getE() + 1) * (k_CC * col.getD()));
	//}
	//else {
	//	c = cir->getM()/2 * ((col.getE() + 1) * (V12.dot(col.getN()) - k_CC * col.getD()));
	//}
	////���x�̕ύX
	//cir->addV(col.getN() * (c / cir->getM()));
	//line->addV(col.getN() * (-c / line->getM()));
	return true;
}

bool Solver::circle_circle(Collision &col ) {
	//Circle* cir1 = static_cast<Circle*>(col.getObj1());
	//Circle* cir2 = static_cast<Circle*>(col.getObj2());
	////���Α��x���擾
	//Vec2 V12 = Vec2(cir2->getV().x - cir1->getV().x , cir2->getV().y - cir1->getV().y);
	////���Α��x�̖@������
	//float V12_n = V12.dot(col.getN());
	////���͂̌W�������߂�
	//float c;
	//if (V12.dot(col.getN()) > 0) {
	//	c = ((cir1->getM() * cir2->getM()) / (cir1->getM() + cir2->getM()))*(-k_CC * col.getD());
	//}
	//else {
	//	c = ((cir1->getM() * cir2->getM()) / (cir1->getM() + cir2->getM()))*((1+col.getE())*V12_n - k_CC * col.getD());
	//}
	////���x�̕ύX
	//cir1->addV(col.getN()*(c/cir1->getM()));
	//cir2->addV(col.getN() * (-c / cir2->getM()));
	return true;
}

void Solver::solve(const std::vector<Object*>& objects ,std::vector<Collision>& cols) {
	//�\���o�[�{�f�B���쐬
	SolverBody* solverBodies;
	solverBodies = new SolverBody[objects.size()];
	for (int i = 0; i < objects.size(); i++) {
		Object* obj = objects[i];
		if (obj->isActive()) {
			solverBodies[i] = SolverBody(obj->getAngle(), 1.f/obj->getM(), 1.f/obj->getI());
		}
		else {
			//�����Ȃ����̂� m,I = ���Ƃ��Čv�Z
			solverBodies[i] = SolverBody(obj->getAngle(), 0 ,0);
		}
	}


	//�S����ݒ�
	for (int i = 0; i < cols.size(); i++) {
		//�v���L�V���쐬
		Collision& col = cols[i];//�Փ�

		Object* objA = cols[i].getObj1();
		SolverBody bobyA = solverBodies[objA->getIndex()];
		Object* objB = cols[i].getObj2();
		SolverBody bodyB = solverBodies[objB->getIndex()];

		//���C�W���ƒ��˕Ԃ�W���̐ݒ�
		col.setFri(sqrt(objA->getFri() * objB->getFri()));
	
		//���˕Ԃ�W���͐V�K�Ɍ��o���ꂽ�Փ˂݂̂ɓK�p
		float restitution;
		if (true/*�Ƃ肠���������W���͂Ȃ�*/) {
			restitution = 0.f;
		}
		else {
			restitution = 0.5f * (objA->getE() + objB->getE());
		}

		for (int j = 0; j < col.getContactNum(); j++) {
			ContactPoint& cp = col.getCp(j);

			//���Α��x(���[���h���W)���v�Z
			Vec2 vA = Vec2();//���[���h���W�ł̏Փ˓_�ɒu���鑬�x
			Vec2 vB = Vec2();
			//���i���x���v�Z
			vA = vA + objA->getV();
			vB = vB + objB->getV();
			//��]���x���v�Z
			vA = vA + objA->getCirV(cp.pointA);
			vB = vB + objB->getCirV(cp.pointB);
			//���Α��x
			Vec2 Vab = vA - vB;
/*���Α��x�擾�m�F*/

			//�s��K���v�Z
			Matrix K = Matrix(2, 2);
			float mSum = 1.f / objA->getM() + 1.f / objB->getM();
			Matrix mMat = Matrix(2 , 2);
			mMat.identity();
			K = K + (mMat * mSum);
			Matrix rAmat = getRtilda(cp.pointA) * (1.f/objA->getI());
			Matrix rBmat = getRtilda(cp.pointB) * (1.f/objB->getI());
			K = (K - rAmat) - rBmat;

			/*�S���̃Z�b�g�A�b�v*/
			//�S�������擾
			Vec2 axis = cp.normal;
			//�S�����̕���
			Matrix axis_ = Matrix(axis);
			Matrix denom_ = (K.product(axis_)).trans().product(axis_);
			assert(denom_.row == 1 && denom_.column == 1);//�f�o�b�O�p�@�P�s�ɏ���������
			float denom = denom_.matrix[0][0];
/*denom != 0*/
			//���������̍S�����Z�b�g
			cp.constraint[0].denomInv = 1.f / denom;
			cp.constraint[0].f = -(1.0f + restitution) * Vab.dot(axis);//���x�␳(f�̕���)
			//printfDx("f1 %f\n" , cp.constraint[0].f);
			cp.constraint[0].f -= (bias * min(0.0f , cp.depth))/(1.f/(float)FPS);//�ʒu�␳ �߂荞�݉����p
			//printfDx("f2 %f\n", cp.constraint[0].f);
			cp.constraint[0].f *= cp.constraint[0].denomInv;//�����������
			//printfDx("f3 %f\n", cp.constraint[0].f);
			//�S���͂̍ő�l�ƍŏ��l��ݒ�
			cp.constraint[0].lowerF = 0.0f;
			cp.constraint[0].upperF = FLT_MAX;
			//���C�͂��Z�b�g
			//��U�p�X
		}
	}

	/*�S���̉��Z*/
	for (int i = 0; i < cols.size(); i++) {
		Collision& col = cols[i];
		Object* objA = cols[i].getObj1();
		SolverBody& bodyA = solverBodies[objA->getIndex()];
		Object* objB = cols[i].getObj2();
		SolverBody& bodyB = solverBodies[objB->getIndex()];
		for (int j = 0; j < col.getContactNum() ; j++) {
			ContactPoint& cp = col.getCp(j);
			Constraint& constraint = cp.constraint[0];
			float deltaImpulse = constraint.f;//���͂��擾
			Vec2 deltaVelocityA = bodyA.deltaLinearV + getVang(cp.pointA , bodyA.deltaRotaV);;//A�̑��x�ω���
			Vec2 deltaVelocityB = bodyB.deltaLinearV + getVang(cp.pointB, bodyB.deltaRotaV);//B�̑��x�ω���
			//�S���͂��Z�o
			deltaImpulse -= constraint.denomInv * constraint.axis.dot(deltaVelocityA - deltaVelocityB);
/*deltaImpulse != 0 �m�F*/
			//�S���͂��N�����v
			clamp(deltaImpulse , constraint.lowerF , constraint.upperF);
			
			//�X�V���鑬�x���v�Z
			bodyA.deltaLinearV = bodyA.deltaLinearV +  (constraint.axis * (deltaImpulse * bodyA.massInv));
			//printfDx("bodyA LV %s\n", bodyA.deltaLinearV.toString().c_str());
			bodyA.deltaRotaV += deltaImpulse * bodyA.inertiaInv;
			bodyB.deltaLinearV = bodyB.deltaLinearV - (constraint.axis * (deltaImpulse * bodyB.massInv));
			bodyB.deltaRotaV -= deltaImpulse * bodyB.inertiaInv;
			//���C�͂ɂ�鑬�x�ω��v�Z
		} 
	}
	//���x���X�V
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->addV(solverBodies[i].deltaLinearV / (float)FPS);
		objects[i]->addVang(solverBodies[i].deltaRotaV /(float)FPS);
	}
	delete[] solverBodies;
}

void Solver::solve(World* world) {
	//�\���o�[�{�f�B���쐬
	std::vector<Object*> objects = world->objects;
	std::vector<Pair>& pairs = world->pairs;
	SolverBody* solverBodies;
	solverBodies = new SolverBody[objects.size()];
	//printfDx("v %s\n" , objects[1]->getV().toString().c_str());
	for (int i = 0; i < objects.size(); i++) {
		Object* obj = objects[i];
		//printfDx("mass %f\n" ,obj->getM());
		if (obj->isActive()) {
			solverBodies[i] = SolverBody(obj->getAngle(), 1.f / obj->getM(), 1.f / obj->getI());
		}
		else {
			//�����Ȃ����̂� m,I = ���Ƃ��Čv�Z
			solverBodies[i] = SolverBody(obj->getAngle(), 0, 0);
		}
		solverBodies[i].deltaLinearV = Vec2();
		solverBodies[i].deltaRotaV = 0.f;
		//printfDx("�ݒ�� %s\n", solverBodies[i].toString().c_str());
	}
/*solver body �m�F*/
	//�S����ݒ�
	for (int i = 0; i < pairs.size(); i++) {
		//�v���L�V���쐬
		Pair& pair = pairs[i];
		Collision* col = pair.getCol();//�Փ�

		Object* objA = pair.getObj0();
		SolverBody bodyA = solverBodies[objA->getIndex()];
		Object* objB = pair.getObj1();
		SolverBody bodyB = solverBodies[objB->getIndex()];

		//���C�W���ƒ��˕Ԃ�W���̐ݒ�
		col->setFri(sqrt(objA->getFri() * objB->getFri()));
		//���˕Ԃ�W���͐V�K�Ɍ��o���ꂽ�Փ˂݂̂ɓK�p
		float restitution;
		if (pair.getType() == Keep) {
			restitution = 0.f;
		}
		else {
			//printfDx("B�̔����W�� %f\n" , objB->getE());
			restitution = 0.5f * (objA->getE() + objB->getE());
		}

		for (int j = 0; j < col->getContactNum(); j++) {
			ContactPoint& cp = col->getCp(j);

			//���Α��x(���[���h���W)���v�Z
			Vec2 vA = Vec2();//���[���h���W�ł̏Փ˓_�ɒu���鑬�x
			Vec2 vB = Vec2();
			//���i���x���v�Z
			vA = vA + objA->getV();
			vB = vB + objB->getV();
			//��]���x���v�Z
			vA = vA + (objA->getCirV(cp.pointA ) );
			vB = vB + (objB->getCirV(cp.pointB ) );
			//printfDx("��]���x�@%s\n", objB->getCirV(cp.pointB).toString().c_str());
			//printfDx("�Փ˓_�̑��x %s\n",vB.toString().c_str());
			//printfDx("B�̎���%f\n", objB->getM());

			//���Α��x
			Vec2 Vab = vA - vB;
			/*���Α��x�擾�m�F*/
			//printfDx("���Α��x %s\n", Vab.toString().c_str());
			//�s��K���v�Z
			Vec2 rA = cp.pointA.rotation(objA->getAngle());
			Vec2 rB = cp.pointB.rotation(objB->getAngle());
			//printfDx("rB %s\n" , rB.toString().c_str());
			//printfDx("rB %s\n", rB.toString().c_str());
			Matrix K = Matrix(2, 2);
			float mSum = bodyA.massInv + bodyB.massInv;
			Matrix mMat = Matrix(2, 2);
			mMat.identity();
			K = K + (mMat * mSum);
			//printfDx("K(mSum)\n%s\n", K.toString().c_str());
			Matrix rAmat = getRtilda(rA) * (bodyA.inertiaInv);
			Matrix rBmat = getRtilda(rB) * (bodyB.inertiaInv);
			//printfDx("Iinv %1.9f\n" , bodyB.inertiaInv);
			//printfDx("rBmat\n%s\n", getRtilda(rB).toString().c_str());
			K = (K + rAmat) + rBmat;
			//printfDx("K \n %s\n" , K.toString().c_str());

/******�S���̃Z�b�g�A�b�v******/
			{
				//�S�������擾
				Vec2 axis = cp.normal;
				//printfDx("axis %s\n" ,axis.toString().c_str());
				//�S�����̕���
				Matrix axis_ = Matrix(axis);
				//printfDx("axis_ %s\n" , axis_.toString().c_str());
				Matrix denom_ = (K.product(axis_)).trans().product(axis_);
				float denom = denom_.matrix[0][0];//����
				//printfDx("����%f \n" , denom);
				//���������̍S�����Z�b�g
				cp.constraint[0].denomInv = 1.f / denom;
				//printfDx("����t��%f \n", cp.constraint[0].denomInv);
				cp.constraint[0].f = -(1.0f + restitution) * Vab.dot(axis);//���x�␳(f�̕���)
				//printfDx("�����W�� %f\n" , restitution);
				//printfDx("���Α��x����%f \n", Vab.dot(axis));
				//printfDx("f:%f \n", cp.constraint[0].f);
				cp.constraint[0].f -= (bias * min(0.0f, cp.depth + 0.1f )) / (1.f / (float)FPS);//�ʒu�␳ �߂荞�݉����p
				//printfDx("�ђʐ[�x %f\n" , cp.depth);
				//printfDx("f:%f \n", cp.constraint[0].f);
				cp.constraint[0].f *= cp.constraint[0].denomInv;//�����������
				//printfDx("f:%f \n", cp.constraint[0].f);
				//�S���͂̍ő�l�ƍŏ��l��ݒ�
				cp.constraint[0].lowerF = 0.0f;
				cp.constraint[0].upperF = FLT_MAX;
				cp.constraint[0].axis = axis;
			}
			{
				//printfDx("���C---\n");
				//���C�͂��Z�b�g
				Vec2 axis = cp.normal.normal();
				//printfDx("axis %s\n", axis.toString().c_str());
				//�S�����̕���
				Matrix axis_ = Matrix(axis);
				Matrix denom_ = (K.product(axis_)).trans().product(axis_);
				float denom = denom_.matrix[0][0];
				//printfDx("����%f \n", denom);
				cp.constraint[1].denomInv = 1.f / denom;
				//printfDx("����t��%f \n", cp.constraint[1].denomInv);
				cp.constraint[1].f = -Vab.dot(axis);       
				//printfDx("���Α��x����%f \n", Vab.dot(axis));
				//printfDx("f:%f \n", cp.constraint[1].f);
				cp.constraint[1].f *= cp.constraint[1].denomInv;//�����������
				//printfDx("f:%f \n", cp.constraint[1].f);
				cp.constraint[1].axis = axis;
			}
		}
	}

/********�S���̉��Z*******/
	//printfDx("-------------���Z---------------\n");
	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < pairs.size(); i++) {
			Collision* col = pairs[i].getCol();
			Object* objA = pairs[i].getObj0();
			SolverBody& bodyA = solverBodies[objA->getIndex()];
			Object* objB = pairs[i].getObj1();
			SolverBody& bodyB = solverBodies[objB->getIndex()];
			for (int j = 0; j < col->getContactNum(); j++) {
				ContactPoint& cp = col->getCp(j);
				Vec2 rA = cp.pointA.rotation(bodyA.angle);
				Vec2 rB = cp.pointB.rotation(bodyB.angle);
				{//��������
					Constraint& constraint = cp.constraint[0];
					//printfDx("accume %f\n", constraint.accumImpulse);
					float deltaImpulse = constraint.f;//���͂��擾
					//printfDx("delta %f\n" , deltaImpulse);
					Vec2 deltaVelocityA = bodyA.deltaLinearV + getVang(cp.pointA, bodyA.deltaRotaV).rotation(objA->getAngle());//A�̑��x�ω���
					Vec2 deltaVelocityB = bodyB.deltaLinearV + getVang(cp.pointB, bodyB.deltaRotaV).rotation(objB->getAngle());//B�̑��x�ω���
					//�S���͂��Z�o
					deltaImpulse -= constraint.denomInv * constraint.axis.dot(deltaVelocityA - deltaVelocityB);
					//printfDx("�f���^����(����)%f \n" , constraint.axis.dot(deltaVelocityA - deltaVelocityB));
					//printfDx("�f���^ %f\n", deltaImpulse);
					float oldImpulse = constraint.accumImpulse;
					//printfDx("old %f\n", oldImpulse);
					constraint.accumImpulse = clamp(oldImpulse + deltaImpulse , constraint.lowerF , constraint.upperF);
					//printfDx("accume %f  old %f\n", constraint.accumImpulse, oldImpulse);
					deltaImpulse = constraint.accumImpulse - oldImpulse;
					//�X�V���鑬�x���v�Z
					bodyA.deltaLinearV = bodyA.deltaLinearV + (constraint.axis * (deltaImpulse * bodyA.massInv));
					bodyA.deltaRotaV += (rA.cross(constraint.axis * deltaImpulse)) * bodyA.inertiaInv;
					bodyB.deltaLinearV = bodyB.deltaLinearV - (constraint.axis * (deltaImpulse * bodyB.massInv));
					bodyB.deltaRotaV -= (rB.cross(constraint.axis * deltaImpulse)) * bodyB.inertiaInv;
					//printfDx("����deltaV %s\n", bodyB.deltaLinearV.toString().c_str(), bodyB.deltaRotaV);
				}
				float maxFriction = col->getFri() * abs(cp.constraint[0].accumImpulse);
				cp.constraint[1].lowerF = -maxFriction;
				cp.constraint[1].upperF = maxFriction;
				{//���C�͂̍S�����Z
					//���C�͂ɂ�鑬�x�ω��v�Z
					Constraint constraint = cp.constraint[1];
					float deltaImpulse = constraint.f;//���͂��擾
					Vec2 deltaVelocityA = bodyA.deltaLinearV + getVang(cp.pointA, bodyA.deltaRotaV).rotation(objA->getAngle());//A�̑��x�ω���
					Vec2 deltaVelocityB = bodyB.deltaLinearV + getVang(cp.pointB, bodyB.deltaRotaV).rotation(objB->getAngle());//B�̑��x�ω���
					//�S���͂��Z�o
					deltaImpulse -= constraint.denomInv * (constraint.axis.dot(deltaVelocityA - deltaVelocityB));
					/*printfDx("�f���^���i%s\n" , bodyB.deltaLinearV.toString().c_str());
					printfDx("delta���Α��x%s\n" , (deltaVelocityA - deltaVelocityB).toString().c_str());
					printfDx("�f���^����(���C)%f \n", constraint.axis.dot(deltaVelocityA - deltaVelocityB));*/
					float oldImpulse = constraint.accumImpulse;
					constraint.accumImpulse = clamp(oldImpulse + deltaImpulse , constraint.lowerF , constraint.upperF);
					deltaImpulse = constraint.accumImpulse - oldImpulse;
					//�X�V���鑬�x���v�Z
					bodyA.deltaLinearV = bodyA.deltaLinearV + (constraint.axis * (deltaImpulse * bodyA.massInv));
					bodyA.deltaRotaV += (rA.cross(constraint.axis * deltaImpulse)) * bodyA.inertiaInv;
					bodyB.deltaLinearV = bodyB.deltaLinearV - (constraint.axis * (deltaImpulse * bodyB.massInv));
					bodyB.deltaRotaV -= (rB.cross(constraint.axis * deltaImpulse)) * bodyB.inertiaInv;
					//printfDx("���CdeltaV %s \n", bodyB.deltaLinearV.toString().c_str(), bodyB.deltaRotaV);
				}
			}
		}
	}

	//���x���X�V
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->addV(solverBodies[i].deltaLinearV);
		objects[i]->addVang(solverBodies[i].deltaRotaV);
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