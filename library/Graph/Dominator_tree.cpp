/* Author: Cara do blog ai
 * Descrição: Acha a dominator tree com raiz em Root, um nó tem na subarvore todos
 * Os caras tal que só dá pra chegar da raiz pra eles passando por mim
 * O mais importante é que a arvore é montada :)
 * Use:
 * !!! 1-index
 * Dominator::addEdge(a,b);
 * Dominator::get(n,root);
 * DFS:
 * for(auto to : Dominator::tree[v])//....
 * Status: Tested on codeforces and cses critical cities - https://cses.fi/paste/bd9ebff02db7215412f6fd/
 * Tested on https://judge.yosupo.jp/
 */
 // From https://codeforces.com/group/W2YvE0cOoh/contest/284785/problem/E

const int N = ; // maxN
namespace Dominator{
  vi g[N],tree[N],rg[N],bucket[N];
  int sdom[N],par[N],dom[N],dsu[N],label[N];
  int arr[N],rev[N],T=0;//1-Based directed graph input
  int Find(int u,int x=0){
    if(u==dsu[u])return x?-1:u;
    int v = Find(dsu[u],x+1);
    if(v<0)return u;
    if(sdom[label[dsu[u]]]<sdom[label[u]])
      label[u] = label[dsu[u]];
    dsu[u] = v;
    return x?v:label[u];
  }
  void Union(int u,int v){ //Add an edge u-->v
    dsu[v]=u;   //yup,its correct :)
  }
  void dfs0(int u){
    T++;arr[u]=T;rev[T]=u;
    label[T]=T;sdom[T]=T;dsu[T]=T;
    for(int i=0;i<sz(g[u]);i++){
      int w = g[u][i];
      if(!arr[w])dfs0(w),par[arr[w]]=arr[u];
      rg[arr[w]].pb(arr[u]);
    }
  }
  void reset(int n){
    for(int i=1;i<=n;i++){
      g[i].clear();rg[i].clear();tree[i].clear();arr[i]=0;
    }
    T=0;
  }
  void addEdge(int u,int v){
    g[u].pb(v);
  }
  //Build Dominator tree(in main)
  void get(int n,int root){
    dfs0(root);n=T;
    for(int i=n;i>=1;i--){
      for(int j=0;j<sz(rg[i]);j++)
        sdom[i] = min(sdom[i],sdom[Find(rg[i][j])]);
      if(i>1)bucket[sdom[i]].pb(i);
      for(int j=0;j<sz(bucket[i]);j++){
        int w = bucket[i][j],v = Find(w);
        if(sdom[v]==sdom[w])dom[w]=sdom[w];
        else dom[w] = v;
      }if(i>1)Union(par[i],i);
    }
    for(int i=2;i<=n;i++){
      if(dom[i]!=sdom[i])dom[i]=dom[dom[i]];
      tree[rev[i]].pb(rev[dom[i]]);
      tree[rev[dom[i]]].pb(rev[i]);
    }
   
  }//done :) 
}
