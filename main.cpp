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

void genTest() {
    //test.txt was generated randomly using Python script

    ifstream fin;
    fin.open("../tests/test.txt");

    ofstream fout;
    fout.open("../tests/test_res.txt", ios_base::out);

    string tmp;
    size_t counter = 1;

    while (!fin.eof()) {
        getline(fin, tmp);

        if (tmp.empty()) {
            break;
        }

        vector<string> nums = split(tmp, ' ');
        auto a = BigInt(nums[0]), b = BigInt(nums[1]);

        fout << "Test #" << counter << endl;

        fout << "BigInt a: " << a << endl;
        fout<<  "Number:   " << nums[0] << endl;
        fout << "BigInt b: " << b << endl;
        fout << "Number:   " << nums[1] << endl;
        fout << "a + b:    " << a + b << endl;
        fout << "Sum:      " << nums[2] << endl;
        fout << "a - b:    " << a - b <<endl;
        fout << "Dif:      " << nums[3] << endl;
        fout << "a * b     " << a * b << endl;
        fout << "Prod:     " << nums[4] << endl;
        fout << "a.mod(b): " << a.mod(b) << endl;
        fout << "Mod:      " << nums[5] << endl;

        fout << endl;

        ++counter;
    }
    fin.close();
    fout.close();
}

int main() {
    auto group = ModArithmetic(BigInt("43423112121212912108376182713918"));

    cout << group.add(BigInt("127623232832763253627323299999999993"),
                      BigInt("338733437232763367362323232325362320003288433")) << endl;

    cout << group.subtract(BigInt("2354954634654243235"),
                           BigInt("99999999999999999999999999999999999999")) << endl;

    cout << group.multiply(BigInt("1212334400000002323"), BigInt("-9939237217212323232121")) << endl;


    return 0;
}








