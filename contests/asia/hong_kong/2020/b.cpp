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
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}

const int N = 5050;
vi g[N];
int dp[N];
int ok[N];
int solve(int v,int p){
  if(dp[v]!=-1)return dp[v];
  set<int> S;
  ok[v]=1;
  int num=0;
  int xo=0;
  for(int to : g[v])if(to!=p){
    xo^=solve(to,v);
    if(!ok[to])
      ok[v]=0;
    num++;
  }
  if(num==1)ok[v]=0;

  if(ok[v]){
    S.insert(0);
  }
  if(num > 0){
    S.insert(xo);
  }
  for(int i=0;;i++){
    if(S.count(i)==0){
      dp[v] = i;
      break;
    }
  }
  return dp[v];
}

int32_t main(){
  fastio;
  int t;
  cin >> t;
  while(t--){
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)g[i].clear(),dp[i]=-1;
    for(int i=1;i<n;i++){
      int a,b;
      cin >> a >> b;
      g[a].pb(b);
      g[b].pb(a);
    }
    cout << (solve(1,-1) ? "Alice" : "Bob") << endl;

  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
