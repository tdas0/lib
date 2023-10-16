/**
 * Author: Naim e tdas
 * Description: Edge Cover. Requires to use fast kuhn beforehand
 * Returns the set of edges such that every vertex of the graph
 * the graph is incident to at least one edge of the set
 * size = # not isolated vertices - maximum matching
 * Status: tested
 * Time: O(VE) but pretty fast actually. random shuffle?
 */


vector<pii> bipartiteEdgeCover(){
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