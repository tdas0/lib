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
typedef vector<ll> vl;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}
  
// debug:
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T){ 
  cerr << ' ' << H; 
  dbg_out(T...); 
}
#ifdef LOCAL
#define dbg(...) cerr<<"(" << #__VA_ARGS__<<"):" , dbg_out(__VA_ARGS__) , cerr << endl
#else
#define dbg(...) 42
#endif
//

const int N = 1e4 + 10;

vector<pii> G[N];
int dist[2][N][(1<<8)];

vi here[N][8];

struct posi{
  int no,msk,t;
  posi(int no,int msk,int t):no(no),msk(msk),t(t){}
  bool operator <(posi o) const{
    return t > o.t;
  }
};

int n,m,k;
const int inf = 1e9;
void calc(int id,int ini){
  priority_queue<posi> pq;
  rep(i,1,n+1)rep(j,0,(1<<k)){
    dist[id][i][j] = inf;
  }
  auto get = [&](int p,int msk){
    return posi(p,msk,dist[id][p][msk]);
  };
  auto go = [&](int v,int msk,int t){
    if(dist[id][v][msk] > t){
      dist[id][v][msk] = t;
      pq.push(get(v,msk));
    }
  };

  dist[id][ini][0] = 0;
  pq.push(get(ini,0));
  while(!pq.empty()){
    auto P = pq.top();pq.pop();
    int no = P.no;
    int msk = P.msk;
    int t = P.t;
    if(dist[id][no][msk]!=t)continue;

    // normal edges:
    for(auto tt : G[no]){
      int to = tt.ff,w=tt.ss;
      go(to,msk,w + t);
    }
    // get a sussy baka
    rep(j,0,k)if(!(msk>>j&1)){
      auto it = lower_bound(all(here[no][j]),t);
      if(it!=here[no][j].end()){
        go(no,msk|(1<<j),*it);
      }
    }
  }

}

void solve(){
  cin >> n >> m >> k;
  for(int i=1;i<=n;i++){
    G[i].clear();
    rep(j,0,k)here[i][j].clear();
  }
  rep(i,1,m+1){
     int a,b,c;
     cin >> a >> b >> c;
     G[a].pb(pii(b,c));
     G[b].pb(pii(a,c));
  }
  int e,tmax;
  cin >> e >> tmax;
  rep(i,0,e){
    int p,x,t;
    cin >> p >> x >> t;
    here[x][p-1].pb(t);
  }
  rep(i,1,n+1)rep(j,0,k)sort(all(here[i][j]));
  int x,y;
  cin >> x >> y;
  calc(0,x);
  calc(1,y);
  int res = tmax + 1;
  for(int msk=0;msk<(1<<k);msk++){
    int op1 = inf,op2 = inf;
    rep(i,1,n+1)op1 = min(op1,dist[0][i][msk]);
    int other = (1<<k)-1;other^=msk;
    rep(i,1,n+1)op2 = min(op2,dist[1][i][other]);
    res = min(res,max(op1,op2));
  }

  cout << (res > tmax ? -1 : res) << endl;
}

int32_t main(){
    fastio;
    int t;
    cin >> t;
    while(t--)
      solve();

    
    // math -> gcd it all
    // Did u check N=1? Did you switch N,M?
}
