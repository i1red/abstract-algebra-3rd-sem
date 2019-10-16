//
// Created by ivan on 03.10.19.
//

#include "BigInt.h"

BigInt::BigInt(const std::string& init) {
    this->positive = init[0] != '-';
    int start = this->positive ? 0 : 1;

    int pos = init.size() - start > 9 ? (int)init.size() - 9 : start;
    int count = pos == start ? (int)init.size() - start : 9;

    while (pos > start)
    {
        this->nums.push_back(std::stoi(init.substr(pos, count)));
        count = pos >= 9 ? 9 : pos - start;
        pos = pos >= 9 ? pos - 9 : start;
    }

    this->nums.push_back(std::stoi(init.substr(pos, count)));
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
