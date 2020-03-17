/**
 * Author: Tiago Domingos
 * Date: 2020-02-21
 * Description: Cria uma arvore isometrica com O(|K|) nós
 * Time: O(Klog(K))
 * Usage: mandar o conjunto de nós que a arvore tem que ter, e implementar uma função
 * lca(x,y) e dist(x,y)
 * Status:tested
 */



#include "graph.cpp"

pair<vector<edge> ,int> build_virtual_tree(vi K){
	auto f = [&](int a , int b){
		return in[a] < in[b];
	};
	sort(all(K) , f);
	int m = sz(K);
	rep(i,1,m){
		K.push_back(lca(K[i] , K[i+1]));
	}
	sort(all(K) , f);
	K.erase(unique(all(K)) , K.end());
	rep(i,0,sz(K) -1){
		int z = lca(K[i] , K[i+1]);
		e.push_back({K[i+1] , z ,dist(z,K[i+1])});
	}
	return {e ,K[0]};
}
