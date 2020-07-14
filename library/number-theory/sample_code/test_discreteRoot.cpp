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
ll mod = (998244352LL);
inline ll Mod(ll a, ll b){return (a%b);}
inline ll poww(ll a, ll b){ll res = 1;while (b > 0){if(b & 1) res = (res * a)%mod;a = (a * a)%mod;b >>= 1;}return res;}
ll gcd (ll a, ll b) { while (b) { a %= b,swap(a, b);}return a;}
void read(vector<int> &w, int n){w.resize(n);for(int i = 0; i < n; i++) cin>>w[i];}
void print(vector<int> &w){for(int i =0; i < sz(w); i++){if(i == sz(w) - 1) cout<<w[i]<<"\n";else cout<<w[i]<<" ";}}
int prodmod(vector<int> w);
int summod(vector<int> w);
///CUIDADO COM MAXN
#define MAXN 120

int n, m, q, k, v[MAXN], ans;
pii w[MAXN];
string s;
int b[MAXN];

struct DiscreteRoot{
	inline int generator(int p) {
	    vector<int> fact;
	    int phi = p-1, n = phi;
	    for (int i = 2; i * i <= n; ++i) {
	        if (n % i == 0) {
	            fact.push_back(i);
	            while (n % i == 0)
	                n /= i;
	        }
	    }
	    if (n > 1)
	        fact.push_back(n);

	    for (int res = 2; res <= p; ++res) {
	        bool ok = true;
	        for (int factor : fact) {
	            if (poww(res, phi / factor) == 1) {
	                ok = false;
	                break;
	            }
	        }
	        if (ok) return res;
	    }
	    return -1;
	}

	// This program finds all numbers x such that x^k = a (mod n)
	inline void solve(ll n, ll k, ll a){
		mod = n;
		ll g = generator(n);
	   ll sq = (ll) sqrt (n + .0) + 1;
	    vector<pair<ll, ll> > dec(sq);
	    for (ll i = 1; i <= sq; ++i)
	        dec[i-1] = {poww(1LL*g, 1LL*i * sq * k % (n - 1)), i};
	    sort(dec.begin(), dec.end());
	    ll any_ans = -1;
	    for (ll i = 0; i < sq; ++i) {
	        ll my = poww(g, i * k % (n - 1)) * a % n;
	        auto it = lower_bound(dec.begin(), dec.end(), pair<ll, ll>(my, 0));
	        if (it != dec.end() && it->first == my) {
	            any_ans = it->second * sq - i;
	            break;
	        }
	    }
	    if (any_ans == -1) {
	        puts("-1");
	        exit(0);
	    }
	    else{

	    // Print all possible answers
		    ll delta = (n-1) / gcd(k, n-1);
		    for (ll cur = any_ans % delta; cur < n-1; cur += delta){
		        // ans.push_back(poww(1LL*g, 1LL*cur));
		        cout<<poww(1LL*g, 1LL*cur)<<"\n";
		        exit(0);
		    }
		    // sort(ans.begin(), ans.end());
		    // cout<<ans[0]<<"\n";
		    // exit(0);
		    // printf("%d\n", ans.size());
		    // for (int answer : ans)
		        // printf("%d ", answer);
		}
	}
};
template<class T, int N> struct Matrix {
	typedef Matrix M;
	array<array<T, N>, N> d{};
	M operator*(const M& m) const {
		M a;
		rep(i,0,N) rep(j,0,N)
			rep(k,0,N){
				a.d[i][j] += d[i][k]*m.d[k][j];
				a.d[i][j] %= mod;
			}
		return a;
	}
	vector<T> operator*(const vector<T>& vec) const {
		vector<T> ret(N);
		rep(i,0,N) rep(j,0,N){
			ret[i] += d[i][j] * vec[j];
			ret[i] %= mod;
		}
		return ret;
	}
	M operator^(ll p) const {
		assert(p >= 0);
		M a, b(*this);
		rep(i,0,N) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};
// int solve(int i){
// 	if(i < k) return 0;
// 	if(i==k) return 1;
// 	int ans = 0;
// 	for(int j = 1; j <= k; j++){
// 		ans += solve(i-j)*b[j];
// 	}
// 	return ans;
// }
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>k;
	for(int i = 1; i <= k; i++) cin>>b[i];
	cin>>n>>m;
	Matrix <ll, 100> base;
	for(int j = 0; j < k -1; j++){
		base.d[j+1][j] = 1;
	}
	for(int i=0;i<k;i++) base.d[i][k-1] = b[k-i];

	Matrix <ll, 100> M;
	M.d[0][k-1] = 1;
	// for(int i = 0; i < k; i++){
	// 	for(int j = 0; j < k; j++){
	// 		cout<<base.d[i][j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }
	base = (base^(n-1));
	M = M*base;
	int alpha = M.d[0][0];
	mod ++;
	DiscreteRoot R;
	R.solve(mod, alpha, m);
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
