// em uma operacao subtraio numero por algum de seus digitos
// monogon

#include <bits/stdc++.h>
 
#define ll long long
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
 
map<pair<int, ll>, pair<ll, int>> dp;
 
pair<ll, int> solve(int d, ll x) {
    if(x < 10) {
        if(d > x) return {0, x};
        else return {1, 0};
    }
    if(dp.count({d, x})) return dp[{d, x}];
    ll p10 = 1;
    int one = 0;
    ll y = x;
    while(y > 0) {
        one = y % 10;
        y /= 10;
        if(y > 0) p10 *= 10;
    }
    ll ans = 0;
    int d2 = 0;
    tie(ans, d2) = solve(max(d, one), x - p10 * one);
    for(int i = one - 1; i >= 0; i--) {
        pair<ll, int> p = solve(max(d, i), p10 + d2 - max({d, d2, i + 1}));
        ans += 1 + p.first;
        d2 = p.second;
    }
    return dp[{d, x}] = {ans, d2};
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    pair<ll, int> p = solve(0, n);
    ll ans = p.first + (p.second > 0);
    cout << ans << '\n';
}