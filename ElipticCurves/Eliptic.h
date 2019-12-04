#pragma once
#include "PT.h"
#include "BigInt/BigInt.h"
#include "ModArithmetic/ModArithmetic.h"
#include <limits>
#include <iostream>
using std::cout;
using std::endl;
class ElipticCurve {
private:

	BigInt a;
	BigInt b;
	BigInt mod;


public:
	ElipticCurve(BigInt a, BigInt b, BigInt mod);

	BigInt get_A();
	BigInt get_B();
	BigInt get_Mod();
	bool isPointOnCurve(PT a);
	PT reversePT(PT a);
    PT ReceivePT(PT temp);

	PT AddPT(PT a, PT b);


};
