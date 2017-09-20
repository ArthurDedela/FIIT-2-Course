#include <iostream>
#include "Fraction.h"
#include "Matrix.h"

using namespace std;


int main() {
    Fraction<long long> a(5, 6), b(4, 6);


    Matrix<Fraction<long long>, 3> m;

    cin >> m;
    cout << m;
    cout << (m * m);
    cout << "Det: " << m.determinant() << '\n';
    
    system("pause");

    return 0;
}