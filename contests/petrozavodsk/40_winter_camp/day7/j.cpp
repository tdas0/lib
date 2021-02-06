#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using namespace std;

// #define int long long
typedef long long ll;
typedef pair<int, int> pii;

#define N 200050
int n;
int qtd[N];
vector<int> grafo[N];

void dfs0(int x, int p){
	qtd[x] = 0;
	for(auto v: grafo[x]){
		if(v == p) continue;
		qtd[x] ^= 1;
		dfs0(v, x);
	}
}

vector<pii> ans;
int sobra[N];
void dfs(int x, int p){
	int lixo = -1, curr = 0;
	vector<int> good;
	for(auto v: grafo[x]){
		if(v == p) continue;
		// curr ++;
		dfs(v, x);
		if(sobra[v] != -1){
			ans.pb({sobra[v], x});
		}
		else good.pb(v);
	}

	if(sz(good) % 2 == 0){
		for(int i = 0; i < sz(good); i += 2)
			ans.pb({good[i], good[i+1]});
	}
	else{
		sobra[x] = good.back();
		good.pop_back();
		for(int i = 0; i < sz(good); i += 2)
			ans.pb({good[i], good[i+1]});
	}
}
int32_t main(){
	memset(sobra, -1, sizeof sobra);
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n;
	for(int i = 1; i < n; i++){
		int a, b;
		cin>>a>>b;
		grafo[a].pb(b);
		grafo[b].pb(a);
	}

	dfs(1, 1);
	cout<<sz(ans)<<"\n";
	for(auto w: ans) cout<<w.f<<" "<<w.s<<"\n";
}
