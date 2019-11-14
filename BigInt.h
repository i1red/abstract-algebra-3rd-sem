#ifndef ABSTRACT_ALGEBRA_BIGINT_H
#define ABSTRACT_ALGEBRA_BIGINT_H

#include <ostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>


class BigInt {
    std::vector<int> nums;
    bool nonNegative;
    static const int BASE;
    
public:
    explicit BigInt(const std::string& init = "0");
    bool operator==(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt mod(const BigInt&) const;
    friend std::ostream& operator<<(std::ostream& os, const BigInt& bigInt);

private:
    BigInt add(const BigInt&) const;
    BigInt subtract(const BigInt&) const;
    BigInt multiplication(const BigInt&) const;
    BigInt modPositive(const BigInt&) const;
    BigInt fillToFit(const BigInt&) const;
    BigInt eqPositive(const BigInt&) const;
    int absCompareTo(const BigInt&) const;
    std::string absToString() const;
    void removeLeadingZeros();
};


#endif //ABSTRACT_ALGEBRA_BIGINT_H
