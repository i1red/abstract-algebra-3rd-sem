#include "Eliptic.h"
#include "BigInt/BigInt.h"
#include "ModArithmetic/ModArithmetic.h"
#include <iostream>
inline ElipticCurve::ElipticCurve(BigInt a, BigInt b, BigInt mod) :a(a), b(b), mod(mod) {
	BigInt discriminant = BigInt("16") + (BigInt("4") * a * a * a + BigInt("27") * b * b);

	if (discriminant == BigInt("0")) {
		cout << "Discriminant can`t be  0" << endl;;
	}

};

inline BigInt ElipticCurve:: get_A() {
	return a;
}
inline BigInt ElipticCurve::get_B() {
	return b ;
}
inline BigInt ElipticCurve::get_Mod() {
	return mod;
}
inline PT ElipticCurve::ReceivePT(PT temp) {
	BigInt x = temp.GetX();
	BigInt y = temp.GetY();
	return PT(x, y);
}
inline bool ElipticCurve::isPointOnCurve(PT first) {
	first = ReceivePT(first);
	BigInt temp = first.GetX() * first.GetY();
	/*if (first.GetY() * first.GetY() != first.GetX() * first.GetX() * first.GetX() + a * first.GetX() + b)
		return false;*/
	if (first.GetX() >= mod || first.GetY() >= mod)
		return false;

	return true;
}

inline PT ElipticCurve::reversePT(PT temp) {
	temp = ReceivePT(temp);
	if (!isPointOnCurve(temp)) {
		cout << "Some of the points are not on the curve" << endl;
	}
	if(temp.GetY() == 0){

	}
	return PT(temp.GetX(), -temp.GetY());
}



inline PT ElipticCurve::AddPT(PT A, PT B)
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
BigInt ElipticCurve::BabyGiantStep() {
	P = 1;
	PT Q = fastpow(P, mod + 1);
	BigInt m = sqrt1(sqrt1(mod)), j, k;
	BigInt jP = new BigInt[m];
	for (BigInt i = 0; i < m; i++)
		jP = fastpow(P, i);
	PT cur = fastpow(P, 2 * m);
	for (k = -m; k < m; i++) {
		PT temp = Q + fastpow(cur, k); // Q+(k+1)2mP = Q + k2mP + 2mP;
		for (j = 0; j < m; i++) {
			if (temp == jP[j]) {
				j = -j;
				break;
			}
			else(temp = -jP[j]) {
				break;
			}
		}
	}
	if (pow1(P, mod + 1 + 2 * m * k + j).isInfinitePoint()) {
		BigInt M = mod + 1 + 2 * m * k + j;
	}
	std::vector<BigInt> primeFactors = PollardRecursiv(M);
	size_t sizeVector = primeFactors.size();
	BigInt tempM;
	for (int i = 1; i < sizeVector; i++) {
		tempM = M / primeFactors[i];
		if (pow(P, tempM).isInfinitePoint()) {
			primeFactors = PollardRecursiv(tempM);
			sizeVector = primeFactors.size();
			i = 0;
		}
	}
	return temp;
}
BigInt lcm(BigInt a, BigInt b) {
	return (a * b) / hsf(a, b);
}
BigInt ElipticCurve::BabyGiantStepGroup() {
	BigInt order, right, left, temp_lcm = 1;
	left = mod + 1 - 2 * sqrt(mod);
	right = mod + 1 + 2 * sqrt(mod);
	while (temp_lcm <= left) {
		order = BabyGiantStep();
		points_order.push_back(order);
		temp_lcm = lcm(temp_lcm, order);
		if (temp_lcm > right) return 0;
	}
	if (temp_lcm > right) return 0;
	return temp_lcm;
}

PT ElipticCurve::fastpow(PT A, BigInt k) {
	BigInt a = k;
	PT B, C = A;
	while (a != 0) {
		if (a % 2 == 0) {
			a = a / 2;
			C = AddPT(C, C);
		}
		else {
			a = a - 1;
			B = AddPT(B, C);
		}
	}
	return B;
}


std::vector<BigInt> PollardRecursiv(BigInt n) {
	std::vector<BigInt> result;
	d = Pollard(n);
	while (d != n) {
		n = n / d;
		result.push_back(d);
		d = Pollard(n);
	}

}

BigInt hcf(BigInt n1, BigInt n2)
{
	if (n2 != 0)
		return hcf(n2, n1 % n2);
	else
		return n1;
}

BigInt Pollard(BigInt n) {
	BigInt a = 2, b = 2;
	BigInt d;
	while (1) {
		a = (a * a + 1) % n;
		b = (b * b + 1) % n;
		b = (b * b + 1) % n;
		d = hcf(a - b, n);
		if (d < n && d > 1) return d;
		if (d == n) return d;
	}
}
BigInt find(BigInt n, BigInt div, std::vector<BigInt> & result)
{
	if (n == 1) return;
	if (n % div == 0)
	{
		result.push_back(div);
		find(n / div, div);
	}
	else
		if (div == 2)
			find(n, div + 1);
		else
			find(n, div + 2);
}



