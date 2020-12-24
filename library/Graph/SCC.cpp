/**
 * Author: Tiago
 * Date: 2020-04-28
 * Description: Computa a SCC, comp[x] diz a componente que o nó x está, comps são as componentes
 * O(n)
 * Usage: SCC(lista de adjacencia, tamanho) (lista é 1 indice)
 * grafo indexado no 1
 * DAG retorna o dag SEM ARESTAS REPETIDAS
 * Status: tested on https://cses.fi/problemset/task/1685/ and more
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
  
  vector<vi> DAG(){// sem arestas repetidas
    vector<vi> dag(n+1);val.assign(n+1,-1);

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
