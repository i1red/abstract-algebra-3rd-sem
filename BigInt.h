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
    int BASE = int(pow(10, 9));
    
public:
    explicit BigInt(const std::string& init = "0");
    BigInt operator+(BigInt&);
    BigInt operator-(BigInt&);
    BigInt mod(BigInt&);
    bool operator>(const BigInt&);
    bool operator<(const BigInt&);
    bool operator==(const BigInt&);
    friend std::ostream& operator<<(std::ostream& os, const BigInt& bigInt);
    std::string toString() const ;
private:

    int absCompareTo(const BigInt&);
    BigInt fillWithZeros(size_t);
    BigInt multToFit(const BigInt&);
    size_t length() const;
    static size_t integerLength(int);
    static size_t firstDigit(int);
    BigInt add(const BigInt&);
    BigInt subtract(const BigInt&);
    BigInt mod_(BigInt&);
    BigInt eqPositive(BigInt&);
    int numbersOfDigits(int number) const;
    void removeLeadingZeros();
};


#endif //ABSTRACT_ALGEBRA_BIGINT_H
