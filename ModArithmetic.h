#ifndef ABSTRACT_ALGEBRA_MODARITHMETIC_H
#define ABSTRACT_ALGEBRA_MODARITHMETIC_H

#include "BigInt.h"

class ModArithmetic {
    BigInt n;

public:
    explicit ModArithmetic(const BigInt&);
    BigInt add(const BigInt&, const BigInt&);
    BigInt subtract(const BigInt&, const BigInt&);
    BigInt multiply(const BigInt&, const BigInt&);
    BigInt divide(const BigInt&, const BigInt&);
    BigInt inverseElement(const BigInt&);
    BigInt gcdex(const BigInt&, const BigInt&, BigInt&, BigInt&);
};


#endif //ABSTRACT_ALGEBRA_MODARITHMETIC_H
