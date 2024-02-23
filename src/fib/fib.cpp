#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
#include "../../include/modint.hpp"

auto main() -> int {
	// calc fib in O(n)
	long long n; cin >> n;
	modint fib_i_1 = 0, fib_i_2 = 1;
	for (long long i = 2; i <= n; i++) {
		fib_i_2 = fib_i_1 + fib_i_2;
		auto x = (int *) &fib_i_1, y = (int *) &fib_i_2;
		*x ^= *y ^= *x ^= *y;
	}
	cout << fib_i_1 + fib_i_2 << endl;
}
