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



struct bipartite_match{ // 1 indice
	int n , m;
	vector<vi> g; vi vis , match;
	bipartite_match(int n , int m) : n(n) , m(m), vis(n+m+2) , match(n+m+2) , g(n+m+2){}
	void addLR(int x , int y){ // aresta da esquerda pra direita
		g[x].push_back(y + n);
		return ;
	}
	void addRL(int x , int y){ // aresta da direita pra esquerda
		g[x+n].push_back(y);
		return ;
	}
	bool dfs(int x){
		allin(w,g[x]){
			if(vis[w]) continue;
			vis[w] = true;
			if(match[w] == 0 || dfs(match[w])){
				match[w] = x, match[x] = w; 
				return true;
			}
		}
		return false;
	}
	int solve(){
		int ans = 0; bool haspath;
		do{
			haspath = false;
			fill(all(vis) , false);
			for(int i = 1 ; i<= n + m; i ++){
				if(!match[i] && dfs(i)) haspath = 1 , ans ++ ;
			}
		} while(haspath);
		return ans;
	}
	int matchL(int x){return (match[x] ? match[x] - n : 0);}
	int matchR(int x){return match[x+n];}
};
int32_t main(){
	int n , m , p;
	cin >> n >> m >> p ;
	bipartite_match match(n , m);
	rep(i,0,p){
		int x , y ;
		cin >> x >> y;
		match.addLR(x,y);
	}
	cout << match.solve() << endl;
}