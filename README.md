English | [中文](https://github.com/fei0319/poly.h/blob/master/README.zh.md)

# poly.h

POLY.H is a library that supports diverse polynomial calculation including linear computation, multiplication, inversion, square root, logarithm and exponent. Also, it supports polynomial with arbitrary modulus.

## Usage

POLY.H is implemented in C++. You only need to download the header file [poly.h](https://github.com/fei0319/poly.h/blob/master/source/poly.h).

There are two classes in POLY.H: `poly` and `m_poly`, both inside namespace `fstdlib`. You can call them by `fstdlib::poly` and `fstdlib::m_poly`, or simply use `using namespace fstdlib`.

---

`poly` is a polynomial class with fixed modulus `fstdlib::mod`, whose value is $998,244,353$ by default. This varible is constant. If you are to modify it, you have to define macro `VARIABLE_MODULO` in advance and ensure that:

- The new modulus can be used for NTT. In other words, it has to be a prime and can be represented by $k \cdot 2^r + 1$ where $k$ and $r$ are integers and $2^r$ is big enough.
- Twice this modulus is within the range of 32b signed integer.

Besides, if $3$ is not a primitive root of your modulus, you have set `fstdlib::grt` to a primitive root of your modulus.

---

`m_poly` is a polynomial class with arbitrary modulus `mod`, which is a 32b signed integer member of each single instance. You should ensure:

- Twice your modulus is within the range of 32b signed integer.
- Any instances that are calculated together have the same modulus.
- If the modulus is not a prime, no calculation except for linear computation and multiplication is applied.

## Constructors

|Method|Intro|
|:-:|:-:|
|`poly(std::size_t n)`|Create a polynomial of length $n$. All elements are initialized with $0$.|
|`poly(std::vector<int> a)`|Create a polynomial by a vector.|
|`m_poly(std::size_t n, int p)`|Create a polynomial of arbitrary modulus $p$ and length $n$. All elements are initialized with $0$.|
|`m_poly(std::vector<int> a, int p)`|Create a polynomial of arbitrary modulus $p$ by a vector.|

## Overloaded Operators

|Method|Intro|Time Complexity|
|:-:|:-:|:-:|
|`poly operator*(const poly &, const poly &)`      |Convolution of two polynomials.                         | $O(n\log n)$ |
|`poly &operator*=(poly &, const poly &)`          |Convolution of two polynomials.                         | $O(n\log n)$ |
|`poly operator*(const poly &, const int &`        |Convolution of a polynomial and a monomial.             | $O(n)$       |
|`poly &operator*=(poly &, const int &)`           |Convolution of a polynomial and a monomial.             | $O(n)$       |
|`poly operator*(const int &, const poly &)`       |Convolution of a polynomial and a monomial.             | $O(n)$       |
|`poly operator>>(const poly &, const int &)`      |Right shift of a polynomial.                            | $O(n)$       |
|`poly &operator>>=(poly &, const int &)`          |Right shift of a polynomial.                            | $O(n)$       |
|`poly operator<<(const poly &, const int &)`      |Left shift of a polynomial.                             | $O(n)$       |
|`poly &operator<<=(poly &, const int &)`          |Left shift of a polynomial.                             | $O(n)$       |
|`poly operator+(const poly &, const poly &)`      |Sum of two polynomials.                                 | $O(n)$       |
|`poly &operator+=(poly &, const poly &)`          |Sum of two polynomials.                                 | $O(n)$       |
|`poly operator+(const poly &, const int &`        |Sum of a polynomial and a monomial.                     | $O(n)$       |
|`poly &operator+=(poly &, const int &)`           |Sum of a polynomial and a monomial.                     | $O(1)$       |
|`poly operator+(const int &, const poly &)`       |Sum of a monomial and a polynomial.                     | $O(n)$       |
|`poly operator-(const poly &, const poly &)`      |Substraction of two polynomials.                        | $O(n)$       |
|`poly &operator-=(poly &, const poly &)`          |Substraction of two polynomials.                        | $O(n)$       |
|`poly operator-(const poly &, const int &`        |Substraction of a polynomial and a monomial.            | $O(n)$       |
|`poly &operator-=(poly &, const int &)`           |Substraction of a polynomial and a monomial.            | $O(1)$       |
|`poly operator-(const int &, const poly &)`       |Substraction of a monomial and a polynomial.            | $O(n)$       |
|`poly operator/(const poly &, const int &)`       |Division of a polynomial and a monomial.                | $O(n)$       |
|`poly operator/=(const poly &, const int &)`      |Division of a polynomial and a monomial.                | $O(n)$       |

## Member Functions

|Method|Intro|Time Complexity|
|:-:|:-:|:-:|
|`poly poly::inv(void)const`              |Inversoin of a polynomial.                                                         | $O(n\log n)$ |
|`poly poly::inv(std::size_t)const`       |Inversion of a polynomial of a specified length.                                   | $O(n\log n)$ |
|`poly poly::prefix(std::size_t)const`    |Prefix of a polynomial. The parameter can be greater than the polynomial's length. | $O(n)$       |

## Other Functions

|Method|Intro|Time Complexity|
|:-:|:-:|:-:|
|`poly sqrt(const poly &)`|Square root of a polynomial.| $O(n\log n)$ |
|`poly log(const poly &)` |Exponent of a polynomial.   | $O(n\log n)$ |
|`poly exp(const poly &)` |Logarithm of a polynomial.  | $O(n\log n)$ |

- The constant term of the polynomial `sqrt` applied to must be $1$.
- The constant term of the polynomial `log` applied to must be $1$.
- The constant term of the polynomial `exp` applied to must be $0$.