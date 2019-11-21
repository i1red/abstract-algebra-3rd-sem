#include <iostream>
#include <fstream>
#include <string>
#include <random>
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


void genTestFile(int numberOfTests, const string& filename) {
    //to run this function efficiently you need to have python3 installed on your computer
    string command = "python3 ../testsBigInt/big_int_test_gen.py -t " +
                      to_string(numberOfTests) + " -f ../testsBigInt/" + filename;

    system(command.c_str());
}


void testBigInt(const string& testFile, const string& resFile) {
    ifstream fin;
    fin.open("../testsBigInt/" + testFile);

    ofstream fout;
    fout.open("../testsBigInt/" + resFile, ios_base::out);

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

        BigInt sum = a + b;
        if (sum != BigInt(nums[2])) {
            cout << "FAILED SUM" << a << " " << b << endl;
        }
        fout << "a + b:    " << sum << endl;
        fout << "Sum:      " << nums[2] << endl;

        BigInt dif = a - b;
        if (dif != BigInt(nums[3])) {
            cout << "FAILED DIF" << a << " " << b << endl;
        }
        fout << "a - b:    " << dif << endl;
        fout << "Dif:      " << nums[3] << endl;

        BigInt prod = a * b;
        if (prod != BigInt(nums[4])) {
            cout << "FAILED PROD" << a << " " << b << endl;
        }
        fout << "a * b     " << prod << endl;
        fout << "Prod:     " << nums[4] << endl;

        BigInt div = a / b;
        if (div != BigInt(nums[5])) {
            cout << "FAILED DIV" << a << " " << b << endl;
        }
        fout << "a / b     " << div << endl;
        fout << "Div:      " << nums[5] << endl;

        BigInt rest = a % b;
        if (rest != BigInt(nums[6])) {
            cout << "FAILED REST" << a << " " << b << endl;
        }
        fout << "a % b     " << rest << endl;
        fout << "Rest:     " << nums[6] << endl;

        BigInt mod = a.mod(b);
        if (mod != BigInt(nums[7])) {
            cout << "FAILED MOD" << a << " " << b << endl;
        }
        fout << "a.mod(b): " << mod << endl;
        fout << "Mod:      " << nums[7] << endl;

        fout << endl;

        ++counter;
    }

    fin.close();
    fout.close();
}


BigInt genRandomBigInt() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> uid(0, 120);

    string init = uid(gen) % 2 ? "" : "-";
    size_t len = 1 + uid(gen);

    init.push_back('1' + uid(gen) % 9);

    for(size_t i = 1; i < len; ++i) {
        init.push_back('0' + uid(gen) % 10);
    }

    return BigInt(init);
}


void testModArithmetic() {
    BigInt n("1000000007");
    ModArithmetic ring(n);

    for (size_t i = 0; i < 25; ++i) {
        BigInt testInt = genRandomBigInt();
        while(testInt.mod(n) == BigInt("0")) {
            testInt = genRandomBigInt();
        }

        cout << endl;
        cout << testInt << endl;

        try {
            cout << ring.divide(testInt, testInt) << endl;
        }
        catch (logic_error& ex){
            cout << ex.what() << endl;
            BigInt testInt2 = testInt.mod(n);
            BigInt inverse = ring.inverseElement(testInt2);

            cout << testInt2 << endl;
            cout << ring.multiply(testInt, inverse) << endl;
        }
    }
}


int main() {
    string testFile = "test.txt";
    string testResFile = "test_res.txt";

    //genTestFile(1000, testFile);
    //testBigInt(testFile, testResFile);

    testModArithmetic();

    return 0;
}








