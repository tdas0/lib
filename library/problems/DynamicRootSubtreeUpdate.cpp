/* coisas para uma arvore que pode mudar a raiz
 * LCA em O(1) 
 * Up -> cara subindo K arestas
 * init para iniciar as coisas e gen(root) para fazer dfs e tals
 * suporta adicionar em subarvores e em nós / fazer querys
 * !! IF USING WEIGHTS CREATE A SECOND ARRAY FOR THE HEIGHTS
 * Status: tested on https://codeforces.com/problemset/problem/916/E
 */
#include "RMQ.h"
#include "seg_lazy.h"

struct Tree{// deixa a raiz como 1 pf ;)
  int n;
  vector<vi> g;
  vi H,pos,tin,tout;
  vector<pii> temp;
  lazy_seg<ll> lazy;
  int T;
  int MY_ROOT = 1;
  vi ans[20];
  void init(int _n){
    T=0;
    n = _n;
    g.resize(n+1);
    H = pos = tin = tout = vi(n+1);
    rep(i,0,20)ans[i].resize(n+1);
  }
  RMQ<pii> rmq;
  void addEdge(int a,int b){
    g[a].pb(b);
    g[b].pb(a);
  }
  void dfs(int v,int p = -1){
    pos[v] = sz(temp);
    tin[v] = ++T;
    temp.pb(pii(H[v],v));
    trav(to,g[v])if(to!=p){
      if(DB)cout << v<<" -> "<<to<<endl;
      H[to] = H[v] + 1; // se for usar pesos cria uma outra altura. Mantem essa pro lca
      ans[0][to] = v;
      dfs(to,v);
      temp.pb(pii(H[v],v));
    }
    tout[v] = T;
  }
  void gen(int Root){
    MY_ROOT = Root;
    ans[0][Root] = Root;
    dfs(Root);
    rmq.init(temp);
    assert(T == n);
    lazy = lazy_seg<ll>(T+1);
    lazy.build(1,T,1);
    rep(j,1,20){
      rep(i,1,n+1){
        ans[j][i] = ans[j-1][ans[j-1][i]];
      }
    }
  }
  int lca(int a,int b){
    a = pos[a],b = pos[b];
    if(a > b)swap(a,b);
    return rmq.query(a,b).ss;
  }
  int dist(int a,int b){
    return H[a] + H[b] - 2*H[lca(a,b)];
  }
  
  
  int lca_root(int a,int b,int root){
    // retorna o lca com "root" sendo a nova raiz
    int Lca = lca(a,b);
    if(lca(Lca,root) == Lca){
      int op1 = lca(a,root);
      int op2 = lca(b,root);
      if(op1 == Lca)return op2;
      return op1;
    } 
    return Lca;
  }
  
  void update_node(int v,ll val){
    lazy.upd(tin[v],tin[v],val,1,T,1);
  }
  void update_subtree(int v,ll val){
    lazy.upd(tin[v],tout[v],val,1,T,1);
  }
  ll query_subtree(int v){
    return lazy.qry(tin[v],tout[v],1,T,1);
  }

  int up(int v,int k){
    for(int j=19;j>=0;j--){
      if(k&(1<<j))v = ans[j][v];
    }
    return v;
  }
  bool is_ans(int a,int b){
    return tin[a]<=tin[b] and tout[a]>=tout[b];
  }
  // update subtree of smallest tree that contains both a and b
  void update_subtree_root(int a,int b,int root,ll val){
    int Lca = lca(a,b),Lca2 = lca_root(a,b,root);
    if(!is_ans(Lca,root)){
      return void(update_subtree(Lca,val));
    }
    // update ALL THE TREE
    update_subtree(MY_ROOT,val);
    // minus some shit:
    if(Lca2 == root)return;
    int pivo = up(root,dist(root,Lca2)-1);
    update_subtree(pivo,-val);
  }
  ll query_subtree_root(int v,int root){ 
    if(v == root)return query_subtree(MY_ROOT);
    if(!is_ans(v,root))return query_subtree(v);
    return query_subtree(MY_ROOT) - query_subtree(up(root,dist(root,v)-1));
  }

};
