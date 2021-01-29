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
#define N 500050
pii v[N];
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int test;
	cin>>test;
	while(test--){
		int n, P, Q, ans = 1;
		cin>>n;
		vector<int> pref(n + 1), cnt(n + 2);
		for(int i = 1; i <= n; i++) cin>>v[i].f,v[i].s=i;
		sort(v + 1, v + n + 1);
		for(int i = 1; i <= n; i++) pref[i] = pref[i-1]+v[i].f;
		cin>>P>>Q;

		int ptr = n, sum = 0,qtd=0;
		//(soma) * p >= maior * qtd * q
		for(int i = n; i >= 1; i--){

			while(ptr >= 1 and ( (sum + v[ptr].f) * P) >= (v[i].f)*(qtd + 1)*Q){
				sum += v[ptr].f;
				qtd ++;
				ptr--;
			}

			ans = max(ans, qtd);
			// cout<<"intervalo "<<i<<" "<<i-qtd+1<<"\n";
			qtd --;
			sum -= v[i].f;

		}

		//(soma) * p >= maior * qtd * q
		vector<int> Lpoints(n + 1), Rpoints(n + 1);
		for(int i = 1; i <= n; i++){
			if(i - ans + 1 >= 1){
				int Sl = pref[i] - pref[i-ans];
				if(Sl * P >= v[i].f*ans*Q){
					cnt[i-ans+1] ++;
					cnt[i + 1] --;
					// cout<<i-ans+1<<" "<<i<<" SSSS \n";
					Lpoints[i-ans + 1] = 1;
					Rpoints[i] = 1;
				}
			}
		}


		vector<int> resp;
		//(soma) * p >= maior * qtd * q
		int R = -1;
		//v[i]*p >= v[r]*ans*q - p*(soma - v[l]) 
		int curr = ((int)(1e18));
		for(int i = n; i >= 1; i--){
			if(Rpoints[i]){
				R = i;
				int L = i - ans + 1;
				curr = min(curr, v[i].f*ans*Q - P*(pref[i] - pref[L]));
			}
			else if(R != -1){
				if(v[i].f*P >= curr){
					cnt[i] ++;
					cnt[i+1]--;
				}
			}
		}

		for(int  i = 1; i <= n; i++){
			cnt[i] += cnt[i-1];
			assert(cnt[i] >= 0);
			if(!cnt[i]) resp.pb(v[i].s);
		}

		cout<<sz(resp)<<"\n";
		if(resp.empty()) cout<<"\n";
		sort(all(resp));
		print(resp);
	}
}
/*
	P/Q = 2

	 1 [1 2 5] 15

	 (soma) * p >= maior * qtd * q



    CUIDADO COM MAXN, MOD, OVERFLOW 
    >Colocar (>DEFINE INT LONG LONG<) no inicio do template
    >mod = (1e9 + 7), por padrao (NAO ESQUECER DE ALTERAR)
    >NAO ESQUECER DEFINE INT LONG LONG
    > N = 1 ? 
*/
int summod(vector<int> w){int curr=0;for(int i=0;i<sz(w); i++){curr = (curr+w[i])%mod;if(curr<0)curr+=mod;}return curr;}
int prodmod(vector<int> w){int curr = 1;
for(int i = 0; i < sz(w); i++){if(w[i] >= mod) w[i] %= mod;curr = (curr * w[i]) % mod;if(curr < 0) curr += mod;}return curr;}
