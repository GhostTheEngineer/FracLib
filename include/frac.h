/******************************************************************************
 * Project: FracLib
 * File: Frac.h
 * Description:
 *  This header file defines the Frac class within the FracLib namespace, 
 *  which provides functionality for handling and performing operations on fractions. 
 *  The Frac class includes constructors for initializing fractions, 
 *  operators for arithmetic and comparison, as well as methods for 
 *  simplifying fractions, converting to and from different representations, 
 *  and performing utility tasks such as parsing strings and handling decimals.
 *  Comprehensive error handling is implemented for invalid inputs and edge cases, 
 *  ensuring robust functionality. This file also declares static constants 
 *  for error messages and a suite of static and private utility functions 
 *  for advanced operations and internal management.
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

#pragma once
#include <stdexcept>

namespace FracLib {
    class Frac {
    public: // ERROR STRINGS
        static const char* ZERO_DIVISOR_ERROR;
        static const char* OVERFLOW_ERROR;
        static const char* INVALID_STRING_PARAMETER_ERROR;
    public: // ATTRIBUTES
        int numerator;
        int denominator;
        int whole;

    public: // CONSTRUCTORS
        /// @brief Default constructor. Initializes the fraction to `0/1`.
        /// @example Frac f; // Represents 0/1
        Frac();
        /// @brief Constructs a Frac object with the given integer numerator.
        /// @param n The integer numerator (denominator is set to 1).
        /// @example Frac f(5); // Creates a fraction representing 5/1
        Frac(int n);
        /// @brief Constructs a Frac object with the specified numerator and denominator.
        /// @param n The numerator.
        /// @param d The denominator.
        /// @param isSimplifying Determines whether the fraction will attempt to simplify or not.
        /// @throws std::invalid_argument If the denominator is zero.
        /// @example Frac f(3, 4); // Creates a fraction representing 3/4
        explicit Frac(int n, int d, bool isSimplifying = false);
        /// @brief Constructs a mixed fraction object.
        /// This constructor initializes a `Frac` object with a whole number part, a numerator, 
        /// and a denominator. The whole number (`w`) represents the integer part of the fraction, 
        /// while the numerator (`n`) and denominator (`d`) represent the fractional part.
        /// @param w The whole number part of the mixed fraction.
        /// @param n The numerator of the fractional part.
        /// @param d The denominator of the fractional part. Must not be zero.
        /// @param isSimplifying Determines whether the fraction will attempt to simplify or not.
        /// @note If the denominator is zero, the behavior is undefined. Ensure the denominator 
        ///       is properly validated before calling this constructor.
        explicit Frac(int w, int n, int d, bool isSimplifying = false);
        /// @brief Constructs a Frac object from a decimal number by approximating its fractional equivalent.
        /// The fraction is then simplified automatically.
        /// @param decimal The decimal number to convert to a fraction.
        /// @example Frac f(0.75); // Creates a fraction representing 3/4
        Frac(float decimal);
        /// @brief Constructs a Frac object by parsing a c-string representation.
        /// @param fracStr The c-string representing the fraction, in the format "numerator/denominator", "numerator" or "whole numerator/denominator".
        /// @param isSimplifying Determines whether the fraction will simplify or not.
        /// @throws std::invalid_argument if the string is not properly formatted or if the denominator is zero.
        /// @example Frac f("3/4"); // Creates a fraction representing 3/4
        explicit Frac(const char* fracStr, bool isSimplifying = false);
        /// @brief Copy constructor. Creates a new Frac object as a copy of an existing Frac.
        /// @param other The Frac object to copy.
        Frac(Frac& other);
        /// @brief Copy constructor. Creates a new Frac object as a copy of an existing const Frac.
        /// @param other The Frac object to copy.
        Frac(const Frac& other);

    public: // OPERATORS
        
        // Basic Arithmetic
        Frac operator+(const Frac& other);
        Frac operator+(int value);
        Frac operator+(float value);
        Frac operator+(const char* value);

        Frac operator-(const Frac& other);
        Frac operator-(int value);
        Frac operator-(float value);
        Frac operator-(const char* value);

        Frac operator*(const Frac& other);
        Frac operator*(int value);
        Frac operator*(float value);
        Frac operator*(const char* value);

        Frac operator/(const Frac& other);
        Frac operator/(int value);
        Frac operator/(float value);
        Frac operator/(const char* value);
        
        // Reversed operand order
        friend Frac operator+(int value, const Frac& frac);
        friend Frac operator+(int value, Frac& frac);
        friend Frac operator+(float value, Frac& frac);
        friend Frac operator+(const char* value, Frac& frac);

        friend Frac operator-(int value, const Frac& frac);
        friend Frac operator-(int value, Frac& frac);
        friend Frac operator-(float value, Frac& frac);
        friend Frac operator-(const char* value, Frac& frac);

        friend Frac operator*(int value, const Frac& frac);
        // friend Frac operator*(int value, Frac& frac);
        friend Frac operator*(float value, Frac& frac);
        friend Frac operator*(const char* value, Frac& frac);

        friend Frac operator/(int value, const Frac& frac);
        friend Frac operator/(int value, Frac& frac);
        friend Frac operator/(float value, Frac& frac);
        friend Frac operator/(const char* value, Frac& frac);
        
        // Compound
        void operator+=(const Frac& other);
        void operator+=(int value);
        void operator+=(float value);
        void operator+=(const char* value);

        void operator-=(const Frac& other);
        void operator-=(int value);
        void operator-=(float value);
        void operator-=(const char* value);

        void operator*=(const Frac& other);
        void operator*=(int value);
        void operator*=(float value);
        void operator*=(const char* value);

        void operator/=(const Frac& other);
        void operator/=(int value);
        void operator/=(float value);
        void operator/=(const char* value);
        
        // Increment/Decrement Post/Pre
        Frac& operator++();
        Frac& operator--();
        Frac operator++(int);
        Frac operator--(int);

        // Unary
        Frac operator-();

        // Comparision
        bool operator==(const Frac& other) const;
        bool operator==(float other) const;
        bool operator==(const char* other) const;
        friend bool operator==(float other, Frac& frac);
        friend bool operator==(const char* other, Frac& frac);

        bool operator!=(const Frac& other) const;
        bool operator!=(float other) const;
        bool operator!=(const char* other) const;
        friend bool operator!=(float other, Frac& frac);
        friend bool operator!=(const char* other, Frac& frac);

        bool operator>=(const Frac& other) const;
        bool operator>=(float other) const;
        bool operator>=(const char* other) const;
        friend bool operator>=(float other, Frac& frac);
        friend bool operator>=(const char* other, Frac& frac);

        bool operator<=(const Frac& other) const;
        bool operator<=(float other) const;
        bool operator<=(const char* other) const;
        friend bool operator<=(float other, Frac& frac);
        friend bool operator<=(const char* other, Frac& frac);

        bool operator>(const Frac& other) const;
        bool operator>(float other) const;
        bool operator>(const char* other) const;
        friend bool operator>(float other, Frac& frac);
        friend bool operator>(const char* other, Frac& frac);

        bool operator<(const Frac& other) const;
        bool operator<(float other) const;
        bool operator<(const char* other) const;
        friend bool operator<(float other, Frac& frac);
        friend bool operator<(const char* other, Frac& frac);

        // Assignment
        Frac& operator=(const Frac& other);
        Frac& operator=(const char* str);
        Frac& operator=(float decimal);

        // Insertion/Extraction
        friend std::ostream& operator<<(std::ostream& os, const Frac& frac);
        friend std::istream& operator>>(std::istream& is, Frac& frac);

    public: // STATIC METHODS
        
        /// @brief Best use is for inline math operations. Simplifies a Frac object using GCD(Greatest Common Divisor).
        /// @param frac Frac value object.
        static Frac Simplify(Frac frac);
        /// @brief Best use is for straight-forward simplification. Simplifies a Frac object using GCD(Greatest Common Divisor).
        /// @param frac Frac reference object.
        static void SimplifyFrac(Frac& frac);
        /// @brief Converts a Frac object to a string (ie. "1/2").
        /// @param frac Frac object
        /// @return fraction as string
        static std::string toString(const Frac& frac);
        static float toFloat(const Frac& frac);
        /// @brief Converts a fraction to a floating decimal.
        /// @param frac Frac object.
        /// @return fraction as float.
        static double toDouble(const Frac& frac);
        /// @brief Returns the reciprocal of a fraction as a new Frac object.
        /// @param frac fraction to get reciprocal of
        /// @return fraction reciprocal
        static Frac toReciprocal(const Frac& frac);
        /// @brief Converts a mixed fraction to an improper fraction.
        /// This function takes a mixed fraction (with a whole number part, numerator, and denominator) 
        /// and converts it into an improper fraction. The resulting fraction has no whole number part, 
        /// and its numerator is adjusted to represent the entire fraction in improper form.
        /// @param frac A `Frac` object representing the mixed fraction to be converted.
        /// @return A `Frac` object representing the improper fraction equivalent of the input.
        /// @note The input fraction (`frac`) remains unmodified. The function creates and returns 
        ///       a new `Frac` object with the converted values.
        static Frac toImproper(const Frac& frac);
    private: // PRIVATE FUNCTIONS
        /// @brief Simplifies this object fraction(numerator/denominator) using GCD method.
        void simplify();
        /// @brief Parses input stream fractions to Frac members numerator and denominator.
        /// @param is input stream.
        /// @param simplify optional, simplify fraction.
        void parseFromStream(std::istream& is, bool isSimplifying = false);
        /// @brief Converts a decimal into a Frac by assigning the numerator and denominator
        /// to this Frac object. The Frac is simplified.
        /// @param decimal decimal to convert to fraction.
        void toFrac(float decimal);
    };
}


