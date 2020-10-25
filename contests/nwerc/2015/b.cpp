// upsolving
#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp(a,b) make_pair(a,b)
#define ms(v,x) memset(v,x,sizeof(v))
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define Unique(v) sort(all(v));v.erase(unique(all(v)),v.end());
#define sz(v) ((int)v.size())
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
#define prl cerr<<"called: "<< __LINE__ << endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll a,ll b,ll m){
    if(b==0LL) return 1LL;
    if(b==1LL) return mod(a,m);
    ll k = mod(exp(a,b/2,m),m);
    if(b&1LL){
        return mod(a*mod(k*k,m),m);
    }
    else return mod(k*k,m);
}

int n,p;
const int N = 205;
const int inf = 1e9;
int dp[N][N];
pii inter[N][N];
int l[N],r[N];

int32_t main(){
  fastio;
  cin >> n >> p;
  vi vec;
  vi ids;
  for(int i=0;i<n;i++){
    cin >> l[i] >> r[i];  
    ids.pb(i);  
  } 
  sort(all(ids),[&](int a,int b){
    return r[a] - l[a] < r[b] - l[b];
  });
  vi good;
  rep(ii,0,n){
    int ok=0,i = ids[ii];
    rep(jj,0,ii){
    int j = ids[jj];
    if(l[i]<=l[j] and r[j]<=r[i]){
      ok=1;
      break;
    }
    }
    if(ok)good.pb(r[i] - l[i]);
    else vec.pb(i);
  }
  sort(all(vec),[&](int a,int b){
    if(l[a] == l[b])return r[a] < r[b];
    return l[a] < l[b];
  });
  rep(i,0,N)rep(j,0,N)dp[i][j] = -inf;
  for(int i=0;i<sz(vec);i++){
    inter[i][i] = pii(l[vec[i]],r[vec[i]]);
    for(int j=i+1;j<sz(vec);j++){
      inter[i][j].ff = max(l[vec[j]],inter[i][j-1].ff);
      inter[i][j].ss = min(r[vec[j]],inter[i][j-1].ss);
    }
  }
  dp[0][0]=0;
  for(int i=1;i<=sz(vec);i++){
    for(int g=1;g<=p;g++){
      for(int j=1;j<=i;j++)if(inter[j-1][i-1].ff<inter[j-1][i-1].ss){
        dp[i][g] = max(dp[i][g],
          dp[j-1][g-1] + inter[j-1][i-1].ss - inter[j-1][i-1].ff
          );
      }
    }
  }
  ll res=0;
  sort(all(good),greater<int>());
  ll cur=0,it=0;
  for(int g=p;g>=0;g--){
    if(g == 0 and sz(vec))break;
    res = max(res,dp[sz(vec)][g] + cur);
    //cout << dp[sz(vec)][g]<<" "<<cur<<endl;
    if(it<sz(good))cur+=good[it++];
    else break;
  }
  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
