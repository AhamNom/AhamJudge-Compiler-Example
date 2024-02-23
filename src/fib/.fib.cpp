#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
#include "../../include/modint.hpp"

auto main() -> int {
	// calc fib in O(logn)
	int n; cin >> n;
	// by matrix multiplication
	using Vec2 = array<modint, 2>;
	using Mat2 = array<Vec2, 2>;
	auto mul = [](const Mat2& a, const Mat2& b) -> Mat2 {
		Mat2 c{};
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		return c;
	};
	auto pow = [&](Mat2 a, int n) -> Mat2 {
		Mat2 res{modint(1), modint(0), modint(0), modint(1)};
		while (n) {
			if (n & 1) res = mul(res, a);
			a = mul(a, a);
			n >>= 1;
		}
		return res;
	};
	Mat2 a{modint(1), modint(1), modint(1), modint(0)};
	Mat2 res = pow(a, n);
	cout << res[0][1] << '\n';
}
