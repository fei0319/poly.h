/*
 * This file is part of the fstdlib project.
 * Version: Build v0.0.3
 * This is not a stable version. You can check for details and get the latest version at https://github.com/FNatsuka/fstdlib
 * If you have discovered any bugs, please report about it at https://github.com/FNatsuka/fstdlib/issues/new
 */

#ifndef _FEISTDLIB_POLY_
#define _FEISTDLIB_POLY_

#if __cplusplus >= 201103L
#define _FEISTDLIB_CPP11_
#endif

#include <cmath>
#include <cstdio>

#include <vector>
#include <stdexcept>
#include <algorithm>

namespace fstdlib{

	typedef long long ll;
	
#ifndef VARIABLE_MODULO
	const int mod = 998244353, grt = 3;
#else
	int mod = 998244353, grt = 3;
#endif
	
	class poly{
	private:
		std::vector<int> data;
	public:
		poly(std::size_t len = std::size_t(0)){data = std::vector<int>(len); }
		poly(const std::vector<int> &b){data = b; }
		poly(const poly &b){data = b.data; }
		void resize(std::size_t len, int val = 0){data.resize(len, val); }
		std::size_t size(void)const{return data.size(); }
		void clear(void){data.clear(); }
#ifdef _FEISTDLIB_CPP11_
		void shrink_to_fit(void){data.shrink_to_fit(); }
#endif
		int &operator[](std::size_t b){return data[b]; }
		const int &operator[](std::size_t b)const{return data[b]; }
		
		poly prefix(std::size_t len)const;

		friend poly operator*(const poly &, const poly &);
		friend poly &operator*=(poly &, const poly &);
		
		friend poly operator+(const poly &, const poly &);
		friend poly &operator+=(poly &, const poly &);
		friend poly operator-(const poly &, const poly &);
		friend poly &operator-=(poly &, const poly &);
		
		friend poly operator*(const poly &, const int &);
		friend poly &operator*=(poly &, const int &);
		friend poly operator+(const poly &, const int &);
		friend poly &operator+=(poly &, const int &);
		friend poly operator-(const poly &, const int &);
		friend poly &operator-=(poly &, const int &);
		
		friend poly operator*(const int &, const poly &);
		friend poly operator+(const int &, const poly &);
		friend poly operator-(const int &, const poly &);
		
		poly inv(void)const;
		poly inv(std::size_t)const;
		
		friend poly operator/(const poly &, const int &);
		friend poly &operator/=(poly &, const int &);

		friend poly sqrt(const poly &);
		friend poly log(const poly &);
		friend poly exp(const poly &);
	};
	
	class arbitrary_modulo_poly{
	private:
		std::vector<int> data;
	public:
		int mod;
		arbitrary_modulo_poly(std::size_t len = std::size_t(0), int modulo = 1e9 + 7){mod = modulo, data = std::vector<int>(len); }
		arbitrary_modulo_poly(const std::vector<int> &b, int modulo = 1e9 + 7){mod = modulo, data = b; }
		void resize(std::size_t len, const int &val = 0){data.resize(len, val); }
		std::size_t size(void)const{return data.size(); }
		void clear(void){data.clear(); }
#ifdef _FEISTDLIB_CPP11_
		void shrink_to_fit(void){data.shrink_to_fit(); }
#endif
		int &operator[](std::size_t b){return data[b]; }
		const int &operator[](std::size_t b)const{return data[b]; }
		
		arbitrary_modulo_poly prefix(std::size_t len)const;

		friend arbitrary_modulo_poly operator*(const arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly &operator*=(arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		
		friend arbitrary_modulo_poly operator+(const arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly &operator+=(arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly operator-(const arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly &operator-=(arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		
		friend arbitrary_modulo_poly operator*(const arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly &operator*=(arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly operator+(const arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly &operator+=(arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly operator-(const arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly &operator-=(arbitrary_modulo_poly &, const int &);
		
		friend arbitrary_modulo_poly operator*(const int &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly operator+(const int &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly operator-(const int &, const arbitrary_modulo_poly &);

		arbitrary_modulo_poly inv(void)const;
		arbitrary_modulo_poly inv(std::size_t)const;
		
		friend arbitrary_modulo_poly operator/(const arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly &operator/=(arbitrary_modulo_poly &, const int &);

		friend arbitrary_modulo_poly sqrt(const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly log(const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly exp(const arbitrary_modulo_poly &);
	};
	
	typedef arbitrary_modulo_poly m_poly;
	
	namespace _FEISTDLIB_SECURITY_{
		const char
			*MODULO_DIF_ERROR = "The modulo of the two polynomial computed should be same.",
			*OUT_OF_CONVERGENCE_RADIUS = "The power series of logarithm/exponential of the polynomial does not converge.",
			*INVERSE_NOT_EXIST = "The inverse element of the polynomial/integer does not exist."; 
		
		int qpow(int a, int b, int p = mod){
			int res = 1;
			while(b){if(b & 1) res = (ll)res * a % p; a = (ll)a * a % p, b >>= 1; }
			return res;
		}
		
		inline int modulo_sqrt(int a, int p){
			return 1;
		}
		
		const long double PI = std::acos((long double)(-1)), EPS = 1e-18;
		
		template <typename FLOAT_T>
		FLOAT_T fabs(const FLOAT_T &x){
			return x > 0 ? x : -x;
		}
		
		template <typename FLOAT_T>
		FLOAT_T sin(const FLOAT_T &x, const long double &EPS = fstdlib::_FEISTDLIB_SECURITY_::EPS){
			FLOAT_T res = 0, delt = x;
			int d = 0;
			while(fabs(delt) > EPS){
				res += delt, ++d;
				delt *= - x * x / ((2 * d) * (2 * d + 1));
			}
			return res;
		}
		
		template <typename FLOAT_T>
		FLOAT_T cos(const FLOAT_T &x, const long double &EPS = fstdlib::_FEISTDLIB_SECURITY_::EPS){
			FLOAT_T res = 0, delt = 1;
			int d = 0;
			while(fabs(delt) > EPS){
				res += delt, ++d;
				delt *= - x * x / ((2 * d) * (2 * d - 1));
			}
			return res;
		}
		
		struct comp{
			long double x, y;
			comp(long double _x = 0, long double _y = 0) : x(_x), y(_y) {}
			comp operator*(const comp &b)const{return comp(x * b.x - y * b.y, x * b.y + y * b.x); }
			comp operator+(const comp &b)const{return comp(x + b.x, y + b.y); }
			comp operator-(const comp &b)const{return comp(x - b.x, y - b.y); }
			comp conj(void){return comp(x, -y); }
		};
		
		std::vector<int> rev;
		void dft_for_modulo(std::vector<int>::iterator f, int n, int b){
			static std::vector<int> w;
			w.resize(n);
			for(int i = 0; i < n; ++i) if(i < rev[i]) std::swap(f[i], f[rev[i]]);
			for(int i = 2; i <= n; i <<= 1){
				w[0] = 1, w[1] = qpow(grt, (mod - 1) / i); if(b == -1) w[1] = qpow(w[1], mod - 2);
				for(int j = 2; j < i / 2; ++j) w[j] = (ll)w[j - 1] * w[1] % mod;
				for(int j = 0; j < n; j += i){
					std::vector<int>::iterator g = f + j, h = f + j + i / 2;
					for(int k = 0; k < i / 2; ++k){
						int p = g[k], q = (ll)h[k] * w[k] % mod;
						g[k] = (p + q) % mod, h[k] = (p - q) % mod;
					}
				}
			}
		}

		void dft_for_complex(std::vector<comp>::iterator f, int n, int b){
			static std::vector<comp> w;
			w.resize(n);
			for(int i = 0; i < n; ++i) if(i < rev[i]) std::swap(f[i], f[rev[i]]);
			for(int i = 2; i <= n; i <<= 1){
				w[0] = comp(1, 0), w[1] = comp(cos(2 * PI / i), b * sin(2 * PI / i));
				for(int j = 2; j < i / 2; ++j) w[j] = w[j - 1] * w[1];
				for(int j = 0; j < n; j += i){
					std::vector<comp>::iterator g = f + j, h = f + j + i / 2;
					for(int k = 0; k < i / 2; ++k){
						comp p = g[k], q = h[k] * w[k];
						g[k] = p + q, h[k] = p - q;
					}
				}
			}
		}
		
		inline int reduct(ll x, ll y, ll z, const int &mod){
			return (x % mod + ((y % mod) << 15) + ((z % mod) << 30)) % mod;
		}
	}
	
	poly poly::prefix(std::size_t len)const{
		std::vector<int> f(len);
		for(int i = std::min(len, size()); i >= 0; --i) f[i] = data[i];
		return f;
	}
	
	m_poly m_poly::prefix(std::size_t len)const{
		std::vector<int> f(len);
		for(int i = std::min(len, size()); i >= 0; --i) f[i] = data[i];
		return m_poly(f, mod);
	}
	
/*
 * Polynomial Convolution
 * Complexity: O(N log N)
 * Implementation: NTT(Number Theoretic Transform)
 * Verification: https://judge.yosupo.jp/problem/convolution_mod
 */
 
	poly operator*(const poly &_f, const poly &_h){
		using _FEISTDLIB_SECURITY_::rev;
		std::vector<int> f(_f.data), h(_h.data);
		
		int N = 1, sz = f.size() + h.size() - 1;
		while(N < sz) N *= 2;
		f.resize(N), h.resize(N), rev.resize(N);
		
		for(int i = 0; i < N; ++i) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? N >> 1 : 0);
		_FEISTDLIB_SECURITY_::dft_for_modulo(f.begin(), N, 1);
		_FEISTDLIB_SECURITY_::dft_for_modulo(h.begin(), N, 1);
		
		for(int i = 0; i < N; ++i) f[i] = (ll)f[i] * h[i] % mod;
		_FEISTDLIB_SECURITY_::dft_for_modulo(f.begin(), N, -1);
		int inv = _FEISTDLIB_SECURITY_::qpow(N, mod - 2);
		f.resize(sz);
		for(int i = 0; i < sz; ++i) f[i] = ((ll)f[i] * inv % mod + mod) % mod;
		
		return f;
	}
	
	poly &operator*=(poly &f, const poly &_h){		
		using _FEISTDLIB_SECURITY_::rev;
		std::vector<int> h(_h.data);
		
		int N = 1, sz = f.size() + h.size() - 1;
		while(N < sz) N *= 2;
		f.resize(N), h.resize(N), rev.resize(N);
		
		for(int i = 0; i < N; ++i) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? N >> 1 : 0);
		_FEISTDLIB_SECURITY_::dft_for_modulo(f.data.begin(), N, 1);
		_FEISTDLIB_SECURITY_::dft_for_modulo(h.begin(), N, 1);
		
		for(int i = 0; i < N; ++i) f[i] = (ll)f[i] * h[i] % mod;
		_FEISTDLIB_SECURITY_::dft_for_modulo(f.data.begin(), N, -1);
		int inv = _FEISTDLIB_SECURITY_::qpow(N, mod - 2);
		f.resize(sz);
		for(int i = 0; i < sz; ++i) f[i] = ((ll)f[i] * inv % mod + mod) % mod;
		
		return f;
	}
	
/*
 * Arbitrary Module Polynomial Convolution
 * Complexity: O(N log N)
 * Implementation: MTT
 * Verification: https://www.luogu.com.cn/problem/P4245
 */ 
 
/*
 * This implementation is much faster than that based on NTT and Chinese Reminder Theorem. 
 * You can refer to it at
 *   https://yutong.site/wp-content/uploads/2018/09/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf .
 * Note that this implementation can perform correctly only when N is around or less than 1e5.
 */
 
	m_poly operator*(const m_poly &_f, const m_poly &_h){
		if(_f.mod != _h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::MODULO_DIF_ERROR);
		const int mod = _f.mod;
		
		using _FEISTDLIB_SECURITY_::rev;
		using _FEISTDLIB_SECURITY_::comp;
		std::vector<comp> f, h;
		
		int N = 1, sz = _f.size() + _h.size() - 1;
		while(N < sz) N *= 2;
		f.resize(N), h.resize(N), rev.resize(N);
		
		for(int i = 0; i < (int)_f.size(); ++i) f[i].x = _f[i] & ((1 << 15) - 1), f[i].y = _f[i] >> 15;
		for(int i = 0; i < (int)_h.size(); ++i) h[i].x = _h[i] & ((1 << 15) - 1), h[i].y = _h[i] >> 15;
				
		for(int i = 0; i < N; ++i) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? N >> 1 : 0);
		_FEISTDLIB_SECURITY_::dft_for_complex(f.begin(), N, 1);
		_FEISTDLIB_SECURITY_::dft_for_complex(h.begin(), N, 1);
		
		std::vector<comp> p(N), q(N);
		for(int i = 0; i < N; ++i){
			p[i] = h[i] * (f[i] + f[(N - i) % N].conj()) * comp(0.50, 0);
			q[i] = h[i] * (f[i] - f[(N - i) % N].conj()) * comp(0, -0.5);
		}
		
		_FEISTDLIB_SECURITY_::dft_for_complex(p.begin(), N, -1);
		_FEISTDLIB_SECURITY_::dft_for_complex(q.begin(), N, -1);
		
		std::vector<int> r(sz);
		for(int i = 0; i < sz; ++i) r[i] = _FEISTDLIB_SECURITY_::reduct(p[i].x / N + 0.5, (p[i].y + q[i].x) / N + 0.5, q[i].y / N + 0.5, mod);
		
		return m_poly(r, mod);
	}
	
	m_poly &operator*=(m_poly &f, const m_poly &h){
		return f = f * h;
	}
	
/*
 * Polynomial Addition
 * Complexity: O(N)
 * Implementation: -
 * Verification: -
 */

	poly operator+(const poly &_f, const poly &_h){
		std::vector<int> f(_f.data);
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] + _h[i]) % mod;
		return f;
	}
	
	poly &operator+=(poly &f, const poly &_h){
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] + _h[i]) % mod;
		return f;
	}

	m_poly operator+(const m_poly &_f, const m_poly &_h){
		if(_f.mod != _h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::MODULO_DIF_ERROR);
		const int mod = _f.mod;
		
		std::vector<int> f(_f.data);
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] + _h[i]) % mod;
		return m_poly(f, mod);
	}
	
	m_poly &operator+=(m_poly &f, const m_poly &_h){
		if(f.mod != _h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::MODULO_DIF_ERROR);
		const int mod = f.mod;
		
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] + _h[i]) % mod;
		return f;
	}

/*
 * Polynomial Subtraction
 * Complexity: O(N)
 * Implementation: -
 * Verification: -
 */

	poly operator-(const poly &_f, const poly &_h){
		std::vector<int> f(_f.data);
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] - _h[i]) % mod;
		return f;
	}
	
	poly &operator-=(poly &f, const poly &_h){
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] - _h[i]) % mod;
		return f;
	}

	m_poly operator-(const m_poly &_f, const m_poly &_h){
		if(_f.mod != _h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::MODULO_DIF_ERROR);
		const int mod = _f.mod;
		
		std::vector<int> f(_f.data);
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] - _h[i]) % mod;
		return m_poly(f, mod);
	}
	
	m_poly &operator-=(m_poly &f, const m_poly &_h){
		if(f.mod != _h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::MODULO_DIF_ERROR);
		const int mod = f.mod;
		
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] - _h[i]) % mod;
		return f;
	}

/*
 * Monomial Calculation
 * Complexity: -
 * Implementation: -
 * Verification: -
 */
		
	poly operator*(const poly &_f, const int &h){
		std::vector<int> f(_f.data);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return f;
	}
		
	poly &operator*=(poly &f, const int &h){
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return f;
	}

	poly operator+(const poly &_f, const int &h){
		std::vector<int> f(_f.data);
		f[0] = (f[0] + h) % mod;
		return f;
	}
		
	poly &operator+=(poly &f, const int &h){
		f[0] = (f[0] + h) % mod;
		return f;
	}

	poly operator-(const poly &_f, const int &h){
		std::vector<int> f(_f.data);
		f[0] = (f[0] - h) % mod;
		return f;
	}
		
	poly &operator-=(poly &f, const int &h){
		f[0] = (f[0] - h) % mod;
		return f;
	}
		
	poly operator*(const int &h, const poly &_f){
		std::vector<int> f(_f.data);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return f;
	}

	poly operator+(const int &h, const poly &_f){
		std::vector<int> f(_f.data);
		f[0] = (f[0] + h) % mod;
		return f;
	}

	poly operator-(const int &h, const poly &_f){
		std::vector<int> f(_f.size());
		f[0] = (h - _f[0]) % mod;
		for(int i = 1; i < (int)f.size(); ++i) f[i] = -_f[i];
		return f;
	}
		
	m_poly operator*(const m_poly &_f, const int &h){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return m_poly(f, mod);
	}
		
	m_poly &operator*=(m_poly &f, const int &h){
		const int mod = f.mod;
	
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return f;
	}

	m_poly operator+(const m_poly &_f, const int &h){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		f[0] = (f[0] + h) % mod;
		return m_poly(f, mod);
	}
		
	m_poly &operator+=(m_poly &f, const int &h){
		const int mod = f.mod;
	
		f[0] = (f[0] + h) % mod;
		return f;
	}

	m_poly operator-(const m_poly &_f, const int &h){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		f[0] = (f[0] - h) % mod;
		return m_poly(f, mod);
	}
		
	m_poly &operator-=(m_poly &f, const int &h){
		const int mod = f.mod;
	
		f[0] = (f[0] - h) % mod;
		return f;
	}
		
	m_poly operator*(const int &h, const m_poly &_f){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return m_poly(f, mod);
	}

	m_poly operator+(const int &h, const m_poly &_f){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		f[0] = (f[0] + h) % mod;
		return m_poly(f, mod);
	}
	
	m_poly operator-(const int &h, const m_poly &_f){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		f[0] = (h - _f[0]) % mod;
		for(int i = 1; i < (int)f.size(); ++i) f[i] = -_f[i];
		return m_poly(f, mod);
	}
	
/*
 * Inverse of Polynomial
 * Complexity: O(N log N)
 * Verification: -
 */
	
	poly poly::inv(void)const{
		if(data[0] == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
		
		using _FEISTDLIB_SECURITY_::rev;
		
		int N = 1, sz = size();
		while(N < sz) N *= 2;
		std::vector<int> f(N << 1), g(N << 1);
		f[0] = _FEISTDLIB_SECURITY_::qpow(data[0], mod - 2);
		
		for(int w = 2; w / 2 < sz; w <<= 1){
			for(int i = size(); i < w; ++i) g[i] = 0;
			for(int i = std::min(w, (int)size()) - 1; i >= 0; --i) g[i] = data[i];
			rev.resize(w * 2);
			for(int i = 0; i < w * 2; ++i) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? w : 0);
			
			_FEISTDLIB_SECURITY_::dft_for_modulo(f.begin(), w << 1, 1);
			_FEISTDLIB_SECURITY_::dft_for_modulo(g.begin(), w << 1, 1);
			
			for(int i = 0; i < w * 2; ++i) f[i] = (ll)f[i] * (2 - (ll)f[i] * g[i] % mod) % mod;
			
			_FEISTDLIB_SECURITY_::dft_for_modulo(f.begin(), w << 1, -1);
			
			int inv = _FEISTDLIB_SECURITY_::qpow(w << 1, mod - 2);
			for(int i = 0; i < w; ++i) f[i] = (ll)f[i] * inv % mod;
			for(int i = w; i < w * 2; ++i) f[i] = 0;
		}
		f.resize(sz);
		
		return f;
	}
	
	poly poly::inv(std::size_t len)const{
		return prefix(len).inv();
	}
	
	m_poly m_poly::inv(void)const{
		if(data[0] == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
			
		m_poly f(1, mod);
		f[0] = _FEISTDLIB_SECURITY_::qpow(this->data[0], mod - 2, mod);
		for(int w = 2; w / 2 < (int)size(); w <<= 1){
			f.resize(w);
			f *= (2 - f * prefix(w));
			f.resize(w);
		}
		f.resize(size());
		return f;
	}
	
	m_poly m_poly::inv(std::size_t len)const{
		return prefix(len).inv();
	}
	
/*
 * Division of Polynomial
 * Complexity: O(N + log P)
 * Verification: - 
 */

	poly operator/(const poly &_f, const int &h){
		if(h == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
		
		std::vector<int> f(_f.data);
		const int inv = _FEISTDLIB_SECURITY_::qpow(h, mod - 2);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * inv % mod;
		return f;
	}
	
	poly &operator/=(poly &f, const int &h){
		if(h == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
			
		const int inv = _FEISTDLIB_SECURITY_::qpow(h, mod - 2);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * inv % mod;
		return f;
	}
	
	m_poly operator/(const m_poly &_f, const int &h){
		if(h == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
		
		std::vector<int> f(_f.data);
		const int inv = _FEISTDLIB_SECURITY_::qpow(h, _f.mod - 2), mod = _f.mod;
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * inv % mod;
		return m_poly(f, mod);
	}
	
	m_poly &operator/=(m_poly &f, const int &h){
		if(h == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
			
		const int inv = _FEISTDLIB_SECURITY_::qpow(h, f.mod - 2), mod = f.mod;
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * inv % mod;
		return f;
	}
	
/*
 * Polynomial Square Root
 * Complexity: O(N log N)
 * Verification: - 
 */

	poly sqrt(const poly &h){
		poly f(1);
		f[0] = _FEISTDLIB_SECURITY_::modulo_sqrt(h.data[0], mod);
		for(int w = 2; w / 2 < (int)h.size(); w <<= 1){
			f.resize(w);
			(f += h.prefix(w) * f.inv()) /= 2;
			f.resize(w);
		}
		f.resize(h.size());
		return f;
	}
	
	m_poly sqrt(const m_poly &h){
		m_poly f(1, h.mod);
		f[0] = _FEISTDLIB_SECURITY_::modulo_sqrt(h.data[0], h.mod);
		for(int w = 2; w / 2 < (int)h.size(); w <<= 1){
			f.resize(w);
			(f += h.prefix(w) * f.inv()) /= 2;
			f.resize(w);
		}
		f.resize(h.size());
		return f;
	}

/*
 * Polynomial Logarithm
 * Complexity: O(N log N)
 * Verification: -
 */
    
	poly log(const poly &h){
		if((h[0] - 1) % mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::OUT_OF_CONVERGENCE_RADIUS);
		
		poly d(h);
		for(int i = 1; i < (int)d.size(); ++i) d[i - 1] = (ll)d[i] * i % mod;
		d.resize(d.size() - 1);
		d *= h.inv();
		d.resize(h.size());
		for(int i = d.size() - 1; i >= 1; --i) d[i] = (ll)d[i - 1] * _FEISTDLIB_SECURITY_::qpow(i, mod - 2) % mod;
		d[0] = 0;
		return d;
	}
    
	m_poly log(const m_poly &h){
		if((h[0] - 1) % h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::OUT_OF_CONVERGENCE_RADIUS);
		const int mod = h.mod;
		
		m_poly d(h);
		for(int i = 1; i < (int)d.size(); ++i) d[i - 1] = (ll)d[i] * i % mod;
		d.resize(d.size() - 1);
		d *= h.inv();
		d.resize(h.size());
		for(int i = d.size() - 1; i >= 1; --i) d[i] = (ll)d[i - 1] * _FEISTDLIB_SECURITY_::qpow(i, mod - 2, mod) % mod;
		d[0] = 0;
		return d;
	}
	
/*
 * Polynomial Exponential
 * Complexity: O(N log N)
 * Verification: -
 */

	poly exp(const poly &h){
		if(h[0] % mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::OUT_OF_CONVERGENCE_RADIUS);
		
		poly f(1);
		f[0] = 1;
		for(int w = 2; w / 2 < (int)h.size(); w <<= 1){
			f.resize(w);
			f *= (1 + h.prefix(w) - log(f));
			f.resize(w);
		}
		f.resize(h.size());
		return f;
	}
	
	m_poly exp(const m_poly &h){
		if(h[0] % h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::OUT_OF_CONVERGENCE_RADIUS);
		const int mod = h.mod;
		
		m_poly f(1, mod);
		f[0] = 1;
		for(int w = 2; w / 2 < (int)h.size(); w <<= 1){
			f.resize(w);
			f *= (1 + h.prefix(w) - log(f));
			f.resize(w);
		}
		f.resize(h.size());
		return f;
	}
}

#endif
