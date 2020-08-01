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
#define N 300050

int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int q;
	cin>>q;
	while(q--){
		int n, m, k;
		string s, t;
		cin>>n>>m>>k;
		cin>>s;
		cin>>t;
		vector<vector<int>> cost(n);
		for(int i = 0; i < n; i++){
			cost[i].resize(m);
			for(int j = 0; j < m; j++){
				if(s[i] != t[j]){
					cost[i][j] = 1;
				}
				else cost[i][j] = 0;

				if(i and j) cost[i][j] += cost[i-1][j-1];
			}
		}
		int ans = 0;
		
		for(int l1 = 0; l1 < n; l1++){
			for(int l2 = 0; l2 < m; l2 ++){
				if(l1 == 0 or l2 == 0){

				}else continue;	
				int L = 0;
				for(int R=0;;R++){
					if(l1 + R >= n || l2 + R>=m)break;

					int v0 = ((l1 + L and l2 + L) ? cost[l1 + L-1][l2 + L- 1] : 0);
					while(L<=R and cost[l1 + R][l2 + R] - v0 > k){
						L++;
						v0 = ((l1 + L and l2 + L) ? cost[l1 + L-1][l2 + L- 1] : 0);
					}
					if(L<=R)ans = max(ans,R-L+1);
				}
				
			}
		}

		cout<<ans<<"\n";
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
