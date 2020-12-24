
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

///CUIDADO COM MAXN
#define N 52

int n, k;
ll v[N], A, B, ans;

ll CARA, dp[55][55][2];
ll solve(int i, int qtd, int flag){
	if(qtd < 0) return 0;
	if(i < 0){
		if(!qtd) return 1;
		return 0;
	}
	if(dp[i][qtd][flag] != -1) return dp[i][qtd][flag];
	if(flag == 1){
		ll A = solve(i - 1, qtd - 1, flag); // coloca 1
		ll B = solve(i - 1, qtd, flag); // coloca 0
		return dp[i][qtd][flag] =A+B;
	}
	else{
		if(CARA & (1LL<<i)){
			ll A = solve(i - 1, qtd - 1, 0); // coloca 1
			ll B = solve(i-1, qtd, 1); // coloca 0
			return dp[i][qtd][flag] =A+B;
		}
		else return dp[i][qtd][flag] =solve(i - 1, qtd, 0);
	}
}
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>k;
	for(int i = 0; i < n; i++) cin>>v[i];
	cin>>A>>B;
	sort(v,v+n);
	ll ini = 0, fim = (1ll<<n) - 1, mid, best = -1;
	while( fim >= ini){
		mid = (ini + fim)/2;
		ll cost = 0;
		for(ll i = 0; i < n; i++){
			if(mid & (1LL<<i)) cost += v[i];
			if(cost > B) break;
		}
		// cout<<mid<<" "<<cost<<"\n";
		if(cost <= B) best = mid, ini = mid + 1;
		else fim = mid - 1;
	}
	ini = 0, fim = (1ll<<n) - 1, mid;
	ll best2 = -1;
	while( fim >= ini){
		mid = (ini + fim)/2;
		ll cost = 0;
		for(ll i = 0; i < n; i++){
			if(mid & (1LL<<i)) cost += v[i];
			if(cost > B) break;
		}
		if(cost < A) best2 = mid, ini = mid + 1;
		else fim = mid - 1;
	}
	// cout<<best<<" "<<best2<<"\n";
	// return 0;
	memset(dp,-1,sizeof dp);
	CARA = best;
	ll p = solve(n-1, k, 0);
	memset(dp,-1,sizeof dp);
	CARA = best2;
	ll q = solve(n-1,k,0);
	cout<<p-q<<"\n";
}
/*
    CUIDADO COM MAXN, MOD, OVERFLOW 
    >Colocar (>DEFINE INT LONG LONG<) no inicio do template
    >mod = (1e9 + 7), por padrao (NAO ESQUECER DE ALTERAR)
    >NAO ESQUECER DEFINE INT LONG LONG
    > N = 1 ? 
*/
