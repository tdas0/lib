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

struct SCC{
  vector< vi> g , comps;
  vi val, z, cont, comp;
  int Time =0, ncomps= 0 , n; 
  SCC(vector<vi> g, int n ):n(n) , g(g) , val(n+1,0), comp(n+1, -1) {}
  int dfs(int j){
    int low = val[j] = ++Time , x ; z.push_back(j);
    trav(e, g[j]) if(comp[e] < 0)
      low = min(low , val[e] ?: dfs(e));
    if(low == val[j]){
      do{
        x = z.back() ; z.pop_back();
        comp[x] = ncomps;
        cont.push_back(x);
      } while(x != j);
      comps.push_back(cont) , cont.clear();
      ncomps++;
    }
    return val[j] = low;
  }

  void scc(){
    val.assign(n+1,0); comp.assign(n+1,-1);
    Time = ncomps = 0 ;
    rep(i,1,n+1) if(comp[i] < 0 ) dfs(i);
  }
  
  vector<vi> DAG(){// sem arestas repetidas
    vector<vi> dag(n+1);
    val.assign(n+1,-1);

    for(int i=0;i<ncomps;i++){
      for(auto v : comps[i]){
        for(auto to : g[v]){
          if(val[to]==-1 && comp[to]!=i){
            val[to]=1;
            dag[i].pb(comp[to]);
          }
        }
      }
      for(auto v : comps[i])
        for(auto to : g[v])
          val[to]=-1;
    }
    return dag;
  }
  int repre(int c){
    // representante da componente c (c < ncomps):
    return comps[c][0];
  }
};
const int N = 2020;
int d[N][N];
vector<pll> vec[N];
ll dist[N];
pii sla[N][N];
int deg[N];
vector<pii> res;
int pai[N];
const ll inf = 1e18;
ll DJ(int s,int t){
  res.clear();
  rep(i,0,N)dist[i] = inf;
  dist[s] = 0;
  pai[s] = -1;
  priority_queue<pll,vector<pll>,greater<pll> > pq;
  pq.push(pll(dist[s],s));
  while(!pq.empty()){
    pll C = pq.top();pq.pop();
    if(dist[C.ss]!=C.ff)continue;
    int v = C.ss;
    for(auto it : vec[v]){
      if(dist[it.ff] > dist[v] + it.ss){
        pai[it.ff] = v;
        pq.push(pll(dist[it.ff] = dist[v] + it.ss,it.ff));
      }
    }
  }
  int cur = t;
  while(pai[cur]!=-1){
    if(sla[pai[cur]][cur]!=pii(-1,-1))
      res.pb(sla[pai[cur]][cur]);
    cur = pai[cur];
  }
  return dist[t];
}

void solve(){
  
  int n;
  cin >> n;
  vector<vi> g(n+1,vi());

  rep(i,1,n+1)rep(j,1,n+1){
    cin >> d[i][j];
    if(i!=j and d[i][j]==0)g[i].pb(j);
  }
  if(n == 2){
    cout<<"NO\n";return;
  }
  SCC scc(g,n);
  scc.scc();
  auto D = scc.DAG();

  int tam = scc.ncomps;
  rep(i,0,tam)vec[i].clear(),deg[i]=0;

  rep(i,0,tam){

    for(auto it : D[i]){
      ll cost = 2e9 + 7;
      pii best;
      for(int k1 : scc.comps[i]){
        for(int k2 : scc.comps[it]){
          if(cost > d[k2][k1]){
            best = pii(k2,k1);
            cost = d[k2][k1];
          }
        }
      }
      sla[i][it] = pii(-1,-1);
      vec[i].pb(pll(it,0));
      sla[it][i] = best;
      vec[it].pb(pll(i,cost));
      deg[i]++;
     }
  }
  cout << "YES"<<endl;
  res.clear();
  int s,t;
  queue<int> q;
  rep(i,0,tam)if(deg[i] == 0){
    q.push(i);
    s = i;
  }
  while(!q.empty()){
    int cur = q.front();q.pop();
    t=cur;
    for(auto it : vec[cur]){
      if((--deg[it.ff])==0)q.push(it.ff);
    }
  }

  ll tot = DJ(s,t);
  cout << sz(res) << " "<<tot<<endl;
  for(auto it : res)cout<<it.ff<<" "<<it.ss<<endl;
  
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
