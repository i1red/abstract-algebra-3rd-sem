//
// Created by ivan on 03.10.19.
//

#include "BigInt.h"

BigInt::BigInt(const char* strInit="0") {

}

BigInt BigInt::operator+(const BigInt& other) {
    return BigInt(nullptr);
}

BigInt BigInt::operator-(const BigInt& other) {
    return BigInt(nullptr);
}


std::ostream& operator<<(std::ostream& os, const BigInt& ) {
    return os;
}
