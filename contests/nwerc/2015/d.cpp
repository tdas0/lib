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
//#define N 1010

int n;
ll p, r, s;
/*
ll dp[N];
ll dp2[N];
*/
int cela(int n,int k){
  return (n+k-1)/k;
}
int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  cin>>n>>r>>p;
  ll res = (n == 1 ? 0ll : (ll)1e18);
  for(int d=1;d<n;d++){
    ll L = 1, R = min(100ll,d);
    int ans = -1;
    while(L<=R){
      int mid = (L+R)/2;
      int fim = n;
      int bota1 = (d/mid);
      int bota2 = cela(d,mid);
      int big = d%mid,small = mid - big;
      for(int i=0;i<big;i++){
        if(fim<=1)break;
        fim = cela(fim,bota2 + 1);
      }
      for(int i=0;i<small;i++){
        if(fim<=1)break;
        fim = cela(fim,bota1 + 1);
      }
      if(fim == 1){
        ans = mid;
        R = mid-1;
      }else L = mid + 1;
    }
    if(ans!=-1){
      res=min(res,ans * r + d * p);
    }
  //  cout << d<<" "<<ans<<" "<<ans*r+d*p<<endl;
  }
  cout << res << endl;
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
