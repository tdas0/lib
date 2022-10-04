/**
 * Author: tdas
 * Date: ???-??-??
 * License: CC0
 * Source: own work
 * Description: Sum from 0 to n-1 of (floor((A*i + B)/M)) N,M<=1e9 A,B< M , T <= 1e6 (casos de testes)
 * Time: O(\log N)
 * Status: stress-tested
 */


using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;


ll sum_of_floor(ll n, ll m, ll a, ll b) {
    ll ans = 0;
    if (a >= m) {
        ans += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }


    ll y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += (n - (x_max + a - 1) / a) * y_max;
    ans += sum_of_floor(y_max, a, m, (a - x_max % a) % a);
    return ans;
}

int main() {

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        ll n, m, a, b;
        scanf("%lld %lld %lld %lld", &n, &m, &a, &b);
        printf("%lld\n", sum_of_floor(n, m, a, b));
    }
    return 0;
}
