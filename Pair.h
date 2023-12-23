#pragma once
#include "Math.h"
#include "Object.h"
#include "Collision.h"

/*
*�y�A�N���X
* �u���[�h�t�F�[�Y����������܂ł͎g�p���Ȃ�
*/
enum Kind : uint16_t {
	CIRCLE_CIRCLE = 0b0000'0000'0000'0001,
	CIRCLE_LINE   = 0b0000'0000'0000'0011,
	CIRCLE_BOX    = 0b0000'0000'0000'0101,
	LINE_LINE     = 0b0000'0000'0000'0010,
	LINE_BOX      = 0b0000'0000'0000'0110,
	BOX_BOX       = 0b0000'0000'0000'0100,
	CONVEX_CONVEX = 0b0000'0000'0000'1000
};

enum PairType {
	New,
	Keep
};

class Pair {
private:
	Object* obj[2];//�I�u�W�F�N�g�ւ̃A�N�Z�X
	Kind kind;//�I�u�W�F�N�g�̑g�ݍ��킹
	PairType type;//�V�K�Ɍ��������y�A��
public:
	Pair();
	Kind getKind()const;
	PairType getType()const;
};