#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;

// #define int long long
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
ll mod = (998244353LL);
inline ll Mod(ll a, ll b){return (a%b);}
inline ll poww(ll a, ll b){ll res = 1;while (b > 0){if(b & 1) res = (res * a)%mod;a = (a * a)%mod;b >>= 1;}return res;}
ll gcd (ll a, ll b) { while (b) { a %= b,swap(a, b);}return a;}
void read(vector<int> &w, int n){w.resize(n);for(int i = 0; i < n; i++) cin>>w[i];}
void print(vector<int> &w){for(int i =0; i < sz(w); i++){if(i == sz(w) - 1) cout<<w[i]<<"\n";else cout<<w[i]<<" ";}}
int prodmod(vector<int> w);
int summod(vector<int> w);
///CUIDADO COM MAXN
#define N 600050

int n, m, q, k, v[N], ans;
pii w[N];
string s;

ll prod1 = 1, prod2 = 1;
set<pii> grafo[N];
int vis[N];
int vis_edg[N], st;
void dfs(int x, int h , int pai){
	vis[x] = 1;
	for(auto v: grafo[x]){
		if(v.f == pai) continue;

		if(!vis[v.f] or v.f == st){
			if(h&1) prod1 = (prod1 * (1LL*v.s)) %mod;
			else prod2 = (prod2* (1LL*v.s)) %mod;
		}
		if(vis[v.f]) continue;
		dfs(v.f, h+1 , x);
	}
}
int grau[N];
bool state[N];
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n;
	for(int i = 1; i <= n; i++){
		int u1, w1, u2, w2;
		cin>>u1>>w1>>u2>>w2;
		grafo[i].insert({u1 + n, w1});
		grafo[i].insert({u2 + n, w2});
		grau[i] += 2;
		grau[u1+n]++;
		grau[u2+n]++;
		grafo[u1 + n].insert({i, w1});
		grafo[u2 + n].insert({i, w2});
	}
	queue<int> q;
	ll pesos = 1;
	for(int i = 1; i <= 2*n; i ++){
		if(grau[i] == 1) q.push(i);
	}
	while(sz(q)){
		int u = q.front();
		q.pop();
		for(auto w : grafo[u]){
			state[w.f] = (state[u] ^ 1);
			if(!state[u]){
				pesos = (pesos * w.s) % mod;
			}
			grafo[w.f].erase({u,w.s});
			grau[w.f] -- ;
			if(grau[w.f] == 1){
				q.push(w.f);
			}
		}
		grafo[u].clear();
	}
	ll ans = 1;
	for(int i = 1; i <= n; i++){
		if(vis[i] || sz(grafo[i]) == 0) continue;
		prod1 = 1;
		prod2 = 1;
		st = i;
		dfs(i, 0 , -1);
		ll sum = (prod1+prod2)%mod;
		ans = (ans*sum)%mod;
	}
	cout<<(ans * pesos) % mod<<"\n";
}
/*
    CUIDADO COM MAXN, MOD, OVERFLOW 
    >Colocar (>DEFINE INT LONG LONG<) no inicio do template
    >mod = (1e9 + 7), por padrao (NAO ESQUECER DE ALTERAR)
    >NAO ESQUECER DEFINE INT LONG LONG
    > N = 1 ? 
*/
int summod(vector<int> w){int curr=0;for(int i=0;i<sz(w); i++){curr = (curr+w[i])%mod;if(curr<0)curr+=mod;}return curr;}
int prodmod(vector<int> w){int curr = 1;
for(int i = 0; i < sz(w); i++){if(w[i] >= mod) w[i] %= mod;curr = (curr * w[i]) % mod;if(curr < 0) curr += mod;}return curr;}
