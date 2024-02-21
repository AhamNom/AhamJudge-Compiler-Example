#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
#include "../../include/modint.hpp"

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

	auto comb = [&](int a, int b) {
		if (a < b) return modint(0);
		if (a < 0 || b < 0) return modint(0);
		return fact[a] * inv_fact[b] * inv_fact[a - b];
	};

	cout << comb(n, k) << endl;
}
