#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
#include "../../include/modint.hpp"

auto main() -> int {
	int n; cin >> n;

	vector<modint> fact(n + 1); fact[0] = 1;
	for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;

	cout << fact[n] << endl;
	cout << modint(1) / fact[n] << endl;
}
