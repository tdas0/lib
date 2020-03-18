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
template <int SZ> class graph{
public:
	vector<edge> g[SZ+1];
	int low[SZ+1], in[SZ+1] ; 
	void add_edge(int x , int y , int id){
		g[x].push_back({y,id});
	}
	void clear(int i){
		g[i].clear();
	}
	vector<edge>* operator[](int id){
		return &g[id];	
	}
};

// begin of BCC
const int N = 100005;
graph<N> g;
vector< vi > bccs;
vi path ; 
int tin = 0 ; 
void dfs(int x , int p = -1){
	g.in[x] = ++tin , g.low[x] = g.in[x];
	int filhos = 0;
	if(p != -1) path.push_back(p);
	allin(w, *g[x]){
		int v = w.x;
		if(g.in[v] == 0){
			dfs(v , x);
			path.push_back(w.id);
			g.low[x] = min(g.low[x] , g.low[v]);
			if(g.low[v] >= g.in[x] && p != -1){
				vi bcc;
				do{
					int u = path.back();
					path.pop_back();
					bcc.push_back(u);
					if(u == w.id) break;
				} while(1);
				bccs.push_back(bcc);
			}
		}
		else if(v != p){
			g.low[x] = min(g.low[x] , g.in[v]);
		}
	}
}
// end of BCC
// begin of Block-cut
void make_block_cut(){
	// só ligar art[i] com bcc j
}
// end of block-cut

// begin of circle-square-tree
// parecido com BCC, liga BLOCK == n + bcc(i) com todo mundo em bcc(i)
// arvore facil pra d&c, mas pode ser facilmente substituida por uma block cut?? 
// transforma a arvore em uma flor ????????????????
// end of circle-square-tree



int32_t main(){
	int n , m;
	cin >> n >> m ;

}