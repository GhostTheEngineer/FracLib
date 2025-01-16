# Changelog
This file shows this current version only. To view past changes, please navigate to past versions via GitHub.

## Version 1.1.0
**WIP** - this version is not complete yet. The following needs must be met to now consider `whole` numbers:
- Arithmetic operations

The addition of improper fraction support and `whole` number attribute fixes some expectation issues - for instance `Frac f(1.5f);` expects `1 1/2` but got `1/2`.

### Addition
- Added new attribute, `whole` which represents the whole number value for mixed fractions.
- `Frac toImproper(const Frac&)` is a new function to attempt to convert a fraction to an improper fraction. Returns new Frac object.
- `/tests` for testing functionality easily using a custom test framework and main to run the tests. Use `./test.bat` to compile and run test.

### Changes 
- `simplify()` now handles whole numbers.
- Insertion operator for printing no handles printing whole numbers, if `whole` is not equal to 0.
- Constructions now support setting `whole` number.
- Copy constructor now supports constant and non-constant Frac object argument.
- Improper example added to the `example` project. Also, added a string before input line.
- `toString`, `toDouble` and `toFloat` now support whole numbers.
- Negation operator now handles `whole` numbers(mixed fractions) and the negative sign is placed on the `whole` number if not equal to zero or placed on numerator if is zero.
- Pre/Post Increment/Decrement operators now handles `whole` numbers(mixed fractions). Also, removed logic from the actual methods into hidden functions inside the cpp file called `incrementLogic()` and `decrementLogic()`.
- Relational operators now handles `whole` numbers(mixed fractions).

### Fixes
- Constructors with `isSimplifying` flag option caused issues with other constructor like `Frac(int w, int n, int d)` due integer implicit. Now defined as explicit.