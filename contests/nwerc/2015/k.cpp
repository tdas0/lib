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
///CUIDADO COM MAXN
#define N 300050

int r,s,m, d, n, bb[N];
vector<int> A[N], B[N], C[N];
int block[1020][1020];

const ll INF = (ll)(1e18);
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>r>>s>>m>>d>>n;
	for(int i = 1; i <= r; i++) cin>>bb[i];
	for(int i = 1; i <=s+m+d; i++){
		int x;
		cin>>x;
		while(x--){
			int y;
			cin>>y;
			A[i].pb(y);
		}
	}

	for(int i = 1; i <= n; i++){
		int a, b;
		cin>>a>>b;
		block[a][b]=block[b][a] = 1;
	}
	int ans= 0;
	for(int a = 1; a <= s; a++){
		for(int b = s+1; b <= m+s; b++){
			for(int c = m+s+1; c <= m+s+d; c++){
				if(block[a][b] or block[a][c] or block[b][c]) continue;
				vector<int> caras;
				for(auto x: A[a]) caras.pb(x);
				for(auto x: A[b]) caras.pb(x);
				for(auto x: A[c]) caras.pb(x);
				sort(all(caras));
				caras.erase(unique(all(caras)), caras.end());
				int curr = 1;
				for(auto x: caras){
					//curr * b[x] <= INF
					//b[x] <= INF/curr
					if(bb[x] > INF/curr){
						curr = INF + 1LL;
						break;
					}
					curr *= bb[x];
					if(curr > INF){
						curr = INF + 1LL;
						break;
					}
				}
				ans += curr;
				if(ans > INF){
					ans = INF + 1LL;
					break;
				}
			}
		}
	}
	if(ans > (ll)(1e18)) cout<<"too many\n";
	else cout<<ans<<"\n";
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
