#include "BigInt.h"

BigInt::BigInt(const std::string& init) {
    this->nonNegative = init[0] != '-';
    int start = this->nonNegative ? 0 : 1;

    int pos = init.size() - start > 9 ? (int)init.size() - 9 : start;
    int count = pos == start ? (int)init.size() - start : 9;

    while (pos > start)
    {
        this->nums.push_back(std::stoi(init.substr(pos, count)));
        count = pos >= 9 + start ? 9 : pos - start;
        pos = pos >= 9 + start ? pos - 9 : start;
    }

    this->nums.push_back(std::stoi(init.substr(pos, count)));
}

BigInt BigInt::operator+(const BigInt& other) {
    return BigInt();
}

BigInt BigInt::operator-(const BigInt& other) {
    return BigInt();
}

//adds two positive integers, other <= this
BigInt BigInt::add(const BigInt &other) {
    auto res = BigInt();

    res.nums.clear();

    int tmp = 0, i = 0, cur;

    for (; i < other.nums.size(); ++i) {
        cur = this->nums[i] + other.nums[i] + tmp;

        res.nums.push_back(cur % 1000000000);
        tmp = cur / 1000000000;
    }

    for(; i < this->nums.size(); ++i) {
        cur = this->nums[i] + tmp;

        res.nums.push_back(cur % 1000000000);
        tmp = cur / 1000000000;
    }

    if(tmp != 0)
        res.nums.push_back(tmp);

    return res;
}

//subtracts two positive integers, other < this
BigInt BigInt::subtract(const BigInt &other) {
    return BigInt();
}

bool BigInt::operator>(const BigInt &other) {
    return false;
}

bool BigInt::operator<(const BigInt &other) {
    if (!this->nonNegative and other.nonNegative)
        return true;

    if (this->nonNegative and !other.nonNegative)
        return false;

    int absCompRes = this->absCompareTo(other);

    if (!this->nonNegative and absCompRes == 1)
        return true;

    return absCompRes == -1;

}

int BigInt::numbersOfDigits(int number) const {
    int counter = 1;
    while ((number /= 10) > 0) {
        counter++;
    }

    return counter;
}


std::ostream& operator<<(std::ostream& os, const BigInt& bigInt ) {
    if (!bigInt.nonNegative) {
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

    return os;
}

int BigInt::absCompareTo(const BigInt &other) {
    if (this->nums.size() < other.nums.size())
        return -1;

    if (this->nums.size() > other.nums.size())
        return 1;

    for(int i = this->nums.size() - 1; i >= 0; --i) {
        if (this->nums[i] < other.nums[i])
            return -1;

        if (this->nums[i] > other.nums[i])
            return 1;
    }

    return 0;
}
