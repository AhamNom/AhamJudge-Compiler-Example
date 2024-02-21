#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
#include "../../include/modint.hpp"

auto main() -> int {
  vector<vector<modint>> S(n + 1, vector<modint>(k + 1, 0)); S[0][0] = 1;

  for (int i = 1; i <= n; ++i) for (int j = 1; j <= min(i, k); ++j)
  if (j == 1 || i == j) S[i][j] = 1;
  else S[i][j] = modint(j) * S[i - 1][j] + S[i - 1][j - 1];

  cout << S[n][k] << endl;
}
