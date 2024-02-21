#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
#include "../../include/modint.hpp"

    // 特殊な剰余と原始根
    // (924844033, 5)
    // (998244353, 3)
    // (1012924417, 5)
    // (167772161, 3)
    // (469762049, 3)
    // (1224736769, 3)
     
    #define MOD 998244353
    #define root 3
     
    unsigned int add(const unsigned int x, const unsigned int y)
    {
        return (x + y < MOD) ? x + y : x + y - MOD;
    }
     
    unsigned int sub(const unsigned int x, const unsigned int y)
    {
        return (x >= y) ? (x - y) : (MOD - y + x);
    }
     
    unsigned int mul(const unsigned int x, const unsigned int y)
    {
        return (unsigned long long)x * y % MOD;
    }
     
    unsigned int mod_pow(unsigned int x, unsigned int n)
    {
        unsigned int res = 1;
        while(n > 0){
            if(n & 1){ res = mul(res, x); }
            x = mul(x, x);
            n >>= 1;
        }
        return res;
    }
     
    unsigned int inverse(const unsigned int x)
    {
        return mod_pow(x, MOD - 2);
    }
     
    void ntt(vector<int>& a, const bool rev = false)
    {
        unsigned int i, j, k, l, p, q, r, s;
        const unsigned int size = a.size();
        if(size == 1) return;
        vector<int> b(size);
        r = rev ? (MOD - 1 - (MOD - 1) / size) : (MOD - 1) / size;
        s = mod_pow(root, r);
        vector<unsigned int> kp(size / 2 + 1, 1);
        for(i = 0; i < size / 2; ++i) kp[i + 1] = mul(kp[i], s);
        for(i = 1, l = size / 2; i < size; i <<= 1, l >>= 1){
            for(j = 0, r = 0; j < l; ++j, r += i){
                for(k = 0, s = kp[i * j]; k < i; ++k){
                    p = a[k + r], q = a[k + r + size / 2];
                    b[k + 2 * r] = add(p, q);
                    b[k + 2 * r + i] = mul(sub(p, q), s);
                }
            }
            swap(a, b);
        }
        if(rev){
            s = inverse(size);
            for(i = 0; i < size; i++){ a[i] = mul(a[i], s); }
        }
    }
     
    vector<int> convolute(const vector<int>& a, const vector<int>& b)
    {
        const int size = (int)a.size() + (int)b.size() - 1;
        int t = 1;
        while(t < size){ t <<= 1; }
        vector<int> A(t, 0), B(t, 0);
        for(int i = 0; i < (int)a.size(); i++){ A[i] = a[i]; }
        for(int i = 0; i < (int)b.size(); i++){ B[i] = b[i]; }
        ntt(A), ntt(B);
        for (int i = 0; i < t; i++){ A[i] = mul(A[i], B[i]); }
        ntt(A, true);
        A.resize(size);
        return A;
    }

auto main() -> int {
	int n, k; cin >> n >> k;

	vector<modint> fact(n + 1); fact[0] = 1;
	for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;

	auto power = [](modint a, int b) {
		if (a == -1) return modint(b % 2 == 0 ? 1 : -1);
		modint res = 1;
		while (b) {
			if (b & 1) res *= a;
			a *= a;
			b /= 2;
		}
		return res;
	};

	vector<modint> inv_fact(n + 1); inv_fact[n] = power(fact[n], mod - 2);
	for (int i = n - 1; i >= 0; i--) inv_fact[i] = inv_fact[i + 1] * (i + 1);

	vector<modint> lhs(n + 1), rhs(n + 1);
	for (int i = 0; i <= n; i++) {
		lhs[i] = power(-1, i) * inv_fact[i];
		rhs[i] = power(i, n) * inv_fact[i];
	}

	auto &&_conv = convolute(
		*reinterpret_cast<vector<int>*>(&lhs),
		*reinterpret_cast<vector<int>*>(&rhs)
	);
	auto conv = *reinterpret_cast<vector<modint>*>(&_conv);

	auto stirling = [&](int n, int k) {
		if (n < k) return modint(0);
		return conv[k];
	};

	cout << stirling(n, k) << endl;
}
