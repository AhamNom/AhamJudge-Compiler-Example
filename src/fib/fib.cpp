#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
#include "modint.hpp"

auto main() -> int {
	// calc fib in O(n)
	int n; cin >> n;
	vector<modint> fib(n + 1);
	fib[0] = 0; fib[1] = 1;
	for (int i = 2; i <= n; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	cout << fib[n] << '\n';
}
