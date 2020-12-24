/*
Lowlink dfs
G[i][j] guarda o j-ésimo adjacente ao cara i no first, e o o id da aresta no second
bridges[i] diz se a i-ésima aresta é uma bridge (ordem do input)
art[i] diz se o i-ésimo nó é um cut-vertex
limpar as merdas se tiver multiplos casos
*/


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
vpi g[N]; // (adjacente, id da aresta)
int tin = 0 , low[N] , in[N];
// lowlink dfs
bool bridges[N], art[N];
void dfs(int x , int p = -1){
	in[x] = ++tin , low[x] = in[x];
	int filhos = 0;
	for(auto w : g[x]){
		int v = w.F;
		if(in[v] == 0){
			dfs(v , x);
			filhos++;
			low[x] = min(low[x] , low[v]);
			if(low[v] > in[x]){
				bridges[w.S] = true;
			}
			if(low[v] >= in[x] && p != -1){
				art[x] = true;
			}
		}
		else if(v != p){
			low[x] = min(low[x] , in[v]);
		}
	}
	if(p == -1 && filhos >= 2) art[x] = true;
}
// end of lowlink dfs



int32_t main(){
	int n , m;
	int t;
	cin >> t;
	int fa = 0;
	while(t--){
		cin >> n >> m;
		rep(i,1,n+1) in[i] = 0 , g[i].clear() , art[i] = false;
		rep(i,0,m)
		bridges[i] = 0;
		tin = 0 ;
		vpi ee , e;
		rep(i,0,m){
			int u , v;
			cin >> u >> v;
			g[u].push_back({v,i});
			g[v].push_back({u,i});
			ee.push_back({min(u,v),max(v,u)});
		}
		dfs(1);
		int cnt = 0 ;
		rep(i,0,m){
			cnt = (cnt + (bridges[i] ? 1 : 0));
			if(bridges[i])
			e.push_back({min(ee[i].F,ee[i].S),max(ee[i].F,ee[i].S)});
		}
		cout <<"Caso #"<<++fa << endl;
		if(cnt){
			cout << cnt << endl;
			sort(all(e));
			for(auto w : e)
				cout << w.F <<" " << w.S << endl;
		}
		else{
			cout <<"Sin bloqueos" << endl;
		}
	}	
}
