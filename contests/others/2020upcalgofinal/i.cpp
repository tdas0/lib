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
const int N = 10002;
vi g[N];
int n , dp[N][N][2] , q , c[N] , sz[N] , tmp[N][2];
string s;

void make(int x , int y = -1){
	if(c[x]){ // sou comunista
		dp[x][1][0] = 0;
		dp[x][1][1] = 0;
	}
	else{
		dp[x][0][0] = 1;
		dp[x][0][1] = 1;
	}
	sz[x] = c[x];
	for(auto w : g[x]){
		if(w == y) continue;
		make(w , x);
		for(int j = 0 ; j <= sz[w] ; j++){
			for(int k = 0 ; k <= sz[x] ; k ++){
				tmp[j+k][0] = INT_MAX/3;
				tmp[j+k][1] = -(INT_MAX/3);
			}
		}
		for(int j = 0 ; j <= sz[w] ; j++){
			for(int k = 0 ; k <= sz[x] ; k ++){
				tmp[j+k][0] = min(tmp[j+k][0] , dp[w][j][0] + dp[x][k][0]);
				tmp[j+k][1] = max(tmp[j+k][1] , dp[w][j][1] + dp[x][k][1]);
			}
		}		
		for(int j = 0 ; j <= sz[w] ; j++){
			for(int k = 0 ; k <= sz[x] ; k ++){
				dp[x][j+k][0] = min(dp[x][j+k][0] , tmp[j+k][0]);
				dp[x][j+k][1] = max(dp[x][j+k][1] , tmp[j+k][1]);
			}
		}
		sz[x] += sz[w];
	}
}

int32_t main(){
	ios::sync_with_stdio(!cin.tie(0));
	cin >> n>>q;
	for(int x = 0 ; x < N ; x ++){
		for(int y = 0 ; y < N ;y ++){
			dp[x][y][0] = INT_MAX / 3;
			dp[x][y][1] = - (INT_MAX / 3);
			tmp[y][0] = INT_MAX/3;
			tmp[y][1] = - (INT_MAX/3);
		}
	}
	for(int i = 1 ; i <= n; i ++){
		int p; cin >> p;
		if(i == 1) continue;
		g[p].push_back(i);
		g[i].push_back(p);
	}
	cin >> s;
	for(int i = 1; i <= n ; i++){
		if(s[i-1] == 'S') c[i] = 1;
	}
	make(1);
	while(q--){
		int root , C, S;
		cin >> root >> C >> S;
		int L = dp[root][S][0] , R = dp[root][S][1];
		if(L <= C && C <= R) cout <<"COMPROMISED" << endl;
		else cout << "NOT COMPROMISED" << endl;
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
 