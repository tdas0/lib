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
typedef vector<int> vi;
ll modpow(ll b, ll e ,ll mod) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
ll sj[33];
ll dp[33][33][2];
int vis[33][33][2];
int n = 0;
const ll mod = (ll) 1e9 + 7;
int ct = 0;
ll solve(int x , int y, bool k){
	if(y < 0) return 0 ; 
	if(x == -1){
		if(y == 0) return 1;
		else return 0;
	}
	if(vis[x][y][k] == ct) return dp[x][y][k]%mod;
	vis[x][y][k] = ct;
	if(k){
		return dp[x][y][k] =( solve(x-1 , y - 1, k) + solve(x-1 , y , k))%mod;
	}
	else{
		if(n & (1<<x)){
			return dp[x][y][k] = (solve(x-1, y-1, k) + solve(x-1 ,y , 1))%mod;
		}
		else{
			return dp[x][y][k] = solve(x-1 , y , k)%mod;
		}
	}
}

int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int q;
	cin >> q;
	while(q--){
		int t;
		cin >> t;
		if(t == 0){
			ll l , r, X;
			cin >> l >> r >> X;
			if(r == 0) continue;
			n = r -1 ;
			++ct;
			for(int i = 0 ;i <= 30; i ++){
				sj[i] = ( X * (solve(30, 30 - i , 0)) + sj[i])%mod;
			}
			if(l){
				++ct;
				n = l-1;
				for(int i = 0 ;i <= 30; i ++){
					sj[i] = ((sj[i] -  (X *((ll) solve(30, 30 - i , 0))))%mod + mod )%mod;
				}			
			}
		}
		else{
			ll l , r;
			cin >> l >> r;
			if(r == 0){
				cout << 0 << endl;
				continue;
			}
			r--;
			ll fx = 0;
			for(int i = l ; i <= r; i ++){
				fx = (sj[i]+fx)%mod;
			}
			if(fx <0) fx += mod;
			cout << fx << endl;
		}
	}
}