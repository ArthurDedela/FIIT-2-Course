#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    ifstream fin("ArturDedela11.txt");
    if (!fin.is_open()) {
        throw std::runtime_error("Can't open file.");
    }

    string input, prev("");
    string buf;

    while (!fin.eof()) {
        fin >> input;

        if (input != prev) {
            buf += input + ' ';
        }

        prev = input;
    }
    ofstream fout("ArturDedela11.txt", ios_base::out);
    fout << buf;

    system("pause");
    return 0;
}