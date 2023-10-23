#include <bits/stdc++.h>
#define pb push_back
#define sz(v) ((int)v.size())
#define ff first
#define ss second

using namespace std;
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define all(X) begin(X), end(X)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


const int N = 100100, MAXL = 20;
vi g[N];
int foi[N], Sz[N];

int pai[N];
int dist[N][MAXL];

void dfs_sz(int v,int p=-1){
  Sz[v] = 1;
  for(auto to : g[v])if(to!=p && !foi[to]){
    dfs_sz(to,v);
    Sz[v] += Sz[to];
  }
}
int dfs_find(int v,int tot,int p =-1){
  for(auto to : g[v])if(to != p && !foi[to]){
    if(Sz[to] > tot - Sz[to])return dfs_find(to,tot,v);
  }
  return v;
}

void dfs_dist(int v,int p,int l,int d){
  dist[v][l] = d;
  for(auto to : g[v])if(to !=p && !foi[to]){
    dfs_dist(to,v,l,d+1);
  }
}
int H[N];

void decomp(int v,int p,int level){
  dfs_sz(v,p);
  int root = dfs_find(v,Sz[v],-1);
  foi[root] = 1;
  H[root] = level;
  pai[root] = p;
  dfs_dist(root,-1,level,0);
  for(auto to : g[root])if(!foi[to]){
    decomp(to,root,level + 1);
  }
}

pii mn[N][MAXL];

void add(int v){
  int l = H[v];
  int iniv = v;
  while( l >= 0){
    mn[v][l] = min(mn[v][l], pii(dist[iniv][l], iniv));
    v = pai[v];
    l--;
  }
}
int query(int v){
  pii best = pii(N,v);
  int iniv = v;
  int l = H[v];
  while(v!=-1){
    int curd = dist[iniv][l];
    pii cur = pii(curd + mn[v][l].ff,mn[v][l].ss);
    best = min(best, cur);
    l--,v = pai[v];
  }
  return best.ss;
}

int ans[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    for(int i=1;i<n;i++){
      int a,b;
      cin >> a >> b;
      g[a].pb(b), g[b].pb(a);
    }
    rep(i,0,N)rep(j,0,MAXL){
      mn[i][j] = pii(N,N);
    }
    decomp(1,-1,0);
    
    for(int i=n;i>=1;i--){
      ans[i] = query(i);
      add(i);
    }
    rep(i,1,n+1)cout << ans[i] <<" ";
    cout << endl;
}
