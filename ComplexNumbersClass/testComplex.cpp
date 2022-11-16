#include "complex.h"

using namespace std;

void basicOperatorsTest();
void specialCasesAdditionTest();
void specialCasesMultiDivTest();
void comparisionTest();
void magnitudeAndPhaseTest();

int main() {
    basicOperatorsTest();
    specialCasesAdditionTest();
    specialCasesMultiDivTest();
    comparisionTest();
    magnitudeAndPhaseTest();
}

void basicOperatorsTest() {
    Complex c1(1, 3);
    Complex c2(2, 4);
    Complex c3(-2.5, -2.1);
    cout << "________________________________" << endl;
    cout << "      BASIC OPERATORS TEST      " << endl;
    cout << "c1 = " << c1 << " |  c2 = " << c2 << " | c3 = " << c3 << "\n" << endl;
    cout << "c1 + c2 = " << c1 + c2 << endl;
    cout << "c1 - c2 = " << c1 - c2 << endl;
    cout << "c1 * c2 = " << c1 * c2 << endl;
    cout << "c1 / c2 = " << c1 / c2 << endl;
}

void specialCasesAdditionTest() {
    Complex c1(2, 3);
    Complex c2(1.5, -4.5);
    Complex c3(-2, -2);
    cout << "________________________________" << endl;
    cout << "   SPECIAL CASES ADDITION TEST  " << endl;
    cout << "c1 = " << c1 << " |  c2 = " << c2 << " | c3 = " << c3 << "\n" << endl;
    c1 += c2 += c3;
    cout << "Test: c1 += c2 += c3" << endl;
    cout << "c1 = " << c1 << " |  c2 = " << c2 << " | c3 = " << c3 << "\n" << endl;
    (c1 += c2) += c3;
    cout << "Test: (c1 += c2) += c3" << endl;
    cout << "c1 = " << c1 << " |  c2 = " << c2 << " | c3 = " << c3 << "\n" << endl;
    c1 = c1 + 7;
    cout << "Test: c1 + 7" << endl;
    cout << "c1 = " << c1 << " |  c2 = " << c2 << " | c3 = " << c3 << "\n" << endl;
    c2 = 7 + c2;
    cout << "Test: 7 + c2" << endl;
    cout << "c1 = " << c1 << " |  c2 = " << c2 << " | c3 = " << c3 << endl;
}

void specialCasesMultiDivTest() {
    Complex c1(2, 3);
    Complex c2(1.5, -4.5);
    Complex c3(-2, -2);
    cout << "________________________________" << endl;
    cout << "  SPECIAL CASES MULTI/DIV TEST  " << endl;
    cout << "c1 = " << c1 << " |  c2 = " << c2 << " | c3 = " << c3 << "\n" << endl;
    c1 *= c2 *= c3;
    cout << "Test: c1 *= c2 *= c3" << endl;
    cout << "c1 = " << c1 << " |  c2 = " << c2 << " | c3 = " << c3 << "\n" << endl;
    c2 = c2 * 5;
    cout << "Test: c2 = c2 * 5" << endl;
    cout << "c1 = " << c1 << " |  c2 = " << c2 << " | c3 = " << c3 << "\n" << endl;
    c3 = 5 * c3;
    cout << "Test: c3 = 5 * c3" << endl;
    cout << "c1 = " << c1 << " |  c2 = " << c2 << " | c3 = " << c3 << endl;

}

void comparisionTest() {
    Complex c(2, 5);
    cout << "________________________________" << endl;
    cout << "       COMPARISION TEST         " << endl;
    cout << "c = 2 + 5i\n" << endl;
    cout << "   c == 3.5 is " << (c == 3.5) << endl;
    cout << "   3.5 == c is " << (3.5 == c) << endl;
    cout << "   c == Complex(2,5) is " << (c == Complex(2,5)) << endl;
}

void magnitudeAndPhaseTest() {
    Complex c(2, 5);
    cout << "________________________________" << endl;
    cout << "    MAGNITUDE AND PHASE TEST    " << endl;
    cout << "c = 2 + 5i\n" << endl;
    cout << "   Magnitude is " << c.getMagnitude() << endl;
    cout << "   Phase is " << c.getPhase() << " rad" << endl;
    cout << "________________________________" << endl;
}