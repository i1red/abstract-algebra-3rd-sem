#include "MontgomeryReducer.h"

void MontgomeryReducer::setReducer() {
    BigInt temporary = BigInt::ONE;

    while (temporary < this -> modulus) {
        temporary = temporary * BigInt("2");
    }

    this -> reducer = temporary;
}


BigInt MontgomeryReducer::getModulus() {
    return modulus;
}

BigInt MontgomeryReducer::getReducer() {
    return reducer;
}

MontgomeryReducer::MontgomeryReducer(const BigInt &modulus) {
    this -> modulus = modulus;
    this -> reducer = BigInt::ONE;

    setReducer();

    reciprocal = ModArithmetic<BigInt>::inverseEl(reducer, modulus);
    factor = ((reducer * reciprocal) - BigInt::ONE) / modulus;

    convertedOne = convertIn(BigInt::ONE);
}

BigInt MontgomeryReducer::convertIn(const BigInt &x) {
    return mod((x * reducer), modulus);
}

BigInt MontgomeryReducer::convertOut(const BigInt &x) {
    return mod((x * reciprocal), modulus);
}

BigInt MontgomeryReducer::multiply(const BigInt &x, const BigInt &y) {
    BigInt product = x * y;
    BigInt temp = mod((product * factor), reducer);
    BigInt reduced = product + (temp * modulus);
    BigInt result = reduced / reducer;
    return result < modulus ? result : result - modulus;
}

BigInt MontgomeryReducer::pow(BigInt &x, BigInt &y) {
    if (x < BigInt::ZERO || x >= modulus) { throw MATH_ERREXCEPT; };

    if (y < BigInt::ZERO) { throw MATH_ERREXCEPT; }
    if (y == BigInt::ZERO) { return convertedOne; }

    BigInt number = x;
    BigInt power = convertedOne;

    std::vector<bool> binary = getBinary(y);

    for (int i = 0; i < binary.size(); i++) {
        if (binary[i]) {
            power = multiply(power, number);
        }
        number = multiply(number, number);
    }

    return power;
}

std::vector<bool> MontgomeryReducer::getBinary(const BigInt &x) {
    BigInt temp = x;
    std::vector<bool> binary;

    while(temp != BigInt::ZERO) {
        BigInt two("2");

        binary.insert(binary.begin(), temp % two == BigInt::ZERO ? 0 : 1);
        temp = temp / two;
    }

    return binary;
}