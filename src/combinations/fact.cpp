#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
#include "../../include/modint.hpp"

auto main() -> int {
	int n; cin >> n;
	cout << fact[n] << endl;
	cout << modint(1) / fact[n] << endl;
}
