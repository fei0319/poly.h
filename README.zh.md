[English](https://github.com/fei0319/poly.h/blob/master/README.md) | 中文

# poly.h

POLY.H 是一个提供多项式线性运算、卷积、计算乘法逆、平方根、对数和指数的模板库。支持任意模数多项式。

## 用法

poly.h 中定义了两个类，名为 `poly` 和 `m_poly`。它们都在命名空间 `fstdlib` 中。

其中，`poly` 是固定模数的多项式类，它的模数定义为 `fstdlib::mod`，默认值为 $998,244,353$。正常情况下，这个模数是一个常量。如果您需要修改它，您应当定义宏 `VARIABLE_MODULO`。您必须保证修改后：

- 模数是一个能够用于 NTT 的模数。换句话讲，它必须能表示为 $O(k\cdot 2^r + 1)$ 的形式，且 $2^r$ 足够大。
- 模数的两倍应当在 32 位有符号整数的表示范围内。

如果 $3$ 不是您设定的模数的一个原根，您还应该将 `fstdlib::grt` 的值改为您设定模数的一个原根。

而 `m_poly` 是任意模数的多项式类。它的模数直接存储在实例中，您可以通过访问一个实例的 `mod` 成员来修改它。该种多项式的模数没有特别要求，但您仍应当保证：

- 模数的两倍应当在 32 位有符号整数的表示范围内。
- 任意两个进行运算的实例的模数相同。
- 如果模数不是质数，实例不能进行开根、求逆等运算。

## 构造函数

|方法|简介|
|:-:|:-:|
|`poly(std::size_t n)`|构造一个长度为  $O(n)$ 的多项式，所有元素初始为 $0$ 。|
|`poly(std::vector<int> a)`|用 $a$ 来初始化一个多项式。|
|`m_poly(std::size_t n, int p)`|构造一个长度为  $O(n)$ 的任意模数多项式，所有元素初始为 $0$。多项式的模数被初始化为 $p$ 。|
|`m_poly(std::vector<int> a, int p)`|用 $a$ 来初始化一个任意模数多项式。多项式的模数被初始化为 $p$ 。|

## 重载运算符

|方法|简介|时间复杂度|
|:-:|:-:|:-:|
|`poly operator*(const poly &, const poly &)`|计算两个多项式的卷积。| $O(n\log n)$ |
|`poly &operator*=(poly &, const poly &)`|计算两个多项式的卷积。| $O(n\log n)$ |
|`poly operator*(const poly &, const int &`|计算多项式和单项式的卷积。| $O(n)$ |
|`poly &operator*=(poly &, const int &)`|计算多项式和单项式的卷积。| $O(n)$ |
|`poly operator*(const int &, const poly &)`|计算多项式和单项式的卷积。| $O(n)$ |
|`poly operator>>(const poly &, const int &)`|将多项式右移指定次。| $O(n)$ |
|`poly &operator>>=(poly &, const int &)`|将多项式右移指定次。| $O(n)$ |
|`poly operator<<(const poly &, const int &)`|将多项式左移指定次。| $O(n)$ |
|`poly &operator<<=(poly &, const int &)`|将多项式左移指定次。| $O(n)$ |
|`poly operator+(const poly &, const poly &)`|计算两个多项式的和。| $O(n)$ |
|`poly &operator+=(poly &, const poly &)`|计算两个多项式的和。| $O(n)$ |
|`poly operator+(const poly &, const int &`|计算多项式和单项式的和。| $O(n)$ |
|`poly &operator+=(poly &, const int &)`|计算多项式和单项式的和。| $O(1)$ |
|`poly operator+(const int &, const poly &)`|计算多项式和单项式的和。| $O(n)$ |
|`poly operator-(const poly &, const poly &)`|计算两个多项式的差。| $O(n)$ |
|`poly &operator-=(poly &, const poly &)`|计算两个多项式的差。| $O(n)$ |
|`poly operator-(const poly &, const int &`|计算多项式和单项式的差。| $O(n)$ |
|`poly &operator-=(poly &, const int &)`|计算多项式和单项式的差。| $O(1)$ |
|`poly operator-(const int &, const poly &)`|计算单项式和多项式的差。| $O(n)$ |
|`poly operator/(const poly &, const int &)`|计算多项式和单项式的逆的卷积，| $O(n)$ |
|`poly operator/=(const poly &, const int &)`|计算多项式和单项式的逆的卷积，| $O(n)$ |

## 成员函数

|方法|简介|时间复杂度|
|:-:|:-:|:-:|
|`poly poly::inv(void)const`|计算多项式相同次数的逆。| $O(n\log n)$ |
|`poly poly::inv(std::size_t)const`|计算多项式指定次数的逆。| $O(n\log n)$ |
|`poly poly::prefix(std::size_t)const`|计算多项式前若干项的和。允许参数大于多项式本身的长度。| $O(n)$ |

## 其他函数

|方法|简介|时间复杂度|
|:-:|:-:|:-:|
|`poly sqrt(const poly &)`|计算多项式的平方根。| $O(n\log n)$|
|`poly log(const poly &)`|计算多项式的自然对数。| $O(n\log n)$|
|`poly exp(const poly &)`|计算多项式的指数函数。| $O(n\log n)$|

- 作为 `sqrt` 参数的多项式的常数项必须为 $1$。
- 作为 `log` 参数的多项式的常数项必须为 $1$。
- 作为 `exp` 参数的多项式的常数项必须为 $0$。