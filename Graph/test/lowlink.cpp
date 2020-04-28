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
// end
const int N = 100005;
graph<N> g;
int tin = 0;
// lowlink dfs
bool bridges[N], art[N];
void dfs(int x , int p = -1){
	g.in[x] = ++tin , g.low[x] = g.in[x];
	int filhos = 0;
	allin(w, *g[x]){
		int v = w.x;
		if(g.in[v] == 0){
			dfs(v , x);
			filhos++;
			g.low[x] = min(g.low[x] , g.low[v]);
			if(g.low[v] > g.in[x]){
				bridges[w.id] = true;
			}
			if(g.low[v] >= g.in[x] && p != -1){
				art[x] = true;
			}
		}
		else if(v != p){
			g.low[x] = min(g.low[x] , g.in[v]);
		}
	}
	if(p == -1 && filhos >= 2) art[x] = true;
}
// end of lowlink dfs



int32_t main(){
	int n , m;
	while(cin >> n >> m , n + m){
		rep(i,1,n+1) g.in[i] = 0 , g.clear(i) , art[i] = false;
		tin = 0 ;
		rep(i,0,m){
			int u , v;
			cin >> u >> v;
			g.add_edge(u,v,i);
			g.add_edge(v,u,i);
		}
		dfs(1);
		int cnt = 0 ;
		rep(i,1,n+1){
			cnt = (cnt + (art[i] ? 1 : 0));
		}
		cout << cnt << endl;
	}	
}