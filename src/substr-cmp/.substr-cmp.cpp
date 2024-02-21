#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
#include "../../include/modint.hpp"

auto main() -> int {
	// string s; int q; cin >> s >> q;
	vector<uint8_t> s(1e5);

	int i = 0;
	while (true) {
		char c; scanf("%c", &c);
		if (c == ' ') break;
		s[i] |= (c - '0') << 4;

		scanf("%c", &c);
		if (c == ' ') break;
		s[i] |= (c - '0');

		i++;
	}
	// for (int i = 0; s[i] != 0x00; i++) printf("%02x ", s[i]); cout << endl;

	int q; cin >> q;
	while (q--) {
		int l0, r0, l1, r1; cin >> l0 >> r0 >> l1 >> r1;

		for (int i = l0 / 2; i < r0 / 2; i++) {
			if (s[i] != s[i - l0 / 2 + l1 / 2]) {
				cout << (s[i] < s[i - l0 / 2 + l1 / 2] ? "<" : ">=") << endl;
				break;
			}
		}
	}
}
