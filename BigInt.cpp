//
// Created by ivan on 03.10.19.
//

#include "BigInt.h"

BigInt::BigInt(std::string init = "0") {

}

BigInt BigInt::operator+(const BigInt& other) {
    return BigInt(nullptr);
}

BigInt BigInt::operator-(const BigInt& other) {
    return BigInt(nullptr);
}

BigInt BigInt::add(const BigInt &other) {
    return BigInt(nullptr);
}

BigInt BigInt::subtract(const BigInt &other) {
    return BigInt(nullptr);
}

bool BigInt::operator>(const BigInt &other) {
    return false;
}


std::ostream& operator<<(std::ostream& os, const BigInt& ) {
    return os;
}
