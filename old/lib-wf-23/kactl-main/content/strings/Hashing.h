/**
 * Author: Arthurpd
 * License: CC0
 * Description: Self-explanatory methods for string hashing.
 * Useful primes: 1e9 + 7,1e9 + 9, 998244353, 139, 137, 1e18 + 9
 * Status: stress-tested
 */
struct hash_interval{
	ll c, mod;
	vector<ll> h, p;
	hash_interval(const string &s, ll c, ll mod) 
	: c(c), mod(mod), h(sz(s) + 1), p(sz(s) + 1)
	{
		p[0] = 1;
		h[0] = 0;
		for (int i = 0; i < sz(s); i++)
		{
			h[i + 1] = (c * h[i] + s[i]) % mod;
			p[i + 1] = (c * p[i]) % mod;
		}
	}
	// Returns hash of interval s[a...b] (where 0 <= a <= b < sz(s))
	ll get(int a, int b)
	{
		return (h[b + 1] - ((h[a] * p[b - a + 1]) % mod) + mod) % mod;
	}
};