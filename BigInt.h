#ifndef ABSTRACT_ALGEBRA_BIGINT_H
#define ABSTRACT_ALGEBRA_BIGINT_H

#include <ostream>
#include <vector>
#include <string>
#include <cmath>

class BigInt {
    std::vector<int> nums;
    bool nonNegative;
    const int BASE = int(pow(10, 9));
public:
    explicit BigInt(const std::string& init = "0");
    BigInt operator+(const BigInt&);
    BigInt operator-(const BigInt&);
    bool operator>(const BigInt&);
    bool operator<(const BigInt&);
    friend std::ostream& operator<<(std::ostream& os, const BigInt& bigInt );
private:
    int absCompareTo(const BigInt&);
    BigInt add(const BigInt&);
    BigInt subtract(const BigInt&);
    int absCompareTo(const BigInt&);
    int numbersOfDigits(int number) const;
    void removeLeadingZeros();
};


#endif //ABSTRACT_ALGEBRA_BIGINT_H
