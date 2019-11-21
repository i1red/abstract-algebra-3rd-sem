#include "ModArithmetic.h"


ModArithmetic::ModArithmetic(const BigInt& n) {
    this->n_ = n;
}


BigInt ModArithmetic::add(const BigInt& lt, const BigInt& rt) {
    BigInt sum = lt + rt;
    return sum.mod(this->n_);
}


BigInt ModArithmetic::subtract(const BigInt& lt, const BigInt& rt) {
    BigInt difference = lt - rt;
    return difference.mod(this->n_);
}


BigInt ModArithmetic::multiply(const BigInt& lt, const BigInt& rt) {
    BigInt product = lt * rt;
    return product.mod(this->n_);
}


BigInt ModArithmetic::divide(const BigInt& lt, const BigInt& rt) {
    BigInt inverseRt = this->inverseElement(rt);

    if (inverseRt == BigInt("-1")) {
        throw std::logic_error("Division error. Inverse element for right operand doesn't exist");
    }

    return this->multiply(lt, inverseRt);
}


BigInt ModArithmetic::inverseElement(const BigInt& el) {
    BigInt x, y, res;
    BigInt g = gcdex (el, n_, x, y);
    auto n_1 = BigInt("1");

    if (!(g == n_1)) {
        res = BigInt("-1");
    }

    else {
        res = (x % n_ + n_) % n_;
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

BigInt ModArithmetic::n() {
    return this->n_;
}





