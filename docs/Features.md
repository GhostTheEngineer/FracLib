# FracLib Features

## Current Features

### Fraction Representation

- Store fractions as two integers: numerator and denominator.

### Constructors

- **Default Constructor**: Initializes fraction to `0/1`.
- **Parameterized Constructor**:
  - Numerator `Fraction(int n)`, denominator initializes to 1 (`x/1`).
  - Numerator and denominator `Fraction(int n, int d)`.
  - Decimal `Fraction(double decimal)` converts decimal to fraction.
  - String `Fraction(const char* fracStr)` parses string to fraction.
- **Copy Constructor**: Creates a new fraction from an existing one.

### Arithmetic Operations
All arithmetic operations do not simplify the fraction results automatically and require the user to manually apply simplification if needed using the `Simplify()` class function.

- **Addition (`+`)**: 
  - Fraction
    `Fraction + Fraction`
  - Integer
    - `Fraction + Integer`
    - `Integer + Fraction`
  - Decimal
    - `Fraction + Double`
    - `Double + Fraction`
  - String
    - `Fraction + String`
    - `String + Fraction`
- **Subtraction (`-`)**: 
  - Fraction
    `Fraction - Fraction`
  - Integer
    - `Fraction - Integer`
    - `Integer - Fraction`
  - Decimal
    - `Fraction - Double`
    - `Double - Fraction`
  - String
    - `Fraction - String`
    - `String - Fraction`
- **Multiplication (`*`)**: 
  - Fraction
    `Fraction * Fraction`
  - Integer
    - `Fraction * Integer`
    - `Integer * Fraction`
  - Decimal
    - `Fraction * Double`
    - `Double * Fraction`
  - String
    - `Fraction * String`
    - `String * Fraction`
- **Division (`/`)**: 
  - Fraction
    `Fraction / Fraction`
  - Integer
    - `Fraction / Integer`
    - `Integer / Fraction`
  - Decimal
    - `Fraction / Double`
    - `Double / Fraction`
  - String
    - `Fraction / String`
    - `String / Fraction`
- **Compound Assignment Operators**: `+=`, `-=`, `*=`, `/=` equivalents for all arithmetic operations listed above.

### Unary Operators

- **Unary Minus (`-`)**: Negates the fraction. Uses the numerator rule meaning negation only happens at the numerator.

### Increment and Decrement Operators

- **Prefix (`++Fraction`, `--Fraction`)**: Increments/decrements the fraction by 1.
- **Postfix (`Fraction++`, `Fraction--`)**: Same as prefix but returns the original value before increment/decrement.

### Comparison Operators

- **Equality (`==`)**: Checks if two fractions are equal. Supports decimal and string fraction representations (`0.5 == Fraction` `1/2 == Fraction`).
- **Inequality (`!=`)**: Checks if two fractions are not equal. Supports decimal and string fraction representations (`0.5 != Fraction` `1/2 != Fraction`).
- **Relational Operators**: `<`, `>`, `<=`, `>=` for comparing fractions. Supports decimal and string fraction representations (`0.5 < Fraction` `1/2 >= Fraction`).

### Assignment Operator

- Overload `operator=` to handle assignment of fractions including decimals and string of fraction representations.

### Conversion Operators

- **To Floating-Point**: Converts fraction to `double` or `float`.
- **To String**: Provides a string representation (`"numerator/denominator"`).
- **To Fraction(decimal)**: Converts a decimal to Fraction object. Also, simplifies the fraction.

### Input/Output Stream Operators

- **Extraction (`>>`)**: Reads fraction from an input stream. Supports decimal(`0.5`) or string fraction representation(`1/2`).
- **Insertion (`<<`)**: Writes fraction to an output stream.

### Exception Handling

- **Zero Denominator**: Throws an exception.
- **Overflow Handling**: Throws an exception.

### Normalization and Simplification

- **Greatest Common Divisor (GCD)**: Used to simplify fractions to their lowest terms.
- **Normalization**: Ensures that:
  - Denominator is always positive.
  - Only numerator carries the sign.

### Reciprocal Function

- Provides a method to compute the reciprocal of a fraction (`toReciprocal(Fraction)`).

### Namespace Encapsulation

- The entire library is placed inside of the FracLib namespace.

---

## Future Features

### Absolute Value Function

- Returns the fraction with a positive numerator and denominator.

### Power Functions

- **Integer Exponents**: Raises the fraction to an integer power.
- **Square Root**: Calculates the square root if applicable (may return an approximate value).

### Accessors and Mutators

- **Getters**: Retrieve numerator and denominator.
- **Setters**: Set numerator and denominator with validation.

### Static Utility Functions

- **GCD and LCM Functions**: May be useful outside of fraction simplification.

### Template Support

- Allow the fraction to work with different integer types (e.g., `int`, `long`, `BigInt`).

### Immutability Options

- Mutable and immutable versions of your fraction objects.

### Memory Management

- Ensure efficient memory usage, especially if using dynamic memory allocation.

### Compatibility with Standard Library

- Implement standard type traits and concepts to make fractions work with STL algorithms and containers.

### Hash Function

- Overload `std::hash` to allow fractions to be used in unordered containers like `unordered_map`.

### Serialization Support

- Provide methods to serialize and deserialize fractions for storage or network transmission.

### Fractional Math Functions

- Implement functions like `floor`, `ceil`, and `round` that work with fractions.

### Extended Mathematical Operations

- **Modulus Operation (`%`)**: Define behavior for the modulus of fractions if applicable.

### Thread Safety

- Ensure that FracLib is safe to use in multi-threaded applications.

### Performance Optimization

- Optimize algorithms for simplification and arithmetic operations.
- Avoid unnecessary copying by using move semantics where appropriate.
- Find more(if any) performance issues and address.

### Edge Case Handling

- Define behavior when dealing with special cases like `0/0`, `1/0`, and large numbers rather than just exception.

### Custom Exception Classes

- Define a more robust custom exceptions for more granular error handling.

### Comparison with Tolerance

- For floating-point approximations, provide methods to compare fractions within a certain tolerance.

### Policy-Based Design Options

- Allow users to define policies for overflow handling, simplification, and arithmetic behavior.

### Plug-in Architecture

- Design the library to be extensible for future features like complex fractions or symbolic computation.
