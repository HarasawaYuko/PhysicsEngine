#pragma once
#include <random>

//�����N���X

class Rand {
private:
	std::random_device rd;
	std::mt19937 mt;
public:
	static Rand* instance();
	float get(const float , const float);
};