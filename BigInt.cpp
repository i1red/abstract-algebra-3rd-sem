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

    //count = pos >= 9 ? 9 : pos - start;

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

}

bool BigInt::operator>(const BigInt &other) {
    return false;
}

bool BigInt::operator<(const BigInt &other) {
    return false;
}

int BigInt::numbersOfDigits(int number) const {
    int counter = 1;
    while ((number /= 10) > 0) {
        counter++;
    }

    return counter;
}


std::ostream& operator<<(std::ostream& os, const BigInt& bigInt ) {
    if (!bigInt.positive) {
        os << '-';
    }

    os << bigInt.nums[bigInt.nums.size() - 1];

    for (int i = bigInt.nums.size() - 2; i >= 0; i--) {
        //os << bigInt.nums[i] << " ";

        if (bigInt.numbersOfDigits(bigInt.nums[i]) < 9) {
            for (int j = 0; j < 9 - bigInt.numbersOfDigits(bigInt.nums[i]); j++) {
                os << '0';
            }
        }

        os << bigInt.nums[i];
    }

    /*os << std::endl;

    for (int i = bigInt.nums.size() - 1; i >= 0; i--) {
        os << bigInt.numbersOfDigits(bigInt.nums[i]) << " ";
    }*/

    return os;
}
