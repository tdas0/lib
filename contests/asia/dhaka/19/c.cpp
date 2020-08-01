#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
using namespace std;

// #define int long long
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
ll mod = (10000007LL);
inline ll Mod(ll a, ll b){return (a%b);}
inline ll poww(ll a, ll b){ll res = 1;while (b > 0){if(b & 1) res = (res * a)%mod;a = (a * a)%mod;b >>= 1;}return res;}
ll gcd (ll a, ll b) { while (b) { a %= b,swap(a, b);}return a;}
void read(vector<int> &w, int n){w.resize(n);for(int i = 0; i < n; i++) cin>>w[i];}
void print(vector<int> &w){for(int i =0; i < sz(w); i++){if(i == sz(w) - 1) cout<<w[i]<<"\n";else cout<<w[i]<<" ";}}
int prodmod(vector<int> w);
//MATH
void crivo(vector<int> &w, int TAM);
void inverso(vector<int> &inv, int TAM);
void fat_inverso(vector<int> &inv, int TAM);
int choose(int a, int b);
void get_fat();

///CUIDADO COM MAXN
#define N 500000
int fat[N];

int n, m, q, k, v[N], ans;
pii w[N];
string s;
vector<int> primes;
int y (int n, ll p){
	int ans = 0;
	ll pot= p;
	while(true){
		ans += (n/pot);
		if(n/pot == 0)break;
		pot *= p;
	}
	return ans;
}
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	vector<int> comp;
	crivo(comp, 1000050);
	while(1){
		int n;
		ll ans = 1;
		cin>>n;
		if(!n) return 0;
		for(auto p:primes){
			ll yi = y(n, p);
			//1+2+...+(yi + 1)
			ll curr = (yi + 2LL)*(yi + 1LL)/2;
			ans = (ans * curr)%mod;
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
int prodmod(vector<int> w){int curr = 1;
for(int i = 0; i < sz(w); i++){if(w[i] >= mod) w[i] %= mod;curr = (curr * w[i]) % mod;if(curr < 0) curr += mod;}return curr;}
void get_fat(){if(fat[0] != 0) return;fat[0]=1;for(int i = 1; i < N; i ++) fat[i]=(i*fat[i-1])%mod;}
int choose(int a, int b){get_fat();if(b>a) return 0;if(!b) return 1;
int A = fat[a];int B= (poww(fat[b],mod-2)*poww(fat[a-b], mod - 2))%mod;A = (A*B)%mod;return A;}
void inverso(vector<int> &inv, int TAM){inv.resize(TAM);inv[1] = 1;for (int i=2; i<TAM; ++i){inv[i] = (mod - (mod/i) * inv[mod%i] % mod) % mod;}}
void fat_inverso(vector<int> &inv, int TAM){inverso(inv, TAM);for(int i = 2; i < TAM; i++) inv[i] = (inv[i] * inv[i-1])%mod;}
void crivo(vector<int> &w, int TAM){
	w.resize(TAM + 1);w[0]=1;
	for(int i = 2; i < TAM; i++)
		if(!w[i]){
			for(int j = 2*i; j < TAM; j += i) w[j]=1;
			primes.pb(i);
		}
}
