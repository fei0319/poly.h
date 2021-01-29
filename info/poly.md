# Poly.h Info.

This is the informations related to poly.h. You can read an better rendered version [here]().

## Fixed Module Polynomial

The fixed module polynomial use specified integers as its module value, default 998244353. If you would like to modify the module value to $P$, you have to:
- $P$ has to be able to expressed as $a*2^k+1$, where $a$ and $k$ are postive integer, and $2^k$ is greater always greater than the length of all instances.
- Let $G$ be the [primitive root](https://en.wikipedia.org/wiki/Primitive_root_modulo_n) modulo $P$, you should assign $P$ and $G$ to `fstdlib::mod` and `fstdlib::grt` repectively.

The strict module restriction is caused by Fast Numerial Theory Tranform (FNTT) used to implement the class.

To create a fixed module polynomial instance, just call for `fstdlib::poly`. You can use the following method to initialize a `fstdlib::poly`:

|Name|Intro.|
|:-:|:-:|
|`poly(std::vector<int>)`|Initialize a polynomial with an vector.|
|`poly(std::size_t n = 0)`|Construct a polynomial of length n, with all elements set to zero.|

Some features are inherit from `std::vector`, like `void resize(std::size_t len, int val = 0)` and `std::size_t size(void)`. You can use it like to a vector.

Several operators are overloaded, some of them are listed in the following form:

|Operator|Intro.|Implement|
|:-:|:-:|:-:|
|`*` and `*=`|Calculate the convolution of two polynomials.|FNTT|

Some member functions are available. Check for them in the following form:

|Name|Intro.|Implement|
|:-:|:-:|:-:|
|`poly inv(int n = this->size())`|Calculate the inverse modulo $x^n$.|Newton's Method|
