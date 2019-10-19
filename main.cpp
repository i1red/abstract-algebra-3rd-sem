#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {
    string str1 = "111111111111111111", str2 = "111111111111111";

    auto test1 = BigInt(str1);
    auto test2 = BigInt(str2);

    auto res_add = test1 + test2; //add

    auto res_sub = test1 - test2; //subtract

    cout << res_sub << endl;

    return 0;
}








