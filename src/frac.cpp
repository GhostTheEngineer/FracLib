/******************************************************************************
 * Project: FracLib
 * File: Frac.cpp
 * Description:
 *  This source file implements the `Frac` class, which provides robust support 
 *  for performing arithmetic operations, comparisons, and utility functions on 
 *  fractions. The class ensures proper error handling for invalid operations 
 *  like division by zero or overflow during calculations.
 *  
 *  Key Features:
 *  - Constructors to initialize fractions from various formats (integers, 
 *    decimals, strings, or other `Frac` objects).
 *  - Comprehensive arithmetic operations, including addition, subtraction, 
 *    multiplication, and division, with detailed overflow checks.
 *  - Overloaded operators for comparisons, compound assignments, and increment 
 *    or decrement operations.
 *  - Utility functions for simplifying fractions, converting fractions to 
 *    strings, and parsing complex fraction formats.
 *  - Static helper methods for validation, such as overflow checks, improper fraction and 
 *    reciprocal calculations.
 *  
 *  This implementation ensures mathematical correctness and robustness, making 
 *  it suitable for applications requiring precise fraction management.
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

#include "../include/frac.h"
#include <limits>
#include <sstream>
#include <iostream>
#include <cmath>

namespace FracLib {
    const char* Frac::ZERO_DIVISOR_ERROR = "Division by zero not allowed. Denominator cannot be zero.";
    const char* Frac::OVERFLOW_ERROR = "Integer overflow detected.";
    const char* Frac::INVALID_STRING_PARAMETER_ERROR = "Improper format. Accepted fraction form: (ie \"1/2\" or \"25\" or  \"3 1/2\").";

    //\\\\\\\\\\\\\\\\\\\\/
    // Utilities
    //\\\\\\\\\\\\\\\\\\\\/
    bool willMultiplicationOverflow(int a, int b) {
        // Handle zero cases
        if (a == 0 || b == 0) return false;

        // Check for overflow
        if (a == -1 && b == std::numeric_limits<int>::min()) return true;
        if (b == -1 && a == std::numeric_limits<int>::min()) return true;

        int result = a * b;
        return result / b != a;
    }

    bool willAdditionOverflow(int a, int b) {
        if (b > 0 && a > std::numeric_limits<int>::max() - b) return true;
        if (b < 0 && a < std::numeric_limits<int>::min() - b) return true;
        return false;
    }

    bool willSubtractionOverflow(int a, int b) {
        if (b < 0 && a > std::numeric_limits<int>::max() + b) return true;
        if (b > 0 && a < std::numeric_limits<int>::min() + b) return true;
        return false;
    }


    //\\\\\\\\\\\\\\\\\\\\/
    // Constructors
    //\\\\\\\\\\\\\\\\\\\\/
    Frac::Frac() : numerator(0), denominator(1), whole(0) {}
    Frac::Frac(int n) : numerator(n), denominator(1), whole(0) {}
    Frac::Frac(int n, int d, bool isSimplifying) : numerator(n), denominator(d), whole(0) {
        if (denominator == 0){
            throw std::invalid_argument(ZERO_DIVISOR_ERROR);
        }
        // Optional
        if (isSimplifying) simplify();
    }
    Frac::Frac(int w, int n, int d, bool isSimplifying) : numerator(n), denominator(d), whole(w) {
        if (denominator == 0){
            throw std::invalid_argument(ZERO_DIVISOR_ERROR);
        }
        // Optional
        if (isSimplifying) simplify();
    }
    Frac::Frac(float decimal) : whole(0) {
        toFrac(decimal);
    }
    Frac::Frac(const char* fracStr, bool isSimplifying) : whole(0) {
        std::istringstream iss(fracStr);
        parseFromStream(iss, isSimplifying);
    }
    Frac::Frac(Frac& other){
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        this->whole = other.whole;
    }
    Frac::Frac(const Frac& other){
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        this->whole = other.whole;
    }


    //\\\\\\\\\\\\\\\\\\\\/
    // Basic Arithmetic Operators
    //\\\\\\\\\\\\\\\\\\\\/
    Frac Frac::operator+(const Frac& other) {
        // Check for overflow in the intermediate calculations
        if (willMultiplicationOverflow(this->numerator, other.denominator) || 
            willMultiplicationOverflow(other.numerator, this->denominator) || 
            willMultiplicationOverflow(this->denominator, other.denominator) || 
            willAdditionOverflow(this->numerator * other.denominator, other.numerator * this->denominator)) {
            throw std::overflow_error(OVERFLOW_ERROR);
        }

        return Frac((this->numerator * other.denominator) + (other.numerator * this->denominator), 
            this->denominator * other.denominator);
    }
    Frac Frac::operator+(int value){
        if(willMultiplicationOverflow(this->denominator, value)){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        if(willAdditionOverflow(this->numerator, (this->denominator * value))){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        return Frac(this->numerator + (this->denominator * value), this->denominator);
    }   
    Frac Frac::operator+(float value){
        return *(this) + Frac(value);
    };
    Frac Frac::operator+(const char* value){
        return *(this) + Frac(value);
    };
    
    Frac Frac::operator-(const Frac& other){
        if(willMultiplicationOverflow(this->numerator, other.denominator) || 
            willMultiplicationOverflow(this->denominator, other.numerator) || 
            willMultiplicationOverflow(this->denominator, other.denominator)){
                throw std::overflow_error(OVERFLOW_ERROR);
            }
        if(willSubtractionOverflow((this->numerator * other.denominator), (this->denominator * other.numerator))){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        return Frac((this->numerator * other.denominator) - (this->denominator * other.numerator), (this->denominator * other.denominator));
    }
    Frac Frac::operator-(int value){
        if(willMultiplicationOverflow(this->denominator, value)){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        if(willSubtractionOverflow(this->numerator, (this->denominator * value))){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        return Frac(this->numerator - (this->denominator * value), this->denominator);
    }   
    Frac Frac::operator-(float value){
        return *(this) - Frac(value);
    };
    Frac Frac::operator-(const char* value){
        return *(this) - Frac(value);
    };
    
    Frac Frac::operator*(const Frac& other){
        if(willMultiplicationOverflow(this->numerator, other.numerator) || 
            willMultiplicationOverflow(this->denominator, other.denominator)){
                throw std::overflow_error(OVERFLOW_ERROR);
            }
        return Frac(this->numerator * other.numerator, this->denominator * other.denominator);
    }
    Frac Frac::operator*(int value){
        if(willMultiplicationOverflow(this->numerator, value)){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        return Frac((this->numerator * value), this->denominator);
    }
    Frac Frac::operator*(float value){
        return *(this) * Frac(value);
    };
    Frac Frac::operator*(const char* value){
        return *(this) * Frac(value);
    };
    
    Frac Frac::operator/(const Frac& other){
        if (other.numerator == 0 || this->denominator == 0) {
            throw std::invalid_argument(ZERO_DIVISOR_ERROR);
        }
        if(willMultiplicationOverflow(this->numerator, other.denominator) || 
            willMultiplicationOverflow(this->denominator, other.numerator)){
                throw std::overflow_error(OVERFLOW_ERROR);
            }
        // reciprocal of other than multiply
        return Frac(this->numerator * other.denominator, this->denominator * other.numerator);
    }
    Frac Frac::operator/(int value){
        if (this->numerator == 0){
            throw std::invalid_argument(ZERO_DIVISOR_ERROR);
        }
        if(willMultiplicationOverflow(this->denominator, value)){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        // reciprocal
        return Frac((this->denominator * value), this->numerator);
    }
    Frac Frac::operator/(float value){
        return *(this) / Frac(value);
    };
    Frac Frac::operator/(const char* value){
        return *(this) / Frac(value);
    };

    // Reversed order
    Frac operator+(int value, const Frac& frac) {
        // Check for overflow in the intermediate calculations
        if (willMultiplicationOverflow(value, frac.denominator)) {
            throw std::overflow_error(Frac::OVERFLOW_ERROR);
        }
        if (willAdditionOverflow(frac.numerator, value * frac.denominator)) {
            throw std::overflow_error(Frac::OVERFLOW_ERROR);
        }

        // Perform the addition
        int newNumerator = frac.numerator + (value * frac.denominator);
        int newDenominator = frac.denominator;

        return Frac(newNumerator, newDenominator);
    }
    Frac operator+(float value, Frac& frac){
        return Frac(value) + frac;
    };
    Frac operator+(const char* value, Frac& frac){
        return Frac(value) + frac;
    };
    
    Frac operator-(int value, const Frac& frac){
        return Frac(frac.numerator - (frac.denominator * value), frac.denominator);
    };
    Frac operator-(float value, Frac& frac){
        return Frac(value) - frac;
    };
    Frac operator-(const char* value, Frac& frac){
        return Frac(value) - frac;
    };
    
    Frac operator*(int value, const Frac& frac){
        return Frac(frac.numerator * value, frac.denominator);
    };
    Frac operator*(float value, Frac& frac){
        return Frac(value) * frac;
    };
    Frac operator*(const char* value, Frac& frac){
        return Frac(value) * frac;
    };
    
    Frac operator/(int value, const Frac& frac){
        if (frac.numerator == 0) {
            throw std::invalid_argument("Division by zero not allowed. Denominator cannot be zero.");
        }
        if(willMultiplicationOverflow(value, frac.denominator)){
            throw std::overflow_error(Frac::OVERFLOW_ERROR);
        }
        return Frac(value * frac.denominator, frac.numerator);
    };
    Frac operator/(float value, Frac& frac){
        return Frac(value) / frac;
    };
    Frac operator/(const char* value, Frac& frac){
        return Frac(value) / frac;
    };
    

    //\\\\\\\\\\\\\\\\\\\\/
    // Compound Operators
    //\\\\\\\\\\\\\\\\\\\\/
    void Frac::operator+=(const Frac& other) {
        // Check for overflow in intermediate calculations
        if (willMultiplicationOverflow(this->numerator, other.denominator) ||
            willMultiplicationOverflow(other.numerator, this->denominator) ||
            willMultiplicationOverflow(this->denominator, other.denominator) ||
            willAdditionOverflow(this->numerator * other.denominator, other.numerator * this->denominator)) {
            throw std::overflow_error(OVERFLOW_ERROR);
        }

        // Calculate new numerator and denominator
        int newNumerator = (this->numerator * other.denominator) + (other.numerator * this->denominator);
        int newDenominator = this->denominator * other.denominator;

        // Update the fraction
        this->numerator = newNumerator;
        this->denominator = newDenominator;
    }
    void Frac::operator+=(int value){
        if(willMultiplicationOverflow(this->denominator, value)){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        if(willAdditionOverflow(this->numerator, (this->denominator * value))){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        this->numerator += (this->denominator * value);
    }
    void Frac::operator+=(float value){
        (*this) = *(this) + Frac(value);
    }
    void Frac::operator+=(const char* value){
        (*this) = *(this) + Frac(value);
    }

    void Frac::operator-=(const Frac& other){
        if(willMultiplicationOverflow(this->numerator, other.denominator) || 
            willMultiplicationOverflow(this->denominator, other.numerator) || 
            willMultiplicationOverflow(this->denominator, other.denominator)){
                throw std::overflow_error(OVERFLOW_ERROR);
            }
        if(willSubtractionOverflow((this->numerator * other.denominator), (this->denominator * other.numerator))){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        this->numerator = (this->numerator * other.denominator) - (this->denominator * other.numerator);
        this->denominator *= other.denominator;
    }
    void Frac::operator-=(int value){
        if(willMultiplicationOverflow(this->denominator, value)){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        if(willSubtractionOverflow(this->numerator, (this->denominator * value))){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        this->numerator = this->numerator - (this->denominator * value);
    }
    void Frac::operator-=(float value){
        (*this) = *(this) - Frac(value);
    }
    void Frac::operator-=(const char* value){
        (*this) = *(this) - Frac(value);
    }
    
    void Frac::operator*=(const Frac& other){
        if(willMultiplicationOverflow(this->numerator, other.numerator) || 
            willMultiplicationOverflow(this->denominator, other.denominator)){
                throw std::overflow_error(OVERFLOW_ERROR);
            }
        this->numerator *= other.numerator;
        this->denominator *= other.denominator;
    }
    void Frac::operator*=(int value){
        if(willMultiplicationOverflow(this->numerator, value)){
            throw std::overflow_error(OVERFLOW_ERROR);
        }
        this->numerator *= value;
    }
    void Frac::operator*=(float value){
        (*this) = *(this) * Frac(value);
    }
    void Frac::operator*=(const char* value){
        (*this) = *(this) * Frac(value);
    }
    
    void Frac::operator/=(const Frac& other){
        if (other.numerator == 0 || this->denominator == 0) {
            throw std::invalid_argument(ZERO_DIVISOR_ERROR);
        }
        if(willMultiplicationOverflow(this->numerator, other.denominator) || 
            willMultiplicationOverflow(this->denominator, other.numerator)){
                throw std::overflow_error(OVERFLOW_ERROR);
            }
        // reciprocal of other than multiply
        this->numerator *= other.denominator;
        this->denominator *= other.numerator;
    }
    void Frac::operator/=(int value){
        if (this->numerator == 0){
            throw std::invalid_argument(ZERO_DIVISOR_ERROR);
        }
        if(willMultiplicationOverflow(value, this->denominator)){
            throw std::overflow_error(Frac::OVERFLOW_ERROR);
        }
        // reciprocal of other than multiply
        this->numerator = this->denominator * value;
        this->denominator = this->numerator;
    }
    void Frac::operator/=(float value){
        (*this) = *(this) / Frac(value);
    }
    void Frac::operator/=(const char* value){
        (*this) = *(this) / Frac(value);
    }

    //\\\\\\\\\\\\\\\\\\\\/
    // Increment Decrement Operators
    //\\\\\\\\\\\\\\\\\\\\/
    void incrementLogic(int& whole, int& numerator, int& denominator, bool isPrefix){
        if (whole != 0) {
            
            numerator += whole * denominator; // Convert to improper fraction

            if (willAdditionOverflow(numerator, 1)) throw std::overflow_error(Frac::OVERFLOW_ERROR);
        
            if (isPrefix)
                ++numerator;
            else
                numerator++;

            // Convert back to mixed fraction
            whole = numerator / denominator;
            numerator %= denominator;

            // Ensure denominator is positive
            if (denominator < 0) {
                numerator = -numerator;
                denominator = -denominator;
            }
        }
        else {
            if (willAdditionOverflow(numerator, 1)) throw std::overflow_error(Frac::OVERFLOW_ERROR);
            if (isPrefix)
                ++numerator;
            else
                numerator++;
        }
    }

    void decrementLogic(int& whole, int& numerator, int& denominator, bool isPrefix){
        if (whole != 0) {
            
            numerator += whole * denominator; // Convert to improper fraction

            if (willAdditionOverflow(numerator, -1)) throw std::overflow_error(Frac::OVERFLOW_ERROR);
        
            if (isPrefix)
                --numerator;
            else
                numerator--;

            // Convert back to mixed fraction
            whole = numerator / denominator;
            numerator %= denominator;

            // Ensure denominator is positive
            if (denominator < 0) {
                numerator = -numerator;
                denominator = -denominator;
            }
        }
        else {
            if (willAdditionOverflow(numerator, 1)) throw std::overflow_error(Frac::OVERFLOW_ERROR);
            if (isPrefix)
                --numerator;
            else
                numerator--;
        }
    }

    Frac& Frac::operator++(){
        incrementLogic(this->whole, this->numerator, this->denominator, true);
        return *this;
    }
    Frac& Frac::operator--(){
        decrementLogic(this->whole, this->numerator, this->denominator, true);
        return *this;
    }
    Frac Frac::operator++(int){
        Frac temp = *this;
        incrementLogic(this->whole, this->numerator, this->denominator, false);
        return temp; 
    }
    Frac Frac::operator--(int){
        Frac temp = *this;
        decrementLogic(this->whole, this->numerator, this->denominator, false);
        return temp;
    }
    

    //\\\\\\\\\\\\\\\\\\\\/
    // Unary Operators
    //\\\\\\\\\\\\\\\\\\\\/
    Frac Frac::operator-(){
        // Handles negating numerator (+/-)
        if (this->whole != 0) return Frac(-this->whole, this->numerator, this->denominator);
        return Frac(-this->numerator, this->denominator);
    }


    //\\\\\\\\\\\\\\\\\\\\/
    // Comparision Operators
    //\\\\\\\\\\\\\\\\\\\\/
    bool Frac::operator==(const Frac& other) const {
        // Convert both fractions to improper form
        int lhsNumerator = this->whole * this->denominator + this->numerator;
        int rhsNumerator = other.whole * other.denominator + other.numerator;

        // This cross-multiplication avoids the need to reduce the fractions to their simplest forms.
        return (lhsNumerator * other.denominator) == (rhsNumerator * this->denominator);
    }
    bool Frac::operator==(float other) const {
        return (*this == Frac(other));
    }
    bool Frac::operator==(const char* other) const {
        return (*this == Frac(other));
    }
    bool operator==(float other, Frac& frac) {
        return (Frac(other) == frac);
    }
    bool operator==(const char* other, Frac& frac) {
        return (Frac(other) == frac);
    }

    bool Frac::operator!=(const Frac& other) const {
        return !(*this == other);  // implement != by negating ==
    }
    bool Frac::operator!=(float other) const {
        return !(*this == Frac(other));  // implement != by negating ==
    }
    bool Frac::operator!=(const char* other) const {
        return !(*this == Frac(other));  // implement != by negating ==
    }
    bool operator!=(float other, Frac& frac) {
        return (Frac(other) != frac);
    }
    bool operator!=(const char* other, Frac& frac) {
        return (Frac(other) != frac);
    }

    bool Frac::operator>=(const Frac& other) const {
        // Convert both fractions to improper form
        int lhsNumerator = this->whole * this->denominator + this->numerator;
        int rhsNumerator = other.whole * other.denominator + other.numerator;

        // This cross-multiplication avoids the need to reduce the fractions to their simplest forms.
        return (lhsNumerator * other.denominator) >= (rhsNumerator * this->denominator);
    }
    bool Frac::operator>=(float other) const {
        return (*this >= Frac(other));
    }
    bool Frac::operator>=(const char* other) const {
        return (*this >= Frac(other));
    }
    bool operator>=(float other, Frac& frac) {
        return (Frac(other) >= frac);
    }
    bool operator>=(const char* other, Frac& frac) {
        return (Frac(other) >= frac);
    }

    bool Frac::operator<=(const Frac& other) const {
        // Convert both fractions to improper form
        int lhsNumerator = this->whole * this->denominator + this->numerator;
        int rhsNumerator = other.whole * other.denominator + other.numerator;

        // This cross-multiplication avoids the need to reduce the fractions to their simplest forms.
        return (lhsNumerator * other.denominator) <= (rhsNumerator * this->denominator);
    }
    bool Frac::operator<=(float other) const {
        return (*this <= Frac(other));
    }
    bool Frac::operator<=(const char* other) const {
        return (*this <= Frac(other));
    }
    bool operator<=(float other, Frac& frac) {
        return (Frac(other) <= frac);
    }
    bool operator<=(const char* other, Frac& frac) {
        return (Frac(other) <= frac);
    }

    bool Frac::operator>(const Frac& other) const {
        // Convert both fractions to improper form
        int lhsNumerator = this->whole * this->denominator + this->numerator;
        int rhsNumerator = other.whole * other.denominator + other.numerator;

        // This cross-multiplication avoids the need to reduce the fractions to their simplest forms.
        return (lhsNumerator * other.denominator) > (rhsNumerator * this->denominator);
    }
    bool Frac::operator>(float other) const {
        return (*this > Frac(other));
    }
    bool Frac::operator>(const char* other) const {
        return (*this > Frac(other));
    }
    bool operator>(float other, Frac& frac) {
        return (Frac(other) > frac);
    }
    bool operator>(const char* other, Frac& frac) {
        return (Frac(other) > frac);
    }

    bool Frac::operator<(const Frac& other) const {
        // Convert both fractions to improper form
        int lhsNumerator = this->whole * this->denominator + this->numerator;
        int rhsNumerator = other.whole * other.denominator + other.numerator;

        // This cross-multiplication avoids the need to reduce the fractions to their simplest forms.
        return (lhsNumerator * other.denominator) < (rhsNumerator * this->denominator);
    }
    bool Frac::operator<(float other) const {
        return (*this < Frac(other));
    }
    bool Frac::operator<(const char* other) const {
        return (*this < Frac(other));
    }
    bool operator<(float other, Frac& frac) {
        return (Frac(other) < frac);
    }
    bool operator<(const char* other, Frac& frac) {
        return (Frac(other) < frac);
    }

    //\\\\\\\\\\\\\\\\\\\\/
    // Misc Operators
    //\\\\\\\\\\\\\\\\\\\\/
    std::ostream& operator<<(std::ostream& os, const Frac& frac) {
        if (frac.whole != 0)
            os << frac.whole << " ";
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }

    std::istream& operator>>(std::istream& is, Frac& frac){
        std::string input;

        // Read the entire input
        std::getline(is, input);

        // Trim any leading/trailing whitespace
        input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);
        input.erase(0, input.find_first_not_of(" \t\n\r\f\v"));

        // Check if the input is empty or invalid
        if (input.empty() || (!std::isdigit(input[0]) && input[0] != '-')) {
            is.setstate(std::ios::failbit);
            throw std::invalid_argument(
                "Invalid format: use decimal (0.5, 1.2) or string fractions (1/2, 2 1/2).");
        }

        // Attempt to parse as a double and convert to Frac object
        {
            std::istringstream iss(input);
            float value;

            if (iss >> value && iss.eof()) { 
                frac.toFrac(value);
                return is;
            }
        }

        // Attempt to parse string and convert to Frac object
        {
            std::istringstream iss(input);
            try {
                frac.parseFromStream(iss);
                return is;
            } catch (const std::invalid_argument& e) {
                is.setstate(std::ios::failbit);
                throw std::invalid_argument(e.what());
            } catch (const std::overflow_error& e) {
                is.setstate(std::ios::failbit); 
                throw std::overflow_error(Frac::OVERFLOW_ERROR);
            }
        }
        is.setstate(std::ios::failbit); // Mark stream as failed for invalid input
        return is;
    }

    Frac& Frac::operator=(const Frac& other){
        if (this != &other) {  // Check for self-assignment
            this->numerator = other.numerator;
            this->denominator = other.denominator;
        }
        return *this;
    }

    Frac& Frac::operator=(const char* str){
        std::istringstream iss(str);
        parseFromStream(iss);
        return *this;
    }

    Frac& Frac::operator=(float decimal){
        toFrac(decimal);
        return *this;
    }


    //\\\\\\\\\\\\\\\\\\\\/
    // Methods
    //\\\\\\\\\\\\\\\\\\\\/
    Frac Frac::toImproper(const Frac& frac) {
        Frac result = frac;

        result.numerator = (result.whole * result.denominator) + result.numerator;
        result.whole = 0;

        return result;
    }

    Frac Frac::toReciprocal(const Frac& frac) {
        if (frac.numerator == 0){
            throw std::invalid_argument(ZERO_DIVISOR_ERROR);
        }
        return Frac(frac.denominator, frac.numerator);
    }

    void Frac::SimplifyFrac(Frac& frac) {
        frac.simplify();
    }

    Frac Frac::Simplify(Frac frac) {
        frac.simplify();
        return frac;
    }
    
    void Frac::simplify() {
        if(denominator == 0) return; // quick fix for 0
        if (numerator == 0) { // Handle the case where numerator is 0
            whole = 0;
            denominator = 1; // Standardize to 0/1
            return;
        }

        // Determine the whole part and adjust the numerator
        whole += numerator / denominator;
        numerator %= denominator;

        // If the numerator is negative, adjust the whole and numerator
        if (numerator < 0 && whole != 0) {
            numerator += std::abs(denominator);
            whole -= (numerator > 0) ? 1 : 0;
        }


        int a = std::abs(numerator); // Use absolute values
        int b = std::abs(denominator);
        int gcd = 0;
        while (true) {
            if (a > b){
                a %= b;
                if(a == 0) {
                    gcd = b;
                    break;
                }
            } else {
                b %= a;
                if(b == 0) {
                    gcd = a;
                    break;
                }
            }
        }
        
        // Simplify the numerator and denominator
        numerator /= gcd;
        denominator /= gcd;

        // Ensure the denominator is always positive
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    std::string Frac::toString(const Frac& frac) {
        if (frac.whole != 0) return std::string(std::to_string(frac.whole) + " " + std::to_string(frac.numerator) + "/" + std::to_string(frac.denominator));
        return std::string(std::to_string(frac.numerator) + "/" + std::to_string(frac.denominator));
    }
    
    float Frac::toFloat(const Frac& frac) {
        int n = (frac.whole * frac.denominator) + frac.numerator; // attempt to form improper first
        return (float)n / (float)frac.denominator;
    }
    
    double Frac::toDouble(const Frac& frac) {
        int n = (frac.whole * frac.denominator) + frac.numerator; // attempt to form improper first
        return (double)n / (double)frac.denominator;
    }

    void Frac::toFrac(float decimal) {
        // Save sign information and make decimal absolute value
        int sign = (decimal < 0) ? -1 : 1;
        decimal = std::abs(decimal);

        // Convert decimal to string to count decimal places
        std::string decimalStr = std::to_string(decimal);
        size_t decimalPointPos = decimalStr.find('.');
        size_t decimalPlaces = decimalStr.size() - decimalPointPos - 1;

        // Remove trailing zeros
        while (decimalStr.back() == '0') {
            decimalStr.pop_back();
            decimalPlaces--;
        }

        // Build numerator and denominator
        denominator = static_cast<int>(std::pow(10, decimalPlaces));
        numerator = static_cast<int>(decimal * denominator + 0.5); // Rounding

        if(denominator == 0){
            throw std::invalid_argument(ZERO_DIVISOR_ERROR);
        }
        
        // Required
        simplify();
    }

    void Frac::parseFromStream(std::istream& is, bool isSimplifying) {
        is >> std::noskipws; // retain all whitespace characters including tab/newline etc
        
        // stack attrs
        int whole = 0, num = 0, denom = 1;
        char ch;
        
        auto isDigit = [&is]() {
            if (!std::isdigit(is.peek())){ // must be numeric or format is incorrect
                throw std::invalid_argument(INVALID_STRING_PARAMETER_ERROR);
            }
        };

        auto consumeWhitespace = [&is, &ch]() {
            // Skip leading whitespace, if any
            while (is.peek() == ' ' || is.peek() == '\t') {
                is.get(ch); // Consume the whitespace
            }
        };

        auto parseNumber = [&is]() {
            int temp = 0;
            while(std::isdigit(is.peek())){
                temp = (temp * std::pow(10,1)) + (is.peek() - 48); // builds full number using scientific notation. -48 gets actual numerical value instead of string representation
                is.get(); // consume
            }
            return temp;
        };

        consumeWhitespace();
        isDigit();
        num = parseNumber();

        if (is.peek() == EOF){ // Found whole number, not a fraction. (i.e. 1/1) 
            numerator = num;
            denominator = num;
            return;
        }

        // attempt to consume '/' or space for fraction or mixed fraction
        ch = is.peek();
        is.get();

        if (ch == ' ') { // potential mixed fraction
            whole = num; // claim the first number as the whole value

            consumeWhitespace();
            isDigit();
            num = parseNumber();

            // attempt to consume '/'
            ch = is.peek();
  
            if (is.peek() == EOF || ch != '/') { // strict condition at this point
                throw std::invalid_argument(INVALID_STRING_PARAMETER_ERROR);
            } else {
                is.get(); // consume
                consumeWhitespace();
                isDigit();
                denom = parseNumber();
            }
        }
        else if (ch == '/') {
            consumeWhitespace();
            isDigit();
            denom = parseNumber();
        }
        else {
            throw std::invalid_argument(INVALID_STRING_PARAMETER_ERROR);
        }
  
        consumeWhitespace();

        // Check for zero denominator
        if (denom == 0) {
            throw std::invalid_argument(ZERO_DIVISOR_ERROR);
        }

        // Assign parsed values to member variables
        denominator = denom;

        // Check for mixed fraction and calculate numerator
        if (whole != 0) {
            if (willMultiplicationOverflow(denominator, whole)) {
                throw std::overflow_error(OVERFLOW_ERROR);
            }
            numerator = denominator * whole;

            if (willAdditionOverflow(numerator, num)) {
                throw std::overflow_error(OVERFLOW_ERROR);
            }
            numerator += num;
        } else {
            numerator = num;
        }

        // Optional simplification
        if (isSimplifying) simplify();
    }

}
