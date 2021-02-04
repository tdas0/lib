#include <bits/stdc++.h>
using namespace std;
const int N = 500005;
const long long mod = 998244353;
typedef long long ll;
ll modpow(ll b, ll e ,ll mod) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

int n;
long long a[N];

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
};
typedef Point<__int128> P;
P h[N];
bool ok[N];
int32_t main(){
	scanf("%d" , &n);
	for(int i = 1; i <= n; i ++){
		scanf("%lld" , &a[i]);
	}
	int k = 0;
	for(int i = n  ; i >= 1 ; i --){
		while(k >= 2 && h[k-2].cross(h[k-1],P(i,a[i])) <= 0)
			k--;
		h[k++] = P(i,a[i]);
	}
	set<int> inhull;
	for(int i = 0 ; i < k; i ++){
		inhull.insert((int)(h[i].x));
	}
	ll ans = 0;
	ll inv = modpow(n , mod-2,mod);
	for(int i = 1; i <= n; i ++){
		if(inhull.count(i)){
			ans = (ans + (a[i]%mod)) % mod;
		}
		else{
			auto left = *prev(inhull.lower_bound(i));
			auto right = *inhull.lower_bound(i);
			ll inv2 = modpow(right - left , mod -2 , mod);
			ll cur = inv2 * (((a[left]%mod) * ((ll) i - left) + (a[right]%mod) * ((ll) right - i))%mod)%mod;
			ans = (ans + cur) % mod;
		}
	}
	printf("%lld\n" , (ans * inv)%mod);
}
