#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x) , end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
ll modpow(ll b, ll e ,ll mod) { ll ans = 1;for (; e; b = b * b % mod, e /= 2){if (e & 1) ans = ans * b % mod;}return ans;}
int t, n , k , l;
const ll mod = 999983;
vi mult(vi x , int K){ // y é um monomio
	vi p(sz(x) + 1);
	for(int i = 0 ; i < sz(x) ; i ++){
		p[i+1] = (x[i] + p[i+1])%mod;
		ll f = x[i];
		f = f * (K*1ll) % mod;
		p[i] = (p[i] + f) %mod ;
	}
	for(auto &w : p){
		if(w < 0) w += mod;
	}
	return p;
}
int32_t main(){
	scanf("%d" ,&t);
	while(t--){
		scanf("%d%d%d" , &n, &k ,&l);
		set<int> s;
		for(int i = 0 ; i < l; i ++){
			int x;
			scanf("%d" , &x);
			s.insert(x%mod);
		}	
		vi p;
		p.push_back(1);
		for(auto w : s){
			p = mult(p , -w);
		}
		if((sz(p)-1) > k){
			printf("0\n");
			continue;
		}
		set<vi> f;
		f.insert(p);
		int j = 1;
		while(sz(f) < n){
			vi u = p;
			for(auto & w : u) w = (w * j)%mod;
			j ++ ;
			f.insert(u);			
		}
		printf("%d\n" , n);
		for(auto w: f){
			reverse(all(w));
			printf("%d " , sz(w) - 1);
			for(auto r : w){
				printf("%d " , r);
			}
			printf("\n");
		}
		continue;
	}
}
/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/
 