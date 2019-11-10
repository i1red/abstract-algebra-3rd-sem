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

BigInt BigInt::operator+(BigInt& other) {
    auto res = BigInt();

    res.nums.clear();

    if (this->nonNegative) {
        if (other.nonNegative) {
            res = this->add(other);
        }

        else {
            if (this->absCompareTo(other) == -1) {
                res = other.subtract(*this);
                res.nonNegative = false;
            }

            else {
                res = this->subtract(other);
            }
        }

        return res;
    }

    else {
        if (other.nonNegative) {
            if (this->absCompareTo(other) == 1) {
                res = this->subtract(other);
                res.nonNegative = false;
            }

            else {
                res = other.subtract(*this);
            }
        }

        else {
            res = this->add(other);
            res.nonNegative = false;
        }

        return res;
    }
}

BigInt BigInt::operator-(BigInt& other) {
    auto res = BigInt();

    res.nums.clear();

    if (this->nonNegative && other.nonNegative) {
        if (this->absCompareTo(other) == -1) {
            res = other.subtract(*this);
            res.nonNegative = false;
        }

        else {
            res = this->subtract(other);
        }
    }

    else if (this->nonNegative && !other.nonNegative) {
        res = this->add(other);
    }

    else if (!this->nonNegative && other.nonNegative) {
        res = this->add(other);
        res.nonNegative = false;
    }

    else {
        if (this->absCompareTo(other) == 1) {
            res = this->subtract(other);
            res.nonNegative = false;
        }

        else {
            res = other.subtract(*this);
        }
    }

    return res;
}

//adds two positive integers, other <= this
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

    for (int i = 0; i < this->nums.size() || temp != 0; ++i) {
        res.nums.push_back(this->nums[i] - temp - (i < other.nums.size() ? other.nums[i] : 0));

        temp = res.nums[i] < 0;
      
        if (temp)
            res.nums[i] += BASE;
    }

    res.removeLeadingZeros();

    return res;
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

    if (!this->nonNegative && other.nonNegative)
        return true;

    if (this->nonNegative && !other.nonNegative)
        return false;

    int absCompRes = this->absCompareTo(other);

    if (!this->nonNegative && absCompRes == 1)
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

    for (int i = int(bigInt.nums.size()) - 2; i >= 0; i--) {
        //os << bigInt.nums[i] << " ";

        os << std::setfill('0') << std::setw(9) << bigInt.nums[i];
    }

    return os;
}

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

BigInt BigInt::mod(BigInt& other) {
    bool posResSign = true;
    BigInt self = *this, div = other;

    if (!div.nonNegative) {
        posResSign = false;
        div.nonNegative = true;
        self.nonNegative = !self.nonNegative;
    }

    if (!self.nonNegative) {
        self = self.eqPositive(div);
    }

    if (self < div) {
        return self;
    }

    BigInt res = self.mod_(div);
    res.nonNegative = posResSign;

    return res;
}

BigInt BigInt::mod_(BigInt& other) {
    BigInt res = *this, tmp = other.multToFit(res), tmpRes = res - tmp;

    while (!(res < tmp)) {
        res = tmpRes;

        if (res < tmp) {
            if (other == tmp) {
                break;
            }
            tmp = other.multToFit(res);
        }

        tmpRes = res - tmp;
    }

    return res;
}

BigInt BigInt::eqPositive(BigInt &other) {
    BigInt res = *this, tmp = other.multToFit(res);

    while (res < BigInt("0")) {
        res = res + tmp;
    }

    return res;
}

std::string BigInt::toString() const{
    std::stringstream numbers;
    numbers << this->nums.back();

    for (auto i = (int)this->nums.size() - 2; i >= 0; --i) {
        numbers << std::setfill('0') << std::setw(9) << this->nums[i];
    }

    return numbers.str();
}

BigInt BigInt::fillWithZeros(size_t zeroCount) {
    std::stringstream zeros;
    zeros << std::setfill('0') << std::setw(zeroCount);
    return BigInt(this->toString() + zeros.str());
}

BigInt BigInt::multToFit(const BigInt& other) {
    std::string thisStr = this->toString(), otherStr = other.toString();
    size_t zeroCount = otherStr.size() - thisStr.size();

    for (size_t i = 0; i < thisStr.size(); ++i) {
        if (thisStr[i] > otherStr[i]) {
            zeroCount -= 1;
            break;
        }
        else if (thisStr[i] < otherStr[i]) {
            break;
        }
    }

    std::stringstream zeros;
    zeros << std::setfill('0') << std::setw(zeroCount) << "";

    return BigInt(thisStr + zeros.str());
}

size_t BigInt::length() const {
    return (this->nums.size() - 1) * 9 + integerLength(this->nums.back());
}

size_t BigInt::integerLength(int number){
    return (size_t)log10(number) + 1;
}

size_t BigInt::firstDigit(int number) {
    return number / (pow(10, integerLength(number)));
}

bool BigInt::operator==(const BigInt& other) {
    return this->absCompareTo(other) == 0 && this->nonNegative == other.nonNegative;
}
