#include "Eliptic.h"
#include "ModArithmetic.h"
#include <iostream>
ElipticCurve::ElipticCurve(BigInt a, BigInt b, BigInt mod) :a(a), b(b), mod(mod) {
	BigInt discriminant = BigInt("16") + (BigInt("4") * a * a * a + BigInt("27") * b * b);

	if (discriminant == BigInt("0")) {
		cout << "Discriminant can`t be  0" << endl;;
	}

};

BigInt ElipticCurve:: get_A() {
	return a;
}
BigInt ElipticCurve::get_B() {
	return b ;
}
BigInt ElipticCurve::get_Mod() {
	return mod;
}
PT ElipticCurve::ReceivePT(PT temp) {
	BigInt x = temp.GetX();
	BigInt y = temp.GetY();
	return PT(x, y);
}
bool ElipticCurve::isPointOnCurve(PT first) {
	first = ReceivePT(first);
	BigInt temp = first.GetX() * first.GetY();
	/*if (first.GetY() * first.GetY() != first.GetX() * first.GetX() * first.GetX() + a * first.GetX() + b)
		return false;*/
	if (first.GetX() >= mod || first.GetY() >= mod)
		return false;

	return true;
}

PT ElipticCurve::reversePT(PT temp) {
	temp = ReceivePT(temp);
	if (!isPointOnCurve(temp)) {
		cout << "Some of the points are not on the curve" << endl;
	}
	if(temp.GetY() == 0){

	}
	return PT(temp.GetX(), -temp.GetY());
}



PT ElipticCurve::AddPT(PT A, PT B)
{
	A = ReceivePT(A);
	B = ReceivePT(B);

	if (A.isInfinitePoint())
		return B;

	if (B.isInfinitePoint())
		return A;

	if (!isPointOnCurve(A) || !isPointOnCurve(B)) {
		cout << "Some of the points are not on the curve" << endl;
	}

	//A+(-A)=O
	if (A == reversePT(B)) {
		return PT::InfPT();
	}
    ModArithmetic <BigInt> tem = ModArithmetic<BigInt>(mod);
	BigInt lambda("0");
	if (A.GetX() == B.GetX()) {
		lambda = ((BigInt("3") * A.GetX() * A.GetX() + a) / (BigInt("2") * A.GetY()))%mod;
	}
	else {
        BigInt t=(B.GetY() - A.GetY());
        BigInt g= (B.GetX() - A.GetX());
                //lambda = (B.GetY() - B.GetY()) / (B.GetX() - A.GetX());

             lambda  =  tem.divide(t,g,mod);
	}

	BigInt x = lambda * lambda - A.GetX() - B.GetX();
    BigInt y = lambda * (A.GetX() - x) - A.GetY();
    BigInt z;
    if ( y < BigInt("0")) {
       z = mod - (-y % mod);
   }


    return PT(x, z);
}



