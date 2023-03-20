/*
Your task is to add new flights so that it will be possible to travel from any city to any other city.
What is the minimum number of new flights required?
*/
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
 
  vector<vi> DAG(){ // sem arestas repetidas
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
  int repre(int c){// representante da componente c (c < ncomps):
    return comps[c][0];
  }
};
 
int dfs(int v,vector<vi>& g,vi& vis){
  vis[v]=1;
  if(sz(g[v])==0)return v;
  for(int x : g[v])if(!vis[x]){
    int r = dfs(x,g,vis);
    if(r!=-1)return r;
  }
  return -1;
}
vector<vi> g;
 
int32_t main(){
  fastio;
  int n,m;
  cin>>n>>m;
  g.resize(n + 1);
  rep(i,0,m){
    int a,b;
    cin>>a>>b;
    g[a].pb(b);
  }
  SCC scc(g,n);
  scc.scc();
  vector<vi> dag = scc.DAG();
  int k = scc.ncomps;
  if(k == 1){
    cout << 0 << endl;
    return 0;
  }
  vi vis(k + 1,0),in(k+1,0),out(k+1,0),used(k+1,0);
  rep(i,0,k){
    for(auto it : dag[i]){
      in[it]++;
      out[i]++;
    }
  }
 
  vi source,sink;
  vector<pii> res;
  rep(i,0,k)if(in[i]==0){
    int algum = dfs(i,dag,vis);
    if(algum!=-1){
      used[i]=used[algum]=1;
      source.pb(i);
      sink.pb(algum);
    }
  }
 
  for(int i=0;i<sz(sink);i++){
    res.pb(pii(sink[i],source[(i+1)%sz(sink)]));
  }
  vi s,t;
  rep(i,0,k)if(!used[i]){
    if(in[i]==0)s.pb(i);
    if(out[i]==0)t.pb(i);
 
  }
  int mn = min(sz(s),sz(t));
  while(mn--){
    res.pb(pii(t.back(),s.back()));
    s.pop_back();
    t.pop_back();
  }
 
  while(sz(t)){
    res.pb(pii(t.back(),source[0]));
    t.pop_back();
  }
  while(sz(s)){
    res.pb(pii(sink[0],s.back()));
    s.pop_back();
  }
  cout << sz(res) << endl;
  for(auto it : res){
    cout << scc.repre(it.ff)<<" "<<scc.repre(it.ss)<<endl;
  }
}