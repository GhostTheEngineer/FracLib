#include "Tester.h"
#include "../include/frac.h"
using namespace FracLib;

TEST(DefaultConstructor) {
    Frac f;
    Tester::assertEqual(0, f.numerator, "Numerator should be 2");
    Tester::assertEqual(1, f.denominator, "Denominator should be 3");
}

TEST(toImproper) {
    Frac mixed(1, 2, 3); // Represents 1 2/3
    Frac improper = mixed.toImproper(mixed);
    Tester::assertEqual(5, improper.numerator, "Improper numerator should be 5");
    Tester::assertEqual(3, improper.denominator, "Improper denominator should be 3");
}

TEST(toDouble) {
    Frac mixed(1, 1, 2); 
    double decimal = Frac::toDouble(mixed);
    Tester::assertEqual(1.5, decimal);
}

TEST(toFloat) {
    Frac mixed(1, 1, 2); 
    float decimal = Frac::toFloat(mixed);
    Tester::assertEqual(1.5f, decimal);
}

TEST(toString) {
    Frac mixed(1, 1, 2); 
    std::string str = Frac::toString(mixed);
    Tester::assertEqual(std::string("1 1/2"), str);
}

TEST(Negation) {
    Frac mixed(1, 1, 2); 
    Frac frac = -mixed;
    Tester::assertEqual(std::string("-1 1/2"), Frac::toString(frac));
}

TEST(PreIncrement) {
    Frac mixed(1, 1, 2); 
    ++mixed;
    Tester::assertEqual(std::string("2 0/2"), Frac::toString(mixed));
}

TEST(PostIncrement) {
    Frac mixed(1, 1, 2); 
    mixed++;
    Tester::assertEqual(std::string("2 0/2"), Frac::toString(mixed));
}

TEST(PreDecrement) {
    Frac mixed(1, 1, 2); 
    --mixed;
    Tester::assertEqual(std::string("1 0/2"), Frac::toString(mixed));
}

TEST(PostDecrement) {
    Frac mixed(1, 1, 2); 
    mixed--;
    Tester::assertEqual(std::string("1 0/2"), Frac::toString(mixed));
}

TEST(Relational) {
    Frac mixed(1, 1, 2); 
    Frac mixed2(1, 2);
    Tester::assertTrue(mixed >= mixed2); // change operator to test other relations
}

TEST(Addition) {
    Frac mixed(1, 1, 2); 
    Frac result = mixed + Frac(1, 1, 2);
    Tester::assertEqual(std::string("3 0/2"), Frac::toString(result)); // change operator to test other relations
}


int main() {
    Tester::runTests();
    system("pause");
    return 0;
}
