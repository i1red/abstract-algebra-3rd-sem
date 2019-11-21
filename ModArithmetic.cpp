#include "ModArithmetic.h"


ModArithmetic::ModArithmetic(const BigInt& n) {
    this->n = n;
}


BigInt ModArithmetic::add(const BigInt& lt, const BigInt& rt) {
    BigInt sum = lt + rt;
    return sum.mod(this->n);
}


BigInt ModArithmetic::subtract(const BigInt& lt, const BigInt& rt) {
    BigInt difference = lt - rt;
    return difference.mod(this->n);
}


BigInt ModArithmetic::multiply(const BigInt& lt, const BigInt& rt) {
    BigInt product = lt * rt;
    return product.mod(this->n);
}


BigInt ModArithmetic::divide(const BigInt& lt, const BigInt& rt) {
    return this->multiply(lt, this->inverseElement(rt));
}


BigInt ModArithmetic::inverseElement(const BigInt& el) {
    BigInt x, y, res;
    BigInt g = gcdex (el, n, x, y);
    auto n_1 = BigInt("1");

    if (!(g == n_1)) {
        res = BigInt("-1");
    }

    else {
        res = (x % n + n) % n;
    }

    return res;
}


BigInt ModArithmetic::gcdex(const BigInt &lt, const BigInt &rt, BigInt &x, BigInt &y) {
    auto n_0 = BigInt("0");

    if (lt == n_0) {
        x = BigInt("0");
        y = BigInt("1");

        return rt;
    }

    BigInt x1, y1;

    BigInt d = gcdex(rt % lt, lt, x1, y1);

    x = y1 - (rt / lt) * x1;
    y = x1;

    return d;
}





