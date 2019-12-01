#ifndef ABSTRACT_ALGEBRA_MONTGOMERY_REDUCER_H
#define ABSTRACT_ALGEBRA_MONTGOMERY_REDUCER_H

#include "BigInt/BigInt.h"
#include "ModArithmetic/ModArithmetic.h"

class MontgomeryReducer {
    BigInt modulus;

public:
    explicit MontgomeryReducer(const BigInt &modulus);
    BigInt convertIn(const BigInt &x);
    BigInt convertOut(const BigInt &x);
    BigInt multiply(const BigInt &x, const BigInt &y);
    BigInt pow(BigInt &x, BigInt &y);

    BigInt getModulus();
    BigInt getReducer();
private:
    // Computed numbers
    BigInt reducer;       // Is a power of 2
    BigInt reciprocal;    // Equal to reducer^-1 mod modulus
    BigInt factor;        // Equal to (reducer * reducer^-1 - 1) / modulo
    BigInt convertedOne;

    static std::vector<bool> getBinary(const BigInt& x);

    void setReducer();
};

#endif //ABSTRACT_ALGEBRA_MONTGOMERY_REDUCER_H