#include "Rand.h"

//シングルトンへのアクセスを返す
Rand* Rand::instance() {
	static Rand instance;
	return &instance;
}

float Rand::get(const float min, const float max) {
	return (float)(min + mt() % ((int)max + 1 - (int)min));
}