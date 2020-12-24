#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
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
// graph class
struct edge{
	int x ,id; 
};
const int SZ = 1000005;
	vector<edge> g[SZ+1];
	int low[SZ+1], in[SZ+1] ; 
	void add_edge(int x , int y , int id){
		g[x].push_back({y,id});
	}
	void clear(int i){
		g[i].clear();
	}
// end
// begin of SCC
const int N = 1000005;
graph<N> g , rg;
int tin = 0 , instack[N] , inscc[N];
vector< vi > sccs;
vi path; 
void dfs(int x , int p = -1){
	g.in[x] = g.low[x] = ++tin;
	path.push_back(x);
	instack[x] = true;
	allin(w , g.g[x]){
		int v = w.x;
		if(g.in[v] == 0){
			dfs(v, x);
			g.low[x] = min(g.low[x] , g.low[v]);
		}
		else if(instack[v]){
			g.low[x] = min(g.low[x] , g.in[v]);
		}
	}
	if(g.low[x] == g.in[x]){
		vi scc;
		do{
			int u = path.back();
			inscc[u] = sz(sccs);
			path.pop_back();
			instack[u] = false;
			scc.push_back(u);
			if(u == x) break ; 
		} while(1);
		sccs.push_back(scc);
	}
}
// end
ll f[N];
ll fs[N];
ll dp[N];
int32_t main(){
	int n , m , s, e;
	cin >> n >> m >> s >> e;
	dp[0] = - (ll) 1e16;
	rep(i,1,n+1) cin >> f[i], dp[i] = -(ll) 1e16;
	rep(i,0,m){
		int x , y;
		cin >> x >> y;
		g.add_edge(x,y,i);
		rg.add_edge(y,x,i);
	}
	rep(i,1,n+1){
		if(g.in[i] == 0) dfs(i);
	}
	rep(i,1,n+1){
		fs[inscc[i]] += f[i];
	}
	dp[inscc[e]] = fs[inscc[e]]; 
	rep(scc, 0, sz(sccs)){
		allin(w, sccs[scc]){
			allin(uv , (rg.g[w])){
				int v = uv.x;
				if(inscc[v] != inscc[w]){
					dp[inscc[v]] = max(dp[inscc[v]] , dp[inscc[w]] + fs[inscc[v]]);
				}
			}
		}
	}
	cout << dp[inscc[s]] << endl;
}	