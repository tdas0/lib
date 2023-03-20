/**
 * Author: Naim e tdas
 * Description: fast kuhn + alguns covers
 * Time: O(VE) but pretty fast actually. random shuffle?
 */

struct bipartiteMatch{ // 1 indice
  int n , m;
  vector<vi> g; vi vis , match;
  int ans=0;
  bipartiteMatch(int n , int m) : n(n) , m(m), vis(n+m+2) , match(n+m+2) , g(n+m+2){}
  void add(int x,int y){
    g[x].pb(y + n);
    g[y + n].pb(x);
  }
  bool dfs(int x){
    allin(w,g[x]){
      if(vis[w]) continue;
      vis[w] = true;
      if(match[w] == 0 || dfs(match[w])){
        match[w] = x, match[x] = w; 
        return true;
      }
    }
    return false;
  }
  int solve(){
     bool haspath;
    do{
      haspath = false;
      fill(all(vis) , false);
      for(int i = 1 ; i<= n + m; i ++){
        if(!match[i] && dfs(i)) haspath = 1 , ans ++ ;
      }
    } while(haspath);
    return ans;
  }
  void dfs2(int v){
    vis[v] = 1;
    for(auto w : g[v]){
      if(vis[w])continue;
      if(v<=n){
          if(match[w]!=v)dfs2(w);
      }else{
        if(match[v]==w)dfs2(w);
      }
    }
  }
  // a vertex cover of a graph is a set of vertices that 
  // includes at least one endpoint of every edge of the graph.
  vector<int> vertexCover(){ // size == maximum matching
    solve();
    vector<int> res;
    fill(all(vis),false);
    for(int i=1;i<=n;i++){
      if(match[i]==0){
        dfs2(i);
      }
    }
    for(int i=1;i<=n;i++){
      if(match[i]!=0 and !vis[i]){
        res.pb(i);
      }
    }
    for(int i=n+1;i<=n+m;i++){
      if(vis[i]){
        res.pb(i);// change the index if needed
      }
    }
    assert(sz(res)==solve());
    return res;
  }
  vector<int> independentSet(){
    // todos menos os no vertexCover
  }
  // set of edges such that every vertex of
  // the graph is incident to at least one edge of the set.
  vector<pii> edgeCover(){ // size == # not isolated vertices - maximum matching
    solve();
    vi aux = match;
    vector<pii> res;
    rep(i,1,n+1){
      if(aux[i]){
          for(auto w : g[i]){
              if(aux[w]==i)res.pb(pii(i,w));
              else if(aux[w]==0)res.pb(pii(i,w)),aux[w]=-1;
          }
      }
    }
    rep(i,n+1,n+m+1){
      if(aux[i]){
        for(auto w : g[i]){
          if(!aux[w])res.pb(pii(w,i)),aux[w]=1;
        }
      }
    }
    return res;
  }
};
