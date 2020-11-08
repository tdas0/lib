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
ll mod = (1000000007LL);
inline ll Mod(ll a, ll b){return (a%b);}
inline ll poww(ll a, ll b){ll res = 1;while (b > 0){if(b & 1) res = (res * a)%mod;a = (a * a)%mod;b >>= 1;}return res;}
ll gcd (ll a, ll b) { while (b) { a %= b,swap(a, b);}return a;}
void read(vector<int> &w, int n){w.resize(n);for(int i = 0; i < n; i++) cin>>w[i];}
void print(vector<int> &w){for(int i =0; i < sz(w); i++){if(i == sz(w) - 1) cout<<w[i]<<"\n";else cout<<w[i]<<" ";}}
int prodmod(vector<int> w);
int summod(vector<int> w);
///CUIDADO COM MAXN
#define N 1000001

int n, m, q, k, v[N], ans;
// vector<int> grafo[N];
// pii w[N];
string s;
vector<int> P, pref;
//0 = LEFT
//1 = RIGHT
int count(int l, int r){
	if(l>r) return 0;
	return pref[r] - (l?pref[l-1]:0);
}
int dp[N][2],primeiro=-1;

int vis[N][2], tempo;
int solve(int i, int ant, int& w){
	if(i < 0) return -1;
	if(vis[i][ant] == tempo) return dp[i][ant];
	vis[i][ant] = tempo;
	int plef = solve(i-1,0, w);
	int prig = solve(i-1,1, w);

	int ans = -1;

	//vou para a direita
	if(!count( max(plef, prig) + 1, P[i] - 1)){
		int cost = max({plef, prig, P[i] + w});
		ans = max(ans, cost);
	}

	//vou para esquerda e o anterior foi pra esquerda
	if(!count( plef + 1, P[i] - w - 1)){
		ans = max(ans, max(plef, P[i]));
	}
	// vou para esquerda e o anterior foi pra direita
	int other = solve(i-2,0,w);
	if(i >= 1 and !count(other + 1, P[i] - w - 1) and P[i-1] + w > P[i]){
		if(i == 1){
			if(P[1] - w <= primeiro) ans = max(ans, P[i-1]+w);
		}
		else ans = max(ans, P[i-1] + w);
	}
	return dp[i][ant]=ans;
}
int last;
int check(int w){
	++tempo;
	int S = max(solve(sz(P)-1,0,w), solve(sz(P)-1,0,w));
	return (S >= last);
}
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n;
	cin>>s;
	for(int i = 0; i < n; i++){
		if(s[i] == 'P') P.pb(i);
		pref.pb((pref.empty()?0:pref.back()) + (s[i] == '*'));
		if(s[i]=='*') last = i,q++;
		if(primeiro == -1 and s[i] == '*') primeiro = i;
	}
	if(sz(P) == 1){
		pii L={0,0}, R = {0, 0};
		int p = P[0];
		for(int i = p-1;i >= 0;i--) if(s[i] == '*') L.f ++, L.s = -abs(p-i);
		for(int i = p+1;i<n;i++) if(s[i] == '*') R.f ++, R.s = -abs(p-i);
		cout<<(max(L, R)).f<<" "<<-(max(L, R)).s<<"\n";
	}
	else{
		int ini = 0, fim = n+1,mid,best=-1;
		while(fim >= ini){
			mid = (ini + fim)/2;
			if(check(mid)) fim =mid-1,best=mid;
			else ini=mid+1;
		}
		assert(best != -1);
		cout<<q<<" "<<best<<"\n";
	}
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
