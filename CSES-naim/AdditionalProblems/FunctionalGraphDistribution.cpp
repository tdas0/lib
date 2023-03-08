// Para todo k achar #grafos funcionais com K componentes e N vert
// berarchegas

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
const int MOD = 1e9 + 7;
const int MAXN = 5e3 + 5;
const ll INF = 2e18;
 
int fat[MAXN], inv[MAXN], pwr[MAXN], stirling[MAXN][MAXN];
 
ll fexp(ll b, ll e) {
    ll ans = 1;
    while (e) {
        if (e&1) ans = (ans * b) % MOD;
        b = (b * b) % MOD;
        e >>= 1;
    }
    return ans;
}
 
ll nck(int n, int k) {
    if (k > n || k < 0 || n < 0) return 0;
    return (((1ll * fat[n] * inv[k]) % MOD) * 1ll * inv[n - k]) % MOD; 
}
 
void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}
 
int mul(ll a, ll b) {
    return (a * b) % MOD;
}
 
void precalc(ll n) {
    fat[0] = 1;
    for (ll i = 1; i < MAXN; i++) fat[i] = (i * fat[i - 1]) % MOD;
    inv[MAXN - 1] = fexp(fat[MAXN - 1], MOD - 2);
    for (ll i = MAXN - 2; i >= 0; i--) inv[i] = ((i + 1ll) * inv[i + 1]) % MOD;
    pwr[0] = 1;
    for (int i = 1; i < MAXN; i++) pwr[i] = (n * pwr[i - 1]) % MOD;
    stirling[0][0] = 1;
    for (int i = 1; i < MAXN; i++) {
        for (int j = 1; j < MAXN; j++) {
            stirling[i][j] = mul(i - 1, stirling[i - 1][j]);
            add(stirling[i][j], stirling[i - 1][j - 1]);
        }
    }
}
 
int ans[MAXN];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    precalc(n);
    for (int k = 1; k <= n; k++) {
        for (int x = k; x <= n; x++) {
            if (x < n)
                add(ans[k], mul(mul(nck(n, x), stirling[x][k]), mul(x, pwr[n - x - 1])));
            else 
                add(ans[k], mul(nck(n, x), stirling[x][k]));
        }
        cout << ans[k] << '\n';
    }
    return 0;
}