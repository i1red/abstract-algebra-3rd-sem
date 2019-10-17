#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {
    string str1 = "12345678", str2 = "999999999";



    auto test1 = BigInt(str1);
    //auto test2 = BigInt(str2);
    //test1.subtract(test2);
    cout << str1 << endl;
    cout << test1 << endl;
    return 0;
}