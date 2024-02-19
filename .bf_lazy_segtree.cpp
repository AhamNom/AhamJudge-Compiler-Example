#include <bits/stdc++.h>
#include <ranges>
using namespace std;

constexpr int mod = 998244353;
#include "modint.hpp"

auto main() -> int {
	int n, q; std::cin >> n >> q;
	std::vector a(n, modint(0)), hist_square_sum(n, modint(0));
	while (q--) {
		int t, l, r; cin >> t >> l >> r;
		if (t == 1) {
			modint k; cin >> k;
			for (int i = l; i < r; i++) a[i] += k;
			for (int i = 0; i < n; i++) hist_square_sum[i] += a[i] * a[i];
		} else {
			modint ans1 = 0, ans2 = 0;
			for (int i = l; i < r; i++) cout << a[i] << " "; cout << endl;
			for (int i = l; i < r; i++) ans1 += a[i], ans2 += hist_square_sum[i];
			cout << ans1 << " " << ans2 << endl;
			// cout << reduce(a.begin() + l, a.begin() + r) << " "\
				<< reduce(hist_square_sum.begin() + l, hist_square_sum.begin() + r) << "\n";
		}
	}
}
