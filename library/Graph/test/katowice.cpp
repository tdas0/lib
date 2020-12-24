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

struct SCC{
	vector< vi> g , comps;
	vi val, z, cont, comp;
	int Time =0, ncomps= 0 , n; 
	SCC(vector<vi> g, int n ):n(n) , g(g) , val(n+1,0), comp(n+1, -1) {}
	int dfs(int j){
		int low = val[j] = ++Time , x ; z.push_back(j);
		trav(e, g[j]) if(comp[e] < 0)
			low = min(low , val[e] ?: dfs(e));
		if(low == val[j]){
			do{
				x = z.back() ; z.pop_back();
				comp[x] = ncomps;
				cont.push_back(x);
			} while(x != j);
			comps.push_back(cont) , cont.clear();
			ncomps++;
		}
		return val[j] = low;
	}
	void scc(){
		val.assign(n+1,0); comp.assign(n+1,-1);
		Time = ncomps = 0 ;
		rep(i,1,n+1) if(comp[i] < 0 ) dfs(i);
	}
};
vector< vi > g;
int n , m;
ll dp[100005][7];
set<int> to[100005];
map<int,int> ord;
int32_t main(){
	cin >> n >> m ;
	g = vector<vi> (n+1);
	rep(i,0,m){
		int x , y;
		cin >> x>> y;
		g[x].push_back(y);
		to[x].insert(y);
	}
	SCC scc(g , n);
	scc.scc();
	vector<vi> comps = scc.comps;
	vi comp = scc.comp;
	rep(i,0,sz(comps)){
		int j = 0;
		allin(w,comps[i]){
			ord[w] = j++;
		}
	}
	rep(i,0,sz(comps)){
		vector<int> perm(sz(comps[i]));
		rep(j,0,sz(comps[i])) perm[j] = j;
		do{	
			vi p = comps[i];
			rep(j,0,sz(p)){
				p[j] = comps[i][perm[j]];
			}
			int curr = 0;
			dp[i][perm[0]] = max(dp[i][perm[0]] , (ll)curr + 1);
			for(auto w : g[p[0]]){
				if(comp[w] != comp[p[0]]){
					dp[i][perm[0]] = max(dp[i][perm[0]] , 1 + dp[comp[w]][ord[w]]);
				}
			}
			while(curr != sz(p) - 1){
				if(to[p[curr]].count(p[curr+1])){
					curr ++ ;
					dp[i][perm[0]] = max(dp[i][perm[0]] , (ll)curr+1);
					for(auto w : g[p[curr]]){
						if(comp[w] != comp[p[curr]]){
							dp[i][perm[0]] = max(dp[i][perm[0]] , 1 + curr + dp[comp[w]][ord[w]]);
						}
					}
				}
				else break;
			}
		} while(next_permutation(all(perm))) ;
		// cout << i << " " << dp[i] << endl; 
 	}
 	ll ans = 0 ;
 	rep(i,0,sz(comps)){
 		rep(j,0,7) ans = max(ans , dp[i][j]);
 	}
 	cout << ans << endl;	 
}