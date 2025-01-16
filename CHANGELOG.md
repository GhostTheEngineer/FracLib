# Changelog
This file shows this current version only. To view past changes, please navigate to past versions via GitHub.

## Version 1.1.0
**WIP** - this version is not complete yet. The following needs must be met to now consider `whole` numbers:
- Arithmetic operations
- Relational operations
- Increment/Decrement operations
- toString, toDouble and toFloat

The addition of improper fraction support and `whole` number attribute fixes some expectation issues - for instance `Frac f(1.5f);` expects `1 1/2` but got `1/2`.

### Addition
- Added new attribute, `whole` which represents the whole number value for mixed fractions.
- `Frac toImproper(const Frac&)` is a new function to attempt to convert a fraction to an improper fraction. Returns new Frac object.

### Changes 
- `simplify()` now handles whole numbers.
- Insertion operator for printing no handles printing whole numbers, if `whole` is not equal to 0.
- Constructions now support setting `whole` number.
- Copy constructor now supports constant and non-constant Frac object argument.
- Improper example added to the `example` project. Also, added a string before input line.

### Fixes
- Constructors with `isSimplifying` flag option caused issues with other constructor like `Frac(int w, int n, int d)` due integer implicit. Now defined as explicit.