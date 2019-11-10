#include <iostream>
#include <fstream>
#include <string>
#include "BigInt.h"

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

void genTest() {
    ifstream fin;
    fin.open("/home/ivan/PycharmProjects/big_int_test_gen/test.txt");

    ofstream fout;
    fout.open("test_res.txt", ios_base::out);

    string tmp;
    size_t counter = 1;

    while (!fin.eof()) {
        getline(fin, tmp);
        vector<string> nums = split(tmp, ' ');
        auto a = BigInt(nums[0]), b = BigInt(nums[1]);

        fout << "Test #" << counter << endl;

        fout << "BigInt a: " << a << endl;
        cout << nums[0] << endl;
        cout << a << endl;
        cout << endl;
        fout<<  "Number:   " << nums[0] << endl;
        fout << "BigInt b: " << b << endl;
        fout << "Number:   " << nums[1] << endl;
        fout << "a + b: " << a + b << endl;
        fout << "Sum:   " << nums[2] << endl;
        fout << "a - b: " << a - b <<endl;
        fout << "Dif:   " << nums[3] << endl;

        fout << endl;

        ++counter;
    }
    fin.close();
    fout.close();
}

int main() {
    BigInt a("7288813678222062832382893230000000123232424243223211112"), b("-3");
    cout << a.toString()<< endl;
    cout << a.mod(b) << endl;

    return 0;
}








