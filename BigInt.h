#ifndef ABSTRACT_ALGEBRA_BIGINT_H
#define ABSTRACT_ALGEBRA_BIGINT_H

#include <ostream>
#include <vector>


class BigInt {
    std::vector<char> digitPlaces;
public:
    explicit BigInt(const char*);
    BigInt operator+(const BigInt&);
    BigInt operator-(const BigInt&);
};

std::ostream& operator<<(std::ostream&, const BigInt&);


#endif //ABSTRACT_ALGEBRA_BIGINT_H
