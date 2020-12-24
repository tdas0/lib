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
#define N (1594323 + 100)

int n, k, q;
vector<int> v[N];
int cost[N];
vector < vector<int> > caras;

int pow3[20];
int get_mask(int mask, int i){
	return (mask/pow3[i]) % 3;
}

bool vis[N];
void gen(int mask){
	if(vis[mask]) return;
	vis[mask] = 1;
	for(int i = 0; i < k; i++){
		int value = get_mask(mask, i);
		if(value == 2){
			int L = mask, R = mask;
			L += -2*pow3[i] + pow3[i];
			R += -2*pow3[i];
			gen(L);
			gen(R);
			cost[mask] += cost[L] + cost[R];
			break;
		}
	}
}

int dp[N];
int solve(int mask){
	int C = cost[mask], qtd=0;
	if(dp[mask] != -1) return dp[mask];
	for(int i = 0; i < k; i++){
		int value = get_mask(mask, i);
		if(value != 2) qtd ++;
	}
	// cout<<"solve "<<qtd<<"\n";
	if(C == 0) return  dp[mask] =1000;
	if(C == 1) return dp[mask] = qtd;

	int best= k;
	for(int i =0;i<k;i++){
		int value = get_mask(mask,i);
		if(value != 2) continue;
		// cout<<"FOR "<<i<<"\n";
		int L = mask - 2*pow3[i] + pow3[i];
		int R = mask - 2*pow3[i];
		int cur = max(solve(L), solve(R));
		if(best > cur) best= cur;
	}
	return dp[mask] =best;
}
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>q;
	pow3[0] = 1;
	for(int i = 1; i < 20; i++) pow3[i] = (3*pow3[i-1]);
	while(q--){
		memset(cost,0,sizeof cost);
		memset(vis,0,sizeof vis);
		memset(dp,-1,sizeof dp);
		cin>>n>>k;
		for(int i = 0; i < n; i++){
			v[i].clear();
			string s;
			cin>>s;
			int curr = 0;
			for(int j = 0; j < k; j++){
				int x=(s[j]-'0');
				v[i].pb(x);
				if(x == 1) curr += pow3[j];
			}
			cost[curr] ++;
		}
		int cara=0;
		for(int i = 0; i < k; i++) cara += 2*pow3[i];
		for(int mask = 0; mask < (pow3[k]); mask ++){
			gen(mask);
		}
		// for(auto w: cost){
		// 	cout<<"COST ";
		// 	for(auto u: w.f) cout<<u<<" ";
		// 	cout<<"   == "<<cost[w.f]<<"\n";
		// }
		cout<<solve(cara)<<"\n";
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
