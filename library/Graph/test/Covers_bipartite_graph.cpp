// tested on cses and grupo da summer
// vertex cover also tested at https://codeforces.com/contest/1525/problem/F

struct bipartite_match{ // 1 indice
  int n , m;
  vector<vi> g; vi vis , match;
  int ans=0;
  bipartite_match(int n , int m) : n(n) , m(m), vis(n+m+2) , match(n+m+2) , g(n+m+2){}
 
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

  // status: tested
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
  vector<int> vertex_cover(){ // size == maximum matching
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
  // end of vertex cover
  // status: not tested
  vector<int> independent_set(){// size == all - maximum matching
    vi cover = vertex_cover();
    fill(all(vis),false);
    for(int x : cover)vis[x]=1;
    vi res;
    for(int i=1;i<=n+m;i++)if(!vis[i])res.pb(i);
    assert(sz(res) == n - solve());
    return res;
  }
  // an edge cover of a graph is a set of edges such that every vertex of
  // the graph is incident to at least one edge of the set.
  //status: tested:
  vector<pii> edge_cover(){ // size == number of not isolated vertices - maximum matching
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

  int matchL(int x){return (match[x] ? match[x] - n : 0);}
  int matchR(int x){return match[x+n];}
};
