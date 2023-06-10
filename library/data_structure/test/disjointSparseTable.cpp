// Source: https://judge.yosupo.jp/submission/89701

#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)(x).size()

template <class T, class Op>
struct RQ {
    vector<vector<T>> s;
    Op op;
    RQ(const vector<T>& a, Op op_) : s{{a}}, op{op_} {
        for (int j = 2; j < sz(a); j *= 2)
            for (int k = (s.push_back(a), j); k < sz(a); k += 2 * j) {
                auto& x = s.back();
                for (int i = k + 1; i < min(j + k, sz(a)); ++i)
                    x[i] = op(x[i - 1], x[i]);
                for (int i = k - 2; i >= k - j; --i) x[i] = op(x[i], x[i + 1]);
            }
    }
    T query(int l, int r) {
        if (l == --r) return s[0][l];
        int b = __lg(l ^ r);
        return op(s[b][l], s[b][r]);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    const auto cmp = [](int x, int y) {
        return min(x, y);
    };
    RQ<int, decltype(cmp)> st(a, cmp);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r) << '\n';
    }
}
