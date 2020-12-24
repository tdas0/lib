/* Source: Aeren's library
 * Chinese Remainder Theorem (Return a number x which satisfies x = a mod m & x = b mod n)
 * All the values has to be less than 2^30
 * O(log(N + M)
 * the resulting modulo is LCM(n,m)
 * Status: tested on kattis
 */
typedef long long ll;
ll euclid(ll x, ll y, ll &a, ll &b){
	if(y){
		ll d = euclid(y, x % y, b, a);
		return b -= x / y * a, d;
	}
	return a = 1, b = 0, x;
}
ll crt_coprime(ll a, ll m, ll b, ll n){
	ll x, y; euclid(m, n, x, y);
	ll res = a * (y + m) % m * n + b * (x + n) % n * m;
	if(res >= m * n) res -= m * n;
	return res;
}
ll crt(ll a, ll m, ll b, ll n){
	ll d = gcd(m, n);
	if(((b -= a) %= n) < 0) b += n;
	if(b % d) return -1; // No solution
	return d * crt_coprime(0LL, m/d, b/d, n/d) + a;
}
