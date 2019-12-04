#pragma once
#include "BigInt.h"
#include "ModArithmetic.h"

class PT {
private:
	BigInt x;
	BigInt y;
	bool isInfinite;

public:
	PT(BigInt x, BigInt y) : x(x), y(y){
	
	}

	static PT InfPT() {
		PT temp = PT(BigInt("0"), BigInt("0"));
		temp.isInfinite = true;
		return temp;
	}
	BigInt GetX() {
		return x;
	}

	BigInt GetY() {
		return y;
	}

	bool isInfinitePoint() {
		return isInfinite;
	}

	bool operator == (PT pt) {
		return x == pt.x && y == pt.y;
	}
};





