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

int p[22];

const int N = 200100;
int deck[N];

int c[N];

int BIT[N];
int tin[N],tout[N],t=0;
vi g[N];
int ans[N][20];
void dfs(int v,int p){
  tin[v] = ++t;
  ans[v][0] = p;
  rep(j,1,20)ans[v][j]=ans[ans[v][j-1]][j-1];
  for(int to : g[v])if(to!=p){
    dfs(to,v);
  }
  tout[v] = t;

}
int is_ans(int a,int b){
  return tin[a]<=tin[b] and tout[a]>=tout[b];
}
int lca(int a,int b){
  if(is_ans(a,b))return a;
  if(is_ans(b,a))return b;
  for(int j=19;j>=0;j--){
    if(!is_ans(ans[a][j],b))a=ans[a][j];
  }
  return ans[a][0];
}
void upd(int x,int v){
  assert(x>0);
  while(x<N){
    BIT[x]^=v;
    x+=(x&-x);
  }
}
int sum(int x){
  int r=0;
  while(x>0){
    r^=(BIT[x]);
    x-=(x&-x);
  }
  return r;
}
int query(int x,int y){
  int val = sum(tin[x])^sum(tin[y])^(1<<c[lca(x,y)]);
  return val;
}

void update(int v,int x){
  int val = (1<<x)^(1<<c[v]);
  c[v] = x;
  upd(tin[v],val);
  upd(tout[v]+1,val);
}

const int M = (int)1e9 + 7;
typedef vector<ll> vl;
void FST(vl& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
      ll &u = a[j], &v = a[j + step]; tie(u, v) =
        // inv ? pii(v - u, u) : pii(v, u + v); // AND
        // inv ? pii(v, u - v) : pii(u + v, u); // OR /// include-line
         pii(u + v, u - v);                   // XOR /// include-line
        u%=M,v%=M;
        if(u<0)u+=M;
        if(v<0)v+=M;
    }
  }
  ll INV = exp(sz(a),M-2,M);
  assert((INV*sz(a)%M)==1);
   if (inv) trav(x, a) x = (x*INV)%M; // XOR only /// include-line
}
vl conv(vl a, vl b) {
  FST(a, 0); FST(b, 0);
  rep(i,0,sz(a)) a[i] = (1ll*a[i]*b[i])%M;
  FST(a, 1); return a;
}

int32_t main(){
  fastio;
  int m,C,n;
  cin >> m >> C >> n;
  rep(i,0,C){
    cin >> p[i];
  }

  rep(i,0,m){
    int x;
    cin >> x;
    rep(j,0,x){
      int a;
      cin>>a;
      deck[i]|=(1<<a);
    }
  }
  rep(i,0,n){
    cin >> c[i];
  }
  rep(i,0,n-1){
    int a,b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }

  dfs(0,0);
  rep(i,0,n){
    upd(tin[i],(1<<c[i]));
    upd(tout[i]+1,(1<<c[i]));
  }
  int cur=0;
  vl vals((1<<C),0);
  vl times((1<<C),0);
  rep(i,0,(1<<C))rep(j,0,C)if(i&(1<<j)){
    vals[i] = gcd(vals[i],p[j]);
    
  }
  vl cop = vals;
  
  rep(i,0,m)times[deck[i]]++;
  
  vl ans = conv(vals,times);
  
  vals = cop;
  rep(i,0,m){
    int u,v,w,y;
    cin >> u >> v >> w >> y;
    cur^=query(u,v);
    ll val=0;
    rep(i,0,m){
      val+=vals[cur^deck[i]];
    }
    update(w,y);
    cout << ans[cur]<<" ";
  }
  cout<<endl;
  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
