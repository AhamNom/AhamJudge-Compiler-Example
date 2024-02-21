#include <bits/stdc++.h>
using namespace std;

auto main(int argc, char *argv[]) -> int {
    int n = 10, q = 20;
    if (argc >= 2) n = atoi(argv[1]);
    if (argc >= 3) q = atoi(argv[2]);
    cout << n << " " << q << endl;
    // mt19937_64 mt(45218965);
    mt19937_64 mt(114514);
    for (int i = 0; i < q; i++) {
        int t = mt() % 2 + 1;
        if (t == 1) {
            int l = mt() % n;
            int r = mt() % n;
            if (l > r) swap(l, r);
            int k = mt() % 998244353;
            cout << "1 " << l << " " << r + 1 << " " << k << endl;
        } else {
            int l = mt() % n;
            int r = mt() % n;
            if (l > r) swap(l, r);
            cout << "2 " << l << " " << r + 1 << endl;
        }
    }
    puts("");
}
