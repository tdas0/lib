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

#include<bits/extc++.h>


template <typename flow_t = int, typename cost_t = long long>
struct MCMF_SSPA {
  int N;
  std::vector<std::vector<int>> adj;
  struct edge_t {
    int dest;
    flow_t cap;
    cost_t cost;
  };
  std::vector<edge_t> edges;

  std::vector<char> seen;
  std::vector<cost_t> pi;
  std::vector<int> prv;

  explicit MCMF_SSPA(int N_) : N(N_), adj(N), pi(N, 0), prv(N) {}

  void addEdge(int from, int to, flow_t cap, cost_t cost) {
    assert(cap >= 0);
    int e = int(edges.size());
    assert(max(to,from)<N);
    edges.emplace_back(edge_t{to, cap, cost});
    edges.emplace_back(edge_t{from, 0, -cost});
    adj[from].push_back(e);
    adj[to].push_back(e+1);
  }

  const cost_t INF_COST = std::numeric_limits<cost_t>::max() / 4;
  const flow_t INF_FLOW = std::numeric_limits<flow_t>::max() / 4;
  std::vector<cost_t> dist;
  __gnu_pbds::priority_queue<std::pair<cost_t, int>> q;
  std::vector<typename decltype(q)::point_iterator> its;
  void path(int s) {
    dist.assign(N, INF_COST);
    dist[s] = 0;

    its.assign(N, q.end());
    its[s] = q.push({0, s});
    while (!q.empty()) {
      int i = q.top().second; q.pop();
      cost_t d = dist[i];
      for (int e : adj[i]) {
        if (edges[e].cap) {
          int j = edges[e].dest;
          cost_t nd = d + edges[e].cost;
          if (nd < dist[j]) {
            dist[j] = nd;
            prv[j] = e;
            if (its[j] == q.end()) {
              its[j] = q.push({-(dist[j] - pi[j]), j});
            } else {
              q.modify(its[j], {-(dist[j] - pi[j]), j});
            }
          }
        }
      }
    }

    swap(pi, dist);
  }

  std::pair<flow_t, cost_t> maxflow(int s, int t) {
    assert(s != t);
    flow_t totFlow = 0; cost_t totCost = 0;
    while (path(s), pi[t] < INF_COST) {
      flow_t curFlow = std::numeric_limits<flow_t>::max();
      for (int cur = t; cur != s; ) {
        int e = prv[cur];
        int nxt = edges[e^1].dest;
        curFlow = std::min(curFlow, edges[e].cap);
        cur = nxt;
      }
      totFlow += curFlow;
      totCost += pi[t] * curFlow;
      for (int cur = t; cur != s; ) {
        int e = prv[cur];
        int nxt = edges[e^1].dest;
        edges[e].cap -= curFlow;
        edges[e^1].cap += curFlow;
        cur = nxt;
      }
    }
    return {totFlow, totCost};
  }
};

const int N = 500500;
int a[N],b[N];
ll c[N];
vector<pll> g[N];
ll pi[N];
int32_t main(){
  fastio;
  int n;
  cin >> n;
  vi cmp;
  for(int i=1;i<=n;i++){
    cin >> a[i] >> b[i] >> c[i];
    cmp.pb(a[i]);
    cmp.pb(b[i]);
  }
  Unique(cmp);
  MCMF_SSPA<int,ll> mcmf(sz(cmp) + 10);
  
  for(int i=1;i<=n;i++){
    a[i] = lower_bound(all(cmp),a[i]) - cmp.begin()+1;
    b[i] = lower_bound(all(cmp),b[i]) - cmp.begin()+1;
    mcmf.addEdge(a[i]-1,b[i],1,-c[i]);
    g[a[i]-1].pb(pll(b[i],-c[i]));
  }
  for(int i=0;i<sz(cmp);i++){
    mcmf.addEdge(i,i+1,2,0);
  }
  int s = sz(cmp)+1;
  mcmf.addEdge(s,0,2,0);

  rep(i,0,N)pi[i] = 0;
  pi[0]=0;
  pi[s]=0;
  rep(i,0,sz(cmp) + 1){
    for(auto to : g[i]){
      pi[to.ff]=min(pi[to.ff],pi[i] + to.ss);
    }
    pi[i+1] = min(pi[i+1],pi[i]);
  }

  rep(i,0,sz(cmp)+10)
    mcmf.pi[i]=pi[i];

  auto res = mcmf.maxflow(s,sz(cmp));
  cout << -res.ss << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
