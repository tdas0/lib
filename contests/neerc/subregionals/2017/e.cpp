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

int n, m, q, k, v[N], ans;
// vector<int> grafo[N];
// pii w[N];
string s, t[1050];

int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	set<char> caras;
	cin>>n;
	cin>>s;
	for(auto c: s)
		if(c != '*') caras.insert(c);
	cin>>m;
	vector<string> possiveis;
	for(int i= 1; i <= m; i++){
		cin>>t[i];
		int can = 1;
		for(int j = 0; j < n; j++){
			if(s[j] != '*' and s[j] != t[i][j]) can = 0;
			if(s[j] == '*' and caras.count(t[i][j])) can = 0;
		}
		if(can) possiveis.pb(t[i]);
	}

	for(char c = 'a'; c <= 'z'; c++){
		int cost = 0;
		for(auto tt: possiveis){
			int can = 1, tem = 0;
			for(int j = 0; j < n; j++){
				if(s[j] != '*' and s[j] != tt[j]) can = 0;
				if(s[j] == '*' and tt[j] == c) tem = 1;
			}
			if(can and tem){
				cost ++;
			}
		}
		if(cost==sz(possiveis)) ans ++;
	}
	cout<<ans<<"\n";
	
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
