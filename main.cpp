#include <iostream>
#include <fstream>
#include <string>
#include "BigInt.h"
#include "ModArithmetic.h"

using namespace std;

vector<string> split(const string& s, char delimiter) {
    vector<string> res;
    size_t lt = 0;
    string tmp;

    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == delimiter) {
            tmp = s.substr(lt, i + 1 - lt);

            if (tmp[tmp.size() - 1] == ' ')
                tmp.pop_back();

            res.push_back(tmp);
            lt = i + 1;
        }
    }

    res.push_back(s.substr(lt, s.size() - lt));

    return res;
}

//void genTest() {
//    //test.txt was generated randomly using Python script
//
//    ifstream fin;
//    fin.open("../tests/test.txt");
//
//    ofstream fout;
//    fout.open("../tests/test_res.txt", ios_base::out);
//
//    string tmp;
//    size_t counter = 1;
//
//    while (!fin.eof()) {
//        getline(fin, tmp);
//
//        if (tmp.empty()) {
//            break;
//        }
//
//        vector<string> nums = split(tmp, ' ');
//        auto a = BigInt(nums[0]), b = BigInt(nums[1]);
//
//        fout << "Test #" << counter << endl;
//
//        fout << "BigInt a: " << a << endl;
//        fout<<  "Number:   " << nums[0] << endl;
//        fout << "BigInt b: " << b << endl;
//        fout << "Number:   " << nums[1] << endl;
//        fout << "a + b:    " << a + b << endl;
//        fout << "Sum:      " << nums[2] << endl;
//        fout << "a - b:    " << a - b <<endl;
//        fout << "Dif:      " << nums[3] << endl;
//        fout << "a * b     " << a * b << endl;
//        fout << "Prod:     " << nums[4] << endl;
//        fout << "a / b     " << a / b << endl;
//        fout << "Div:      " << nums[5] << endl;
//        fout << "a.mod(b): " << a.mod(b) << endl;
//        fout << "Mod:      " << nums[6] << endl;
//
//        fout << endl;
//
//        ++counter;
//    }
//
//    fin.close();
//    fout.close();
//}




int main() {
    //genTest();

    auto n1 = BigInt("11");
    auto mod = BigInt("3");

    auto res = ModArithmetic(mod);

    cout << res.inverseElement(n1) << endl;

    return 0;
}








