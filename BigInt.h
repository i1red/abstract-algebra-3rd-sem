#ifndef ABSTRACT_ALGEBRA_BIGINT_H
#define ABSTRACT_ALGEBRA_BIGINT_H

#include <ostream>
#include <vector>
#include <string>
#include <cmath>

class BigInt {
    std::vector<int> nums;
<<<<<<< Updated upstream
    bool positive;
=======
    bool nonNegative;
    const int BASE = int(pow(10, 9));
>>>>>>> Stashed changes
public:
    explicit BigInt(const std::string& init = "0");
    BigInt operator+(const BigInt&);
    BigInt operator-(const BigInt&);
    bool operator>(const BigInt&);
    bool operator<(const BigInt&);
    friend std::ostream& operator<<(std::ostream& os, const BigInt& bigInt );
private:
    BigInt add(const BigInt&);
    BigInt subtract(const BigInt&);
    int numbersOfDigits(int number) const;
    void removeLeadingZeros();
};

std::ostream& operator<<(std::ostream&, const BigInt&);


#endif //ABSTRACT_ALGEBRA_BIGINT_H
