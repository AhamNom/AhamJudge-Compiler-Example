#include <bits/stdc++.h>

void solorejudger();

#define int long long

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    while(T--) {
        solorejudger();
    }
    return 0;
}

void solorejudger() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> u(m), v(m), w(m);
    for(int i = 0; i < m; ++i) {
        std::cin >> u[i] >> v[i] >> w[i];
        u[i]--, v[i]--;
    }
    
    std::vector<std::vector<std::pair<int, int>>> edge(n);
    for(int i = 0; i < m; ++i) {
        edge[u[i]].emplace_back(v[i], w[i]);
        edge[v[i]].emplace_back(u[i], w[i]);
    }
    long long ans = 0;
    for(int k = 0; k < 30; ++k) {
        std::vector<int> col(n, -1);
        for(int i = 0; i < n; ++i) if(col[i] == -1) {
            std::vector<int> cnt(2);
            std::fill(cnt.begin(), cnt.end(), 0);
            bool gameover = false;
            std::function<void(int, int)> dfs = [&] (int u, int c) {
                if(col[u] != -1) {
                    if(col[u] != c) gameover = true;
                    return;
                }
                ++cnt[col[u] = c];
                for(auto [v, w]: edge[u]) dfs(v, c ^ (w >> k & 1));
            };

            dfs(i, 0);
            if(gameover) {
                std::cout << -1 << std::endl;
                return;
            }
            ans += std::min(cnt[0], cnt[1]) * (1ll << k);
        }
    }
    std::cout << ans << std::endl;
}

