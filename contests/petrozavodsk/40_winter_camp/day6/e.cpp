#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<ll> vi;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
int n;

void FST(vi& a, bool inv) {
	for (int n = (int) a.size(), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) for(int j =i ; j < i+step; j ++) {
			ll &u = a[j], &v = a[j + step]; tie(u, v) =
			pair<ll,ll>(u + v, u - v);              
		}
	}
	if (inv) for(auto &x :  a) x /= (ll) (a).size(); 
}
vi conv(vi a, vi b) {
	FST(a, 0); FST(b, 0);
	for(int i = 0 ; i < (int)a.size() ; i ++) a[i] *= b[i];
	FST(a, 1); return a;
}

int32_t main(){
	scanf("%d" , &n);
	vector<ll> a(1<<17 , 0);
	for(int i = 1 ; i<= n; i ++){
		ll x;
		scanf("%lld" , &x);
		a[x]++;
	}
	a = conv(a,a);
	for(int i = 1; i < (int) a.size() ; i ++){
		if((a[i]) > 2){
			puts("Yes");
			return 0;
		}
	}
	puts("No");
}
