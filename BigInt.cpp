#include "BigInt.h"


const int BigInt::BASE = (int)pow(10, 9);


BigInt::BigInt(const std::string& init) {
    this->nonNegative = init[0] != '-';
    size_t start = this->nonNegative ? 0 : 1;

    size_t pos = init.size() - start > 9 ? (int)init.size() - 9 : start;
    size_t count = pos == start ? (int)init.size() - start : 9;

    while (pos > start)
    {
        this->nums.push_back(std::stoi(init.substr(pos, count)));
        count = pos >= 9 + start ? 9 : pos - start;
        pos = pos >= 9 + start ? pos - 9 : start;
    }

    this->nums.push_back(std::stoi(init.substr(pos, count)));
}


bool BigInt::operator==(const BigInt& other) const{
    return this->nonNegative == other.nonNegative && this->absCompareTo(other) == 0;
}


bool BigInt::operator>(const BigInt &other) const{
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


bool BigInt::operator<(const BigInt &other) const{

    if (!this->nonNegative && other.nonNegative)
        return true;

    if (this->nonNegative && !other.nonNegative)
        return false;

    int absCompRes = this->absCompareTo(other);

    if (!this->nonNegative && absCompRes == 1)
        return true;

    return absCompRes == -1;
}


bool BigInt::operator>=(const BigInt& other) const{
    return !this->operator<(other);
}


bool BigInt::operator<=(const BigInt& other) const{
    return !this->operator>(other);
}


BigInt BigInt::operator+(const BigInt& other) const {
    auto res = BigInt();

    res.nums.clear();

    if (this->nonNegative) {
        if (other.nonNegative) {
            res = this->absCompareTo(other) >= 0 ? this->add(other) : other.add(*this);
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

BigInt BigInt::operator-(const BigInt& other) const {
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


BigInt BigInt::operator*(const BigInt &other) const {
    return this->multiplication(other);
}


BigInt BigInt::operator/(const BigInt& other) const {
    BigInt res = this->absDivide(other).first;
    res.nonNegative = res.nums.back() == 0 ? true : this->nonNegative == other.nonNegative;

    return res;
}


BigInt BigInt::operator%(const BigInt& other) const {
    auto absDiv = this->absDivide(other);

    BigInt res = absDiv.second;
    res.nonNegative = res.nums.back() == 0 ? true : this->nonNegative;

    return res;
}


BigInt BigInt::mod(const BigInt& other) const {
    BigInt res = *this, div = other;

    if (!div.nonNegative) {
        div.nonNegative = true;
        res.nonNegative = !res.nonNegative;
    }

    if (!res.nonNegative) {
        res = res.eqPositive(div);
    }

    if (res >= div) {
        res = res.absDivide(div).second;
    }

    res.nonNegative = res.nums.back() == 0 ? true : other.nonNegative;

    return res;
}


std::ostream& operator<<(std::ostream& os, const BigInt& bigInt ) {
    if (!bigInt.nonNegative) {
        os << '-';
    }

    os << bigInt.nums[bigInt.nums.size() - 1];

    for (int i = int(bigInt.nums.size()) - 2; i >= 0; i--) {
        os << std::setfill('0') << std::setw(9) << bigInt.nums[i];
    }

    return os;
}


//adds two positive integers, other <= this
BigInt BigInt::add(const BigInt& other) const{
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
BigInt BigInt::subtract(const BigInt& other) const{
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


BigInt BigInt::multiplication(const BigInt &other) const {
    auto res  = BigInt();

    res.nums.clear();
    res.nums.resize(this->nums.size() + other.nums.size());

    for (size_t i = 0; i < this->nums.size(); ++i) {
        int carry = 0;

        for (size_t j = 0; j < other.nums.size() || carry != 0; ++j) {
            long long cur = res.nums[i + j] +
                            this->nums[i] * 1LL * (j < other.nums.size() ? other.nums[j] : 0) + carry;
            res.nums[i + j] = static_cast<int>(cur % BASE);
            carry = static_cast<int>(cur / BASE);
        }
    }

    res.nonNegative = this->nonNegative == other.nonNegative;
    res.removeLeadingZeros();
    return res;
}


std::pair<BigInt, BigInt> BigInt::absDivide(const BigInt& other) const{
    if (other == BigInt("0")) {
        throw std::logic_error("Zero division error");
    }

    auto fillOther = other.absFillToFit(*this);
    BigInt modRes = *this, tmp = fillOther.first, increment = fillOther.second, divRes("0");
    modRes.nonNegative = tmp.nonNegative = true;
    BigInt tmpRes = modRes - tmp;

    while (modRes >= tmp) {
        modRes = tmpRes;
        divRes = divRes + increment;

        if (modRes < tmp) {
            if (other == tmp) {
                break;
            }

            fillOther = other.absFillToFit(modRes);
            tmp = fillOther.first, increment = fillOther.second;
        }

        tmpRes = modRes - tmp;
    }

    return std::make_pair(divRes, modRes);
}


std::pair<BigInt, BigInt> BigInt::absFillToFit(const BigInt& other) const {
    std::string thisStr = this->absToString(), otherStr = other.absToString();
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
    zeros << std::setfill('0') << std::setw((int)zeroCount) << "";

    return std::make_pair(BigInt(thisStr + zeros.str()), BigInt("1" + zeros.str()));
}


BigInt BigInt::eqPositive(const BigInt &other) const {
    BigInt res = *this, tmp = other.absFillToFit(res).first;

    while (!res.nonNegative) {
        res = res + tmp;
    }

    return res;
}


int BigInt::absCompareTo(const BigInt &other) const { // (-1 ~ <)  (1 ~ >) (0 ~ ==)
    if (this->nums.size() < other.nums.size())
        return -1;

    if (this->nums.size() > other.nums.size())
        return 1;

    for(int i = int(this->nums.size()) - 1; i >= 0; --i) {
        if (this->nums[i] < other.nums[i]) {
            return -1;
        }

        if (this->nums[i] > other.nums[i]) {
            return 1;
        }
    }

    return 0;
}


std::string BigInt::absToString() const {
    std::stringstream numbers;
    numbers << this->nums.back();

    for (auto i = (int)this->nums.size() - 2; i >= 0; --i) {
        numbers << std::setfill('0') << std::setw(9) << this->nums[i];
    }

    return numbers.str();
}


void BigInt::removeLeadingZeros() {
    while (this->nums.size() > 1 && this->nums.back() == 0) {
        this->nums.pop_back();
    }

    if (this->nums.size() == 1 && this->nums[0] == 0) {
        this->nonNegative = true;
    }
}

