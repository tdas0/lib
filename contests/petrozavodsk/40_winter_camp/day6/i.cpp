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

#define int long long
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
#define int long long
///CUIDADO COM MAXN
#define N 500050
int n, v[N];

int MID, INF = (int)(1e9);
int dp[(1<<16)], vis[(1<<16)], cnt;
int solve(int mask){
	if(mask==0){
		return 0;
	}
	if(vis[mask] == cnt){
		return dp[mask];
	}
	vis[mask] = cnt;
	int sum = 0;
	for(int i = 0; i < n; i++)
		if((mask & (1<<i))) sum += v[i];

	int ans = -INF,can=0;

	for(int i = 0; i < n; i++){
		if((mask & (1<<i))){
			int mask2 = (mask^(1<<i));
			int S = min({0LL, sum, solve(mask2)});
			if(sum - S <= MID){
				ans = max(ans, min(S, sum));
				can=1;
			}
		}
	}
	if(!can) return dp[mask] = -INF;
	else return dp[mask] = ans;
}
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n;
	for(int i = 0; i < n; i++) cin>>v[i];
	int mx = -(int)(1e9);
	int ok = 1;
	for(int i = 0; i < n; i++){
		if(v[i] > 0) ok = 0;
		mx=max(mx, v[i]);
	}
	if(ok){
		cout<<mx<<"\n";
		return 0;
	}
	const int MX = 2000000;
	int ini = -MX, fim = MX, best;
	while(fim >= ini){
		MID= (ini + fim)/2;
		++cnt;
		if(solve((1<<n) - 1) != -INF){
			best=MID;
			fim = MID - 1;
		}
		else ini = MID + 1;
	}
	cout<<best<<"\n";
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
