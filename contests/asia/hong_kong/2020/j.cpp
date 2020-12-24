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
const int mod = (1000000007LL);
inline ll Mod(ll a, ll b){return (a%b);}
inline ll poww(ll a, ll b){ll res = 1;while (b > 0){if(b & 1) res = (res * a)%mod;a = (a * a)%mod;b >>= 1;}return res;}
ll gcd (ll a, ll b) { while (b) { a %= b,swap(a, b);}return a;}
void read(vector<int> &w, int n){w.resize(n);for(int i = 0; i < n; i++) cin>>w[i];}
void print(vector<int> &w){for(int i =0; i < sz(w); i++){if(i == sz(w) - 1) cout<<w[i]<<"\n";else cout<<w[i]<<" ";}}
int prodmod(vector<int> w);
int summod(vector<int> w);
///CUIDADO COM MAXN
#define N 300050

int n, m, q, k, v[N], ans;
// vector<int> grafo[N];
// pii w[N];
// string s;
string L, R;
#define M 
int pot10[5010];

int tempo;
int dp[5010][2][61][61];
int vis[5010][2][61][61];
int solve(int i, int f, int cost, int sum){
	if(i == sz(R)){
		if(!cost) return 1;
		return 0;
	}
	if(vis[i][f][cost][sum] == tempo) return dp[i][f][cost][sum];
	vis[i][f][cost][sum] = tempo;
	int ans = 0;
	for(int j = 0; j < 10; j++){
		bool can = true;
		int f2 = f, cost2 = cost + j*(pot10[sz(R)-i-1] - sum + m)%m, sum2 = (sum + j)%m;
		// cost2 %= m;
		if(cost2 >= m) cost2 -= m;
		if(!f){
			if(j < (R[i] - '0')) f2 = 1;
			if(j > (R[i]-'0')) can = false;
		}
		if(!can) break;
		ans += solve(i + 1, f2, cost2, sum2);
		if(ans >= mod) ans -= mod;
	}

	return dp[i][f][cost][sum] = ans;
}

int solve2(int i, int f, int cost, int sum){
	if(i == sz(L)){
		if(!cost and f) return 1;
		return 0;
	}
	if(vis[i][f][cost][sum] == tempo) return dp[i][f][cost][sum];
	vis[i][f][cost][sum] = tempo;
	int ans = 0;
	for(int j = 0; j < 10; j++){
		bool can = true;
		int f2 = f, cost2 = cost + j*(pot10[sz(L)-i-1] - sum + m)%m, sum2 = (sum + j)%m;
		// cost2 %= m;
		if(cost2 >= m) cost2 -= m;
		if(!f){
			if(j < (L[i] - '0')) f2 = 1;
			if(j > (L[i]-'0')) can = false;
		}
		if(!can) break;
		ans += solve2(i + 1, f2, cost2, sum2);
		if(ans >= mod) ans -= mod;
	}

	return dp[i][f][cost][sum] = ans;
}

int get(int flag){
	int tam = (flag ? sz(R): sz(L));
	string curr = (flag?R:L);
	// memset(dp,0, sizeof)
	for(int i = tam; i >= 0; i--){
		for(int f = 0; f < 2; f++){
			for(int cost = 0; cost < m; cost ++){
				for(int sum = 0; sum < m; sum ++){
					dp[i][f][cost][sum]=0;
					if(i==tam){
						if(flag)dp[i][f][cost][sum] = (cost==0);
						else dp[i][f][cost][sum] = (cost == 0 && f);
						continue;
					}
					for(int j = 0;j<10;j++){
						if(f || j <= curr[i]-'0')
							dp[i][f][cost][sum] += dp[i+1][(f||j<curr[i]-'0')][ (cost + j*(pot10[tam-i-1] - sum + m)%m )%m][(sum+j)%m];
						else break;
						if(dp[i][f][cost][sum] >= mod) dp[i][f][cost][sum] -= mod;
					}
				}
			}
		}
	}
	return dp[0][0][0][0];
}
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>q;
	pot10[0] = 1;
	while(q--){
		cin>>L>>R>>m;
		for(int i = 1; i <= 5000; i++){
			pot10[i] = (pot10[i-1]*10)%m;
		}
		cout<<(get(1)-get(0) + mod)%mod<<"\n";
		// cout<<get(1)<<" "<<get(0)<<"\n";
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
