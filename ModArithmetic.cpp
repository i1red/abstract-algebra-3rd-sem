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
    return BigInt();
}


BigInt ModArithmetic::inverseElement(const BigInt& el) {
    return BigInt();
}





