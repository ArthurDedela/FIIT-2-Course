#include <iostream>
#include <vector>

using namespace std;

int main() {

    vector<int> squares;
    squares.resize(100);

    cout << "Squares: ";
    for (int i = 1; i <= 100; i++) {
        cout << (squares[i - 1] = i*i) << ' ';        
    }
    cout << '\n';
    cout << "Square root: ";
    for (auto it : squares) {
        cout << sqrt(it) << ' ';
    }
    cout << '\n';

    system("pause");

    return 0;
}