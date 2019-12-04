#ifndef GENERATOR_OF_G_GEN_OF_G_H
#define GENERATOR_OF_G_GEN_OF_G_H

#include <math.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "BigInt/BigInt.h"
#include "ModArithmetic/ModArithmetic.h"

struct factorization
{
    std::vector<BigInt> p;
    std::vector<BigInt> e;
};

factorization factorize_naive(BigInt divided);
std::vector<BigInt> generator(std::vector<BigInt> G);
BigInt getBigInt(int a);

#endif //GENERATOR_OF_G_GEN_OF_G_H
