#include <iostream>
#include "Fraction.h"
#include "Matrix.h"


template<typename T>
struct PolyDef {};

template<>
struct PolyDef<int> {
    static constexpr int One = 1;
    static constexpr int Zero = 0;
};

template<>
struct PolyDef<Fraction<int>> {
    static Fraction<int> One;
    static Fraction<int> Zero;
};
Fraction<int> PolyDef<Fraction<int>>::One = Fraction<int>(1, 1);
Fraction<int> PolyDef<Fraction<int>>::Zero = Fraction<int>(0, 1);

#include "Polynom.h"

using namespace std;


int main() {
    /*
1/2	    3/5	    1/2
4/5	    2/3 	5/6
2/3	    1/2 	2/5
*/


    ////cin >> m;
    //cout << m;
    //cout << m.inverse();


    //cout << (m * m);
    //cout << "Det: " << m.determinant() << '\n';


    cout << "\nPolynoms:\n";

    Fraction<int> a(5, 6), b(4, 6);
    Fraction<int> c(2, 3);

    Matrix<Fraction<int>, 3> m_1;
    Matrix<Fraction<int>, 3> m_2;

    //Polynom<Fraction<int>> pol_f;
    //pol_f.addMonom(c, 2);
    //pol_f.addMonom(a, 4);

    //cout << pol_f;
    //cin >> m_1;
    //cin >> m_2;

    Polynom<Matrix<Fraction<int>, 2>> pol(
        "4/1 4/1\n4/1 4/1\nx^2 1/1 2/1\n3/1 4/1\nx^0"
    ); 

    Polynom<Matrix<Fraction<int>, 2>> pol_2(
        "-1/1 0/1\n0/1 -1/1\nx^1"
    );

    Polynom<Matrix<Fraction<int>, 2>> pol_3(
        "4/1 4/1\n4/1 4/1\nx^2"
    );

    /*TODO полиномы от матрицы, конструктор полинома из строки*/

    cout << "Pol: \n" << pol << '\n';
    cout << "Pol_2: \n" << pol_2 << '\n';

    cout << "Pol_2 - pol_2: \n";
    cout << (pol_2 - pol_2) << "\n\n";
    cout << "pol - pol_3: \n";
    cout << (pol - pol_3) << "\n\n";

    //cout << pol.derivative() << '\n';
    //cout << pol.superposition(pol_2) << '\n';

    //cout << (pol + pol_2) << '\n';
    //cout << (pol - pol_2) << '\n';
    //cout << (pol * pol_2) << '\n';
    //cout << (pol / pol_2) << '\n';
    //cout << (pol % pol_2) << endl;

    //cout << (pol += pol_2) << '\n';
    //cout << (pol -= pol_2) << '\n';
    //cout << (pol *= pol_2) << '\n';
    //cout << (pol /= pol_2) << '\n';
    //cout << (pol %= pol_2) << endl;

    
    system("pause");

    return 0;
}