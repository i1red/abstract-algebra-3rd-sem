#include <iostream>

#include "Generator_of_G/Gen_of_G.h"

using namespace std;

BigInt small_pow(const BigInt& a, BigInt n) {
  BigInt ret = BigInt::ONE;
  while (n != BigInt::ZERO) {
    ret = ret * a;
    n = n - BigInt::ONE;
  }
  return ret;
}

BigInt smod_pow(ModArithmetic<BigInt>& M,
    const BigInt& a, BigInt n) {
  BigInt ret = BigInt::ONE;
  while (n != BigInt::ZERO) {
    ret = M.ringMultiply(ret, a);
    n = n - BigInt::ONE;
  }
  return ret;
}

BigInt order(const BigInt& mod,
    const BigInt& n, const BigInt& a) {
  factorization f = factorize_naive(n);
  ModArithmetic<BigInt> M(mod);

  BigInt t = n;
  for (int i = 0; i < f.p.size(); i++) {
    t = t / small_pow(f.p[i], f.e[i]);
    BigInt a1 = smod_pow(M, a, t);
    while (a1 != BigInt::ONE) {
      a1 = smod_pow(M, a1, f.p[i]);
      t = t * f.p[i];
    }
  }

  return t;
}

int main() {
  cout << "hello world" << endl;

  cout << "G={1, 2, 3, 4, 5, 6}, mod 7" << endl;
  cout << "ord(1) = ";
  cout << order(BigInt("7"), BigInt("6"), BigInt("1")) << endl;
  cout << "ord(2) = ";
  cout << order(BigInt("7"), BigInt("6"), BigInt("2")) << endl;
  cout << "ord(3) = ";
  cout << order(BigInt("7"), BigInt("6"), BigInt("3")) << endl;
  cout << "ord(4) = ";
  cout << order(BigInt("7"), BigInt("6"), BigInt("4")) << endl;
  cout << "ord(5) = ";
  cout << order(BigInt("7"), BigInt("6"), BigInt("5")) << endl;
  cout << "ord(6) = ";
  cout << order(BigInt("7"), BigInt("6"), BigInt("6")) << endl;

  return 0;
}
