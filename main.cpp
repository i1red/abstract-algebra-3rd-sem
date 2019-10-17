#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {
    string str1 = "99999999999999999999", str2 = "999999999999999999";

    auto test1 = BigInt(str1);
    auto test2 = BigInt(str2);
    //test1.subtract(test2);s
    return 0;
}