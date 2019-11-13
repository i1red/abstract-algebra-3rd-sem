#ifndef ABSTRACT_ALGEBRA_BIGINT_H
#define ABSTRACT_ALGEBRA_BIGINT_H

#include <ostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

class BigInt {
    std::vector<int> nums;
    bool nonNegative;
    int BASE = int(pow(10, 9));
    
public:
    explicit BigInt(const std::string& init = "0");
    BigInt operator+(BigInt&);
    BigInt operator-(BigInt&);
    BigInt operator*(BigInt&);
    bool operator>(const BigInt&);
    bool operator<(const BigInt&);
    friend std::ostream& operator<<(std::ostream& os, const BigInt& bigInt);

private:
    int absCompareTo(const BigInt&);
    BigInt add(BigInt&);
    BigInt subtract(const BigInt&);
    BigInt multiplication(const BigInt&);
    int numbersOfDigits(int number) const;
    void removeLeadingZeros();
};


#endif //ABSTRACT_ALGEBRA_BIGINT_H
