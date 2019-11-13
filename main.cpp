#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {
    string str1 = "-1111111111111111111111111111", str2 = "858719562523133589452408799040184151";

    auto test1 = BigInt(str1);
    auto test2 = BigInt(str2);

    auto res_add = test1 + test2; //add

    auto res_sub = test1 - test2; //subtract

    auto res_mult = test1 * test2; //multiplication

    cout << res_add << endl;
    cout << res_sub << endl;
    cout << res_mult << endl;

    return 0;
}








