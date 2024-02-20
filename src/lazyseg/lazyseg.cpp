#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
#include "modint.hpp"

/**
 * @brief Lazy-Segment-Tree(遅延伝搬セグメント木)
 * @docs docs/lazy-segment-tree.md
 */
template< typename T, typename E, typename F, typename G, typename H >
struct LazySegmentTree {
private:
  int n{}, sz{}, height{};
  vector< T > data;
  vector< E > lazy;
  const F f;
  const G g;
  const H h;
  const T ti;
  const E ei;

  inline void update(int k) {
    data[k] = f(data[2 * k + 0], data[2 * k + 1]);
  }

  inline void all_apply(int k, const E &x) {
    data[k] = g(data[k], x);
    if(k < sz) lazy[k] = h(lazy[k], x);
  }

  inline void propagate(int k) {
    if(lazy[k] != ei) {
      all_apply(2 * k + 0, lazy[k]);
      all_apply(2 * k + 1, lazy[k]);
      lazy[k] = ei;
    }
  }

public:
  LazySegmentTree() = default;

  explicit LazySegmentTree(int n, const F f, const G g, const H h,
                           const T &ti, const E &ei)
      : n(n), f(f), g(g), h(h), ti(ti), ei(ei) {
    sz = 1;
    height = 0;
    while(sz < n) sz <<= 1, height++;
    data.assign(2 * sz, ti);
    lazy.assign(2 * sz, ei);
  }

  explicit LazySegmentTree(const vector< T > &v, const F f, const G g, const H h,
                           const T &ti, const E &ei)
      : LazySegmentTree(v.size(), f, g, h, ti, ei) {
    build(v);
  }

  void build(const vector< T > &v) {
    assert(n == (int) v.size());
    for(int k = 0; k < n; k++) data[k + sz] = v[k];
    for(int k = sz - 1; k > 0; k--) update(k);
  }

  void set(int k, const T &x) {
    k += sz;
    for(int i = height; i > 0; i--) propagate(k >> i);
    data[k] = x;
    for(int i = 1; i <= height; i++) update(k >> i);
  }

  T get(int k) {
    k += sz;
    for(int i = height; i > 0; i--) propagate(k >> i);
    return data[k];
  }

  T operator[](int k) {
    return get(k);
  }

  T prod(int l, int r) {
    if(l >= r) return ti;
    l += sz;
    r += sz;
    for(int i = height; i > 0; i--) {
      if(((l >> i) << i) != l) propagate(l >> i);
      if(((r >> i) << i) != r) propagate((r - 1) >> i);
    }
    T L = ti, R = ti;
    for(; l < r; l >>= 1, r >>= 1) {
      if(l & 1) L = f(L, data[l++]);
      if(r & 1) R = f(data[--r], R);
    }
    return f(L, R);
  }

  T all_prod() const {
    return data[1];
  }

  void apply(int k, const E &x) {
    k += sz;
    for(int i = height; i > 0; i--) propagate(k >> i);
    data[k] = g(data[k], x);
    for(int i = 1; i <= height; i++) update(k >> i);
  }

  void apply(int l, int r, const E &x) {
    if(l >= r) return;
    l += sz;
    r += sz;
    for(int i = height; i > 0; i--) {
      if(((l >> i) << i) != l) propagate(l >> i);
      if(((r >> i) << i) != r) propagate((r - 1) >> i);
    }
    {
      int l2 = l, r2 = r;
      for(; l < r; l >>= 1, r >>= 1) {
        if(l & 1) all_apply(l++, x);
        if(r & 1) all_apply(--r, x);
      }
      l = l2, r = r2;
    }
    for(int i = 1; i <= height; i++) {
      if(((l >> i) << i) != l) update(l >> i);
      if(((r >> i) << i) != r) update((r - 1) >> i);
    }
  }

  template< typename C >
  int find_first(int l, const C &check) {
    if(l >= n) return n;
    l += sz;
    for(int i = height; i > 0; i--) propagate(l >> i);
    T sum = ti;
    do {
      while((l & 1) == 0) l >>= 1;
      if(check(f(sum, data[l]))) {
        while(l < sz) {
          propagate(l);
          l <<= 1;
          auto nxt = f(sum, data[l]);
          if(not check(nxt)) {
            sum = nxt;
            l++;
          }
        }
        return l + 1 - sz;
      }
      sum = f(sum, data[l++]);
    } while((l & -l) != l);
    return n;
  }

  template< typename C >
  int find_last(int r, const C &check) {
    if(r <= 0) return -1;
    r += sz;
    for(int i = height; i > 0; i--) propagate((r - 1) >> i);
    T sum = ti;
    do {
      r--;
      while(r > 1 and (r & 1)) r >>= 1;
      if(check(f(data[r], sum))) {
        while(r < sz) {
          propagate(r);
          r = (r << 1) + 1;
          auto nxt = f(data[r], sum);
          if(not check(nxt)) {
            sum = nxt;
            r--;
          }
        }
        return r - sz;
      }
      sum = f(data[r], sum);
    } while((r & -r) != r);
    return -1;
  }
};

template< typename T, typename E, typename F, typename G, typename H >
LazySegmentTree< T, E, F, G, H > get_lazy_segment_tree
    (int N, const F &f, const G &g, const H &h, const T &ti, const E &ei) {
  return LazySegmentTree{N, f, g, h, ti, ei};
}

template< typename T, typename E, typename F, typename G, typename H >
LazySegmentTree< T, E, F, G, H > get_lazy_segment_tree
    (const vector< T > &v, const F &f, const G &g, const H &h, const T &ti, const E &ei) {
  return LazySegmentTree{v, f, g, h, ti, ei};
}

auto main() -> int {
	using Vec4 = array<modint, 4>; // (val, val^2, sum_in_history(val^2), 1)
	using Mat4 = array<Vec4, 4>;
	auto f = [](Vec4 a, Vec4 b) -> Vec4 {
		Vec4 res;
		res[0] = a[0] + b[0];
		res[1] = a[1] + b[1];
		res[2] = a[2] + b[2];
		res[3] = a[3] + b[3];
		return res;
	};
	auto g = [](Vec4 a, Mat4 b) -> Vec4 {
		Vec4 res;
		res[0] = b[0][0] * a[0] + b[0][1] * a[1] + b[0][2] * a[2] + b[0][3] * a[3];
		res[1] = b[1][0] * a[0] + b[1][1] * a[1] + b[1][2] * a[2] + b[1][3] * a[3];
		res[2] = b[2][0] * a[0] + b[2][1] * a[1] + b[2][2] * a[2] + b[2][3] * a[3];
		res[3] = b[3][0] * a[0] + b[3][1] * a[1] + b[3][2] * a[2] + b[3][3] * a[3];
		return res;
	};
	auto h = [](Mat4 a, Mat4 b) -> Mat4 {
		Mat4 res;
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				res[i][j] = 0;
				for(int k = 0; k < 4; k++) {
					res[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		return res;
	};
	auto ti = Vec4{0, 0, 0, 0};
	auto ei = Mat4{Vec4{1, 0, 0, 0}, Vec4{0, 1, 0, 0}, Vec4{0, 0, 1, 0}, Vec4{0, 0, 0, 1}};

	int N, Q; cin >> N >> Q;
	auto seg = get_lazy_segment_tree(N, f, g, h, ti, ei);
	/*
	for (int i = 0; i < N; i++) {
		modint ai; cin >> ai;
		seg.set(i, {ai, 0, 0, 0});
	}
	 */
	while (Q--) {
		int t, l, r; cin >> t >> l >> r;
		if (t == 1) {
			modint k; cin >> k;
			seg.apply(l, r, Mat4{
				Vec4{1, modint(2) * k, 0, 0},
				Vec4{0, 1, 0, 0},
				Vec4{0, 0, 1, 0}, 
				Vec4{k * k, k, 0, 1}
			});
			seg.apply(0, N, Mat4{
				Vec4{1, 0, 0, 0},
				Vec4{0, 1, 1, 0},
				Vec4{0, 0, 1, 0},
				Vec4{0, 0, 0, 1}
			});
		} else {
			auto res = seg.prod(l, r);
			cout << res[0] << " " << res[2] << endl;
		}
	}
}
