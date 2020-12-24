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
#define N 270000
#define min(a,b) (a<b ? a : b)
int n, m, q, k, v[N], ans;
pii w[N];
string s;

ll dp[N][11][11][3];
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>k;
	for(int i = 1; i <= n; i++) cin>>v[i];

	const ll inf = (ll)(1e17);
	for(int i = n+1;i>=1;i--){
		for(int bad = 0;bad <= k; bad++){
			for(int good = 0; good <= k; good ++){
				for(int delta = 0; delta < 3; delta++){
					if(i ==3 and delta == 2){
						dp[i][bad][good][delta] = inf;
					}
					else if(i > n){
						if(delta == 2){
							dp[i][bad][good][delta] = inf;
						}
						else if(bad == good) dp[i][bad][good][delta] = 0;
						else dp[i][bad][good][delta] = inf;
					}
					else{
						ll A = dp[i + 1][bad][good][0] + 1LL*v[i];
						//tou escolhendo mas vou remover
						ll B = (bad < k ? dp[i + 1][bad + 1][good][0] : inf);
						//nao tou escolhendo mas vou adicionar
						ll C = ((good < k and delta<2) ? dp[i + 1][bad][good + 1][delta+1] + 1LL*v[i] : inf);
						//nao escolho e cago pra ele
						ll D = (delta < 2? dp[i + 1][bad][good][delta+1]:inf);

						if(delta == 2) dp[i][bad][good][delta] = min(A, B);
						else dp[i][bad][good][delta] = min(A, min(B, min(C, D)));

					}
				}
			}
		}
	}
	cout<<dp[1][0][0][1]<<"\n";
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