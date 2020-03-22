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
	int low[SZ+1], in[SZ+1];
	ll sz[SZ+1] , c[SZ+1] ,ct = 0; 
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
const int N = 200005;
graph<N> g;
vi path ; 
int tin = 0 ; 
int pnode = 0 ;
graph<N> tree; 

void dfs(int x , int p = -1){
	g.in[x] = ++tin , g.low[x] = g.in[x];
	tree.sz[x] = 1;
	tree.c[x] = -1;
	tree.ct ++ ;
	path.push_back(x);
	allin(w, *g[x]){
		int v = w.x;
		if(g.in[v] == 0){
			dfs(v , x);
			g.low[x] = min(g.low[x] , g.low[v]);
			if(g.low[v] >= g.in[x]){
					pnode++;
					tree.add_edge(pnode , x,0);
					tree.add_edge(x, pnode,0);
					tree.c[pnode]++;
				do{
					int u = path.back();
					path.pop_back();
					tree.add_edge(pnode,u,0) , tree.add_edge(u,pnode,0) , tree.c[pnode]++;
					if(u == v) break;
				} while(1);
			}
		}
		else if(v != p){
			g.low[x] = min(g.low[x] , g.in[v]);
		}
	}
}
ll ans = 0;
void cst(int x , int p = -1){
	ll pontas = 0 ;
	trav(w, *tree[x]){
		int v = w.x;
		if(v == p) continue;
		cst(v, x);
		pontas = tree.sz[x] * tree.sz[v] + pontas;
		tree.sz[x] += tree.sz[v];
	}
	pontas = pontas + tree.ct*tree.sz[x] - tree.sz[x]*tree.sz[x]; 
	ans = (ans + 2ll*tree.c[x]*pontas);
}

int getint(){
	char c;
	int a = 0;
	while(!(c>='0'&&c<='9')) c=  getchar();
	while(c>='0'&&c<='9') a = 10*a + (c-'0') , c = getchar();
	return a;
}

int32_t main(){
	int n=getint() , m=getint();
	pnode = n + 1;
	rep(i,0,m){
		int x , y;
		x = getint() , y = getint();
		g.add_edge(x,y,i);
		g.add_edge(y,x,i);
	}
	for(int i = 1;  i <= n; i ++){
		if(!g.in[i]){
			tree.ct = 0;
			dfs(i);
			cst(i);
		}
	}
	printf("%lld\n" , ans);
}