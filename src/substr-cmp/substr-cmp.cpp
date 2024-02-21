#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
#include "../../include/modint.hpp"

auto main() -> int {
	string s; int q; cin >> s >> q;
	while (q--) {
		int l0, r0, l1, r1; cin >> l0 >> r0 >> l1 >> r1;
		cout << (s.substr(l0, r0-l0+1) < s.substr(l1, r1-l1+1) ? "<" : ">=") << '\n';
	}
}
