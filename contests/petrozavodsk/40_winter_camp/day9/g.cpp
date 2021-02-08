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
//#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}

struct Line {
  mutable ll k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) { x->p = inf; return false; }
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(ll k, ll m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};
const int N = 305;
int Q[N][N];
int pre[N][N];
int get(int i1,int j1,int i2,int j2){
  return pre[i2][j2] - pre[i1-1][j2] - pre[i2][j1-1] + pre[i1-1][j1-1];
}
LineContainer CHT[N];

ll dp[N][N];
bool vis[N][N];
int n;

ll solve(int l,int r){
  if(l>r)return 0;
  ll&x = dp[l][r];
  if(vis[l][r])return x;
  vis[l][r]=1;
  x=-(ll)1e18;

  for(int i=l;i<=r;i++){
    int qtd = get(l,i,i,r);
    /*int q=0;

    rep(j,l,i+1){
      rep(k,i,r+1)q+=Q[j][k];
    }
    if(q!=qtd){
      cout << i <<" "<<l<<" "<<r<<endl;
      cout << q<<" "<<qtd<<endl;
      exit(0);

    }*/

    x = max(x,solve(l,i-1)+solve(i+1,r)+CHT[i].query(qtd));
  }
  return x;
}

int32_t main(){
  fastio;
  ms(dp,-1);
  cin >> n;
  for(int i=1;i<=n;i++){
    for(int j=i;j<=n;j++)cin >> Q[i][j];
  }
  rep(i,1,n+1){
    rep(j,1,n+1){
      pre[i][j] = Q[i][j] + pre[i][j-1] + pre[i-1][j] - pre[i-1][j-1];
    }
  }
  for(int i=1;i<=n;i++){
    int k;
    cin >> k;
    rep(jj,0,k){
      ll v,c;
      cin >> v >> c;
      CHT[i].add(v,-c);
    }
  }

  cout << solve(1,n) << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
