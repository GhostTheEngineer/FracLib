/******************************************************************************
 * Project: MathApp
 * File: main.cpp
 * Description:
    This example file is meant to experiment with the library to familiarize
    yourself with FracLib features.

    Below in the main function is a basic example, you may run the executable
    by using ./run in your terminal (make sure you first compile/build with ./build 
    and that you've built the FracLib in the main directory with ./build).

    You may change the contents of main to experiment with the library,
    ensure you rebuild using ./build when changes are made.

    Enjoy!                                          
 * 
 * This file is not part of FracLib Library, it is an example standalone exe.
 * 
 * Copyright © 2025 Ghost - Two Byte Tech. All Rights Reserved.
 *
 * This source code is licensed under the MIT License. For more details, see
 * the LICENSE file in the root directory of this project.
 *
 * Version: v1.1.0
 * Author: Ghost
 * Created On: 1-16-2025
 * Last Modified: 1-16-2025
 *****************************************************************************/

#include "frac.h"
#include <iostream>

void print(const char* msg, FracLib::Frac& frac){
    // Support for writing Frac objects to output stream.
    std::cout << msg << ": " << frac << std::endl;
}

int main(){

    // CONSTRUCTION AND ASSIGNMENT
    FracLib::Frac frac1(0.5f); // use decimals!. 
    print("Construction by decimal", frac1);

    FracLib::Frac frac7("5/10", true); // use strings!
    print("Construction by string", frac7);

    frac1 = 0.6f; // Reassign with a decimal 
    print("Reassigned by decimal", frac1);

    frac1 = "1/2"; // Reassign with a string literal
    print("Reassigned by string", frac1);

    FracLib::Frac frac2(1,2); // Construction with numerator and denominator
    print("Construction of defined numerator and denominator", frac2);
    FracLib::Frac frac3(5); // Construction results in a fraction of 5/1
    print("Construction of defined numerator", frac3);
    FracLib::Frac frac4; // Construction results in a fraction of 0/1
    print("Default Construction", frac4);

    FracLib::Frac frac5(1.5f); // use decimals with a whole number for mixed fraction! 
    print("Construction by decimal with whole number", frac5);

    FracLib::Frac frac6("1 1/2"); // use string with a whole number for mixed fraction! 
    print("Construction by string with whole number", frac6);

    // ARITHMETIC
    frac1 = frac1 + frac2; // Arithmetic of two separate Frac objects
    print("Arithmetic (fraction + fraction)", frac1);

    frac1 = frac1 + "1/2"; // Arithmetic using string representation
    print("Arithmetic (fraction + string)", frac1);

    frac1 = frac1 * 0.2f; // Arithmetic using decimal representation
    print("Arithmetic (fraction * decimal)", frac1);

    frac1 = frac1 * 1.2f; // Arithmetic with mix fractions decimal
    print("Arithmetic (fraction * decimal(mixed))", frac1);

    frac1 = frac1 + "2 1/2"; // Arithmetic with mix fractions string
    print("Arithmetic (fraction + string(mixed))", frac1);

    // Arithmetic reversed order 
    frac1 = FracLib::Frac::Simplify(0.5f / frac1); // simplified
    print("Arithmetic (decimal / fraction) - simplified", frac1);
    
    frac1 = FracLib::Frac::Simplify("1/2" - frac1);
    print("Arithmetic (string / fraction) - simplified", frac1);

    // Increment/Decrement pre/post
    ++frac1;
    print("Prefix Increment", frac1);
    --frac1;
    print("Postfix Decrement", frac1);
    frac1++;
    print("Prefix Increment", frac1);
    frac1--;
    print("Postfix Decrement", frac1);

    frac1 *= -1; // flip negative to positive
    print("Compound Arithmetic (fraction *= -1) - flips sign.", frac1);

    // RELATIONAL
    if (frac1 == frac1){
        print("Equality", frac1);
    }
    if (frac1 != "2/92"){
        print("Inequality 2/92 not equal to", frac1);
    }
    if (2.6 > frac1){
        print("Relational 2 3/5 greater than", frac1);
    }

    // Improper Fraction
    FracLib::Frac frac8(2,1,2); // Construct improper fraction (whole, numerator, denominator)
    FracLib::Frac frac9 = FracLib::Frac::toImproper(frac8); // converts and return new frac object
    print("Improper fraction from 2 1/2 to", frac9);

    // INPUT: accepts decimal(0.5, 1.5) or string(2/4, 1 1/2) representations
    std::cout << "Input a fraction: " << std::flush;
    std::cin >> frac1;
    FracLib::Frac::SimplifyFrac(frac1); // when you can't perform inline or just want to simplify later
    print("User Input display", frac1);

    // Prevent terminal from closing
    system("pause");
    return 0;
}