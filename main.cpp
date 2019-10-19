#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {
<<<<<<< Updated upstream
    string str1 = "-123456789000000000000000123450000678900000000", str2 = "999999999";



    auto test1 = BigInt(str1);
    //auto test2 = BigInt(str2);
    //test1.subtract(test2);
    cout << str1 << endl;
    cout << test1 << endl;
=======
    string str1 = "111111111111111111", str2 = "11111111111111119";

    auto test1 = BigInt(str1);
    auto test2 = BigInt(str2);

    auto res_add = test1 + test2; //add

    auto res_sub = test1 - test2; //subtract

    cout << res_sub << endl;

>>>>>>> Stashed changes
    return 0;
}








