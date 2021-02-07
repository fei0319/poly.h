# poly.h 文档

本文档是 [poly.h](https://github.com/FNatsuka/fstdlib/blob/master/source/poly.h) 的支持文档。您可以在此了解 poly.h 的使用方法。

## 基本介绍

poly.h 中定义了两个类，名为 `poly` 和 `m_poly`。它们都在命名空间 `fstdlib` 中。

其中，`poly` 是固定模数的多项式类，它的模数定义为 `fstdlib::mod`，默认值为 ![](http://latex.codecogs.com/gif.latex?998244353)。正常情况下，这个模数是一个常量。如果您需要修改它，您应当定义宏 `VARIABLE_MODULO`。您必须保证修改后：

- 模数是一个能够用于 NTT 的模数。换句话讲，它必须能表示为 ![](http://latex.codecogs.com/gif.latex?k\cdot%202^r+1) 的形式。
- 模数的两倍应当小于 32 位有符号整数的表示范围。

如果 ![](http://latex.codecogs.com/gif.latex?3) 不是您设定的模数的一个原根，您还应该将 `fstdlib::grt` 的值改为您设定模数的一个原根。

而 `m_poly` 是任意模数的多项式类。它的模数直接存储在实例中，您可以通过访问一个实例的 `mod` 成员来修改它。该种多项式的模数没有特别要求，但您仍应当保证：

- 模数的两倍应当小于 32 位有符号整数的表示范围。
- 任意两个进行运算的实例的模数相同。
- 如果模数不是质数，实例不能进行开根、求逆等运算。

`poly` 和 `m_poly` 的用法基本一致，但是构造方法不同。请您继续阅读以了解更多。

## 构造函数

|方法|简介|
|:-:|:-:|
|`poly(std::size_t n)`|构造一个长度为 ![](http://latex.codecogs.com/gif.latex?n) 的多项式，所有元素初始为 ![](http://latex.codecogs.com/gif.latex?0) 。|
|`poly(std::vector<int> a)`|用 ![](http://latex.codecogs.com/gif.latex?a) 来初始化一个多项式。|
|`m_poly(std::size_t n, int p)`|构造一个长度为 ![](http://latex.codecogs.com/gif.latex?n) 的任意模数多项式，所有元素初始为 ![](http://latex.codecogs.com/gif.latex?0)。多项式的模数被初始化为 ![](http://latex.codecogs.com/gif.latex?p) 。|
|`m_poly(std::vector<int> a, int p)`|用 ![](http://latex.codecogs.com/gif.latex?a) 来初始化一个任意模数多项式。多项式的模数被初始化为 ![](http://latex.codecogs.com/gif.latex?p) 。|

## 重载运算符和成员函数

|方法|简介|时间复杂度|
|:-:|:-:|:-:|
|`poly operator*(const poly &, const poly &)`|计算两个多项式的卷积。|![](http://latex.codecogs.com/gif.latex?O(n\log%20n)) |
|`poly &operator*=(poly &, const poly &)`|计算两个多项式的卷积。|![](http://latex.codecogs.com/gif.latex?O(n\log%20n)) |
|`poly operator*(const poly &, const int &`|计算多项式和单项式的卷积。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly &operator*=(poly &, const int &)`|计算多项式和单项式的卷积。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly operator*(const int &, const poly &)`|计算多项式和单项式的卷积。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly operator>>(const poly &, const int &)`|将多项式右移指定次。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly &operator>>=(poly &, const int &)`|将多项式右移指定次。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly operator<<(const poly &, const int &)`|将多项式左移指定次。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly &operator<<=(poly &, const int &)`|将多项式左移指定次。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly operator+(const poly &, const poly &)`|计算两个多项式的和。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly &operator+=(poly &, const poly &)`|计算两个多项式的和。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly operator+(const poly &, const int &`|计算多项式和单项式的和。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly &operator+=(poly &, const int &)`|计算多项式和单项式的和。|![](http://latex.codecogs.com/gif.latex?O(1)) |
|`poly operator+(const int &, const poly &)`|计算多项式和单项式的和。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly operator-(const poly &, const poly &)`|计算两个多项式的差。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly &operator-=(poly &, const poly &)`|计算两个多项式的差。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly operator-(const poly &, const int &`|计算多项式和单项式的差。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly &operator-=(poly &, const int &)`|计算多项式和单项式的差。|![](http://latex.codecogs.com/gif.latex?O(1)) |
|`poly operator-(const int &, const poly &)`|计算单项式和多项式的差。|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly operator/(const poly &, const int &)`|计算多项式和单项式的逆的卷积，|![](http://latex.codecogs.com/gif.latex?O(n)) |
|`poly operator/=(const poly &, const int &)`|计算多项式和单项式的逆的卷积，|![](http://latex.codecogs.com/gif.latex?O(n)) |

|方法|简介|时间复杂度|
|:-:|:-:|:-:|
|`poly poly::inv(void)const`|计算多项式相同次数的逆。|![](http://latex.codecogs.com/gif.latex?O(n\log%20n)) |
|`poly poly::inv(std::size_t)const`|计算多项式指定次数的逆。|![](http://latex.codecogs.com/gif.latex?O(n\log%20n)) |
|`poly poly::prefix(std::size_t)const`|计算多项式前若干项的和。允许参数大于多项式本身的长度。|![](http://latex.codecogs.com/gif.latex?O(n)) |

## 其他函数

|方法|简介|时间复杂度|
|:-:|:-:|:-:|
|`poly sqrt(const poly &)`|计算多项式的平方根。|![](http://latex.codecogs.com/gif.latex?O(n\log%20n))|
|`poly log(const poly &)`|计算多项式的自然对数。|![](http://latex.codecogs.com/gif.latex?O(n\log%20n))|
|`poly exp(const poly &)`|计算多项式的指数函数。|![](http://latex.codecogs.com/gif.latex?O(n\log%20n))|

目前尚未实现二次剩余，因此 `sqrt` 函数只有在多项式的常数项为 ![](http://latex.codecogs.com/gif.latex?1) 时才能正常工作。

由于本身的数学性质，`log` 函数的参数的常数项必须为 ![](http://latex.codecogs.com/gif.latex?1) ，`exp` 函数的参数的常数项必须为 ![](http://latex.codecogs.com/gif.latex?0) 。

## 计划

- 在卷积的两个多项式中的其中一个次数较小时，使用 ![](http://latex.codecogs.com/gif.latex?O(nm)) 的方法直接计算。
- 支持求二次剩余。
- 新增 `pow` 函数，计算多项式的指定次幂。
- 支持分治 NTT 实现的小常数 ![](http://latex.codecogs.com/gif.latex?O(n\log^2%20n)) 指数函数求法。
