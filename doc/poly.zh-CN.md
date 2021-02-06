# poly.h 文档

本文档是 [poly.h](https://raw.githubusercontent.com/FNatsuka/fstdlib/poly/source/poly.h) 的支持文档。您可以在此了解 poly.h 的使用方法。

## 基本介绍

poly.h 中定义了两个类，名为 `poly` 和 `m_poly`。它们都在命名空间 `fstdlib` 中。

其中，`poly` 是固定模数的多项式类，它的模数定义为 `fstdlib::mod`，默认值为 ![](http://latex.codecogs.com/gif.latex?998244353)。这个模数是一个变量，您可以随时修改它，但您必须保证：

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
|`poly(std::size_t n)`|构造一个长度为 ![](http://latex.codecogs.com/gif.latex?n) 的多项式，所有元素初始为 ![](http://latex.codecogs.com/gif.latex?0)。|
|`poly(std::vector<int> a)`|用 ![](http://latex.codecogs.com/gif.latex?a) 来初始化一个多项式。|
|`m_poly(std::size_t n, int p)`|构造一个长度为 ![](http://latex.codecogs.com/gif.latex?n) 的任意模数多项式，所有元素初始为 ![](http://latex.codecogs.com/gif.latex?0)。多项式的模数被初始化为 ![](http://latex.codecogs.com/gif.latex?p)。|
|`m_poly(std::vector<int> a, int p)`|用 ![](http://latex.codecogs.com/gif.latex?a) 来初始化一个任意模数多项式。多项式的模数被初始化为 ![](http://latex.codecogs.com/gif.latex?p)。|

**下面部分尚未完工。暂且使用较为口语化的语言大致描述。**

## 重载运算符和成员函数

支持 `*`，`*=` 等一系列运算，能用到的都有。只有以多项式为右值的除法没有定义，因为我认为这种运算不太严谨。

通过以 `inv` 为名的成员函数可以计算多项式的乘法逆。如果没有提供参数，则默认计算模 ![](http://latex.codecogs.com/gif.latex?x^n) 意义下的逆，否则计算模指定幂意义下的逆。

## 其他函数

`sqrt`，`log`，`exp` 都已实现。`log` 使用求导后积分的方法求，其余两个都是通过牛顿迭代法求。
