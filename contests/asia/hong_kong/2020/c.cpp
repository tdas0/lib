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

const int N = 400100;
// BIT
int tempo=0;
int vis[N];
int BIT[N];
int sum(int x){
  int r=0;
  while(x>0){
    if(vis[x]==tempo){
      r+=BIT[x];
    }
    x-=(x&-x);
  }
  return r;
}
void upd(int x,ll v){
  while(x<N){
    if(vis[x]!=tempo){
      vis[x]=tempo;
      BIT[x]=0;
    }
    BIT[x]+=v;
    x+=(x&-x);
  }
  return ;
}
// CENTROID:
vi g[N];
int del[N];
int sz[N];

ll a[N];
int calc_sz(int v,int p = -1){
  sz[v]=1;
  for(int to : g[v])if(to!=p and !del[to]){
    sz[v]+=calc_sz(to,v);
  }
  return sz[v];
}
int find_centroid(int v,int p ,int tam){
  for(int to : g[v])if(to!=p and !del[to]){
    if(sz[to]*2 > tam)return find_centroid(to,v,tam);
  }
  return v;
}

vector<pll> paths;

const int inf = 2e9 + 7;
ll res=0;
void dfs(int v,int p,ll mx,ll sum){
  sum+=a[v];
  mx = max(mx,a[v]);
  paths.pb(pll(mx,sum));
  for(int to : g[v])if(to!=p and !del[to]){
    dfs(to,v,mx,sum);
  }
}
typedef vector<ll> vl;
void compute_answer(int C){
  paths.clear();
  // all in:
  for(int to : g[C]){
    if(del[to])continue;
    dfs(to,C,a[C],0);
  }
  vl cmp;
  for(auto it : paths){
    cmp.pb(it.ss); // sum
    cmp.pb(it.ff*2ll - it.ss - a[C]); // 2*mx - sum
  }
  Unique(cmp);
  sort(all(paths));
  tempo++;
  int CNT=0;
  for(auto it : paths){
    ll need = 2ll*it.ff - it.ss - a[C];
    int id = upper_bound(all(cmp),need) - cmp.begin();
    res+=CNT - sum(id);
    int pos = upper_bound(all(cmp),it.ss) - cmp.begin();
    upd(pos,1);
    CNT++;
  }
  // resposta contando a centroid:
  for(auto it : paths){
    if(it.ff * 2 < it.ss + a[C])res++;
  }
  // double count:
  for(int to : g[C]){
    if(del[to])continue;
    paths.clear();

      dfs(to,C,a[C],0);

      vl cmp;
      for(auto it : paths){
        cmp.pb(it.ss);
        cmp.pb(it.ff*2 - it.ss - a[C]);
      }
      Unique(cmp);
      sort(all(paths));
      tempo++;
      int CNT=0;
      for(auto it : paths){
        ll need = 2*it.ff - it.ss - a[C];
        int id = upper_bound(all(cmp),need) - cmp.begin();
        res-=CNT - sum(id);
        int pos = upper_bound(all(cmp),it.ss) - cmp.begin();
        upd(pos,1);
        CNT++;
      }

  }

  return;
}

void decompose(int v){
  int tam = calc_sz(v);
  int cent = find_centroid(v,-1,tam);
  if(tam == 1)return;
  compute_answer(cent);
  del[cent]=1;
  for(int to : g[cent])if(!del[to]){
    decompose(to);
  }
}

void solve(){
  int n;
  cin >> n;
  for(int i=1;i<=n;i++){
    g[i].clear();
    cin >> a[i];
    del[i]=0;
  }
  for(int i=1;i<n;i++){
    int a,b;
    cin>>a>>b;
    g[a].pb(b);
    g[b].pb(a);
  }
  res=0;

  decompose(1);
  cout << res << endl;
}

int32_t main(){
  fastio;
  int t;
  cin >> t;
  while(t--){
    solve();
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
