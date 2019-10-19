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
<<<<<<< Updated upstream
    return BigInt(nullptr);
}

BigInt BigInt::operator-(const BigInt& other) {
    return BigInt(nullptr);
}

BigInt BigInt::add(const BigInt &other) {
    return BigInt(nullptr);
}

BigInt BigInt::subtract(const BigInt &other) {

=======
    auto res = this->add(other);

    return res;
}

BigInt BigInt::operator-(const BigInt& other) {
    auto res = this->subtract(other);

    return res;
}

//adds two positive integers, this >= other
BigInt BigInt::add(const BigInt &other) {
    auto res = BigInt();

    res.nums.clear();

    int temp = 0, i = 0, cur;

    for (; i < int(other.nums.size()); i++) {
        cur = this->nums[i] + other.nums[i] + temp;

        res.nums.push_back(cur % BASE);
        temp = cur / BASE;
    }

    for(; i < int(this->nums.size()); ++i) {
        cur = this->nums[i] + temp;

        res.nums.push_back(cur % BASE);
        temp = cur / BASE;
    }

    if(temp != 0)
        res.nums.push_back(temp);

    return res;
}

//subtracts two positive integers, this >= other
BigInt BigInt::subtract(const BigInt &other) {
    auto res  = BigInt();

    res.nums.clear();

    int temp = 0;

    for (int i = 0; i < other.nums.size() || temp != 0; ++i) {
        res.nums.push_back(this->nums[i] - temp - (i < other.nums.size() ? other.nums[i] : 0));

        temp = res.nums[i] < 0;
        if (temp)
            res.nums[i] += BASE;
    }

    res.removeLeadingZeros();

    return res;
>>>>>>> Stashed changes
}

bool BigInt::operator>(const BigInt &other) {
    if (!this->nonNegative && other.nonNegative)
        return false;

    if (this->nonNegative && !other.nonNegative)
        return true;

    int absCompRes = this->absCompareTo(other);

    if (!this->nonNegative && absCompRes == 1) {
        return false;
    }

    return absCompRes == 1;

}

bool BigInt::operator<(const BigInt &other) {
<<<<<<< Updated upstream
    return false;
=======
    if (!this->nonNegative && other.nonNegative)
        return true;

    if (this->nonNegative && !other.nonNegative)
        return false;

    int absCompRes = this->absCompareTo(other);

    if (!this->nonNegative && absCompRes == 1)
        return true;

    return absCompRes == -1;

>>>>>>> Stashed changes
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

    for (int i = int(bigInt.nums.size()) - 2; i >= 0; i--) {
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
<<<<<<< Updated upstream
=======

int BigInt::absCompareTo(const BigInt &other) { // (-1 ~ <)  (1 ~ >) (0 ~ ==)
    if (this->nums.size() < other.nums.size())
        return -1;

    if (this->nums.size() > other.nums.size())
        return 1;

    for(int i = int(this->nums.size()) - 1; i >= 0; --i) {
        if (this->nums[i] < other.nums[i])
            return -1;

        if (this->nums[i] > other.nums[i])
            return 1;
    }

    return 0;
}

void BigInt::removeLeadingZeros() {
    while (this->nums.size() > 1 && this->nums.back() == 0) {
        this->nums.pop_back();
    }

    if (this->nums.size() == 1 && this->nums[0] == 0) {
        this->nonNegative = true;
    }
}




>>>>>>> Stashed changes
