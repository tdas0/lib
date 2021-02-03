#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<b;i++)
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
using namespace std;
typedef pair<int,int> pii;
#define endl '\n'
typedef long long ll;
typedef vector<int> vi;

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
const ll M = ((ll)1e18) + 31;


ll modLog(ll a, ll b, ll m) {
	assert(__gcd(a, m) == 1);
	ll n = (ll) sqrt(m) + 1, e = 1, x = 1, res = LLONG_MAX;
	unordered_map<ll, ll> f;
	rep(i,0,n) e = modmul(e,a,M);// % m;
	rep(i,0,n) x = modmul(x,e,M), f.emplace(x, i + 1);
	rep(i,0,n) if (f.count(b = modmul(b,a,M)))
		res = min(res, f[b] * n - i - 1);
	return res;
}
bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

ull pollard(ull n) {
	auto f = [n](ull x) { return modmul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 0, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}


ll phi(ll m){
	if(isPrime(m))return m-1;
	if(m == 1)return 1;
	ll res = m;
	for(ll i=2;i*i<=m;i++){
		if(m%i == 0){
			res = (res/i) *(i-1);
			
			while(m%i==0)m/=i;
		}
	}
	if(m > 1)res = (res/m)*(m-1);
	return res;
}
const ll g = 42;
const int N = 1e6 + 100;
ll res[N];
int32_t main(){
	res[1000000] = 300;
	for(int i=1000000-1;i>=0;i--){
		res[i] = modpow(g,res[i+1],M);
	}
	int n;
	cin >> n;
	cout << res[n] << endl;

}
