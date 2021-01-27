/*
* Author: Tiago
* Ta um caralho esse código, mas parece rápido, codar um swap nas matroides (oraculo de exchange)
* testado em https://open.kattis.com/problems/rainbowgraph
*/

template <class M1, class M2>
pair<vi , vi> solve_matroid_intersection(M1&& m1, M2&& m2, int n , vi cost){
	vector<bool> iset(n+5 , false);
	vi ind_set , ans(n+1, (int) 1e9);
	int sum = 0 , tam = n;
	for(int i = 0 ; i < sz(cost); i ++)
		sum += cost[i];
	ans[tam] = min(ans[tam] , sum);
	while (1) {
		vi dist(n + 2, (int) 1e9);
		vector<array<int,3>> edges;
		vi p(n+2 , -1);
		for(int i = 0 ; i < n; i ++){
			if(iset[i]){
				for(int j = 0 ; j < n; j ++){
					if(!iset[j]){
						if(m1.swap(i,j))
							edges.push_back({i,j,cost[i]});
						if(m2.swap(i,j))
							edges.push_back({j,i,-cost[j]});
					}
				}
			}
			else{
				if(m1.check(i))
					edges.push_back({n,i,0});
				if(m2.check(i))
					edges.push_back({i,n+1,-cost[i]});
			}
		}
		dist[n] = 0;
		while(1){
			bool can = false;
			for(int i = 0 ; i < sz(edges) ; i ++){
				if(dist[edges[i][0]] < (int) 1e9){
					if(dist[edges[i][1]] > dist[edges[i][0]] + edges[i][2]){
						dist[edges[i][1]] = dist[edges[i][0]] + edges[i][2];
						p[edges[i][1]] = edges[i][0];
						can = true;
					}
				}
			}
			if(!can)
				break;
		}
		if(p[n+1] == -1)
			break;
		tam --;
		sum += dist[n+1];
		ans[tam] = min(ans[tam] , sum);
		int cur = n+1;
		while(cur != -1){
			if(cur < n)
				iset[cur] = iset[cur]^1;
			cur = p[cur];
		}
		m1.clear();
		m2.clear();
		ind_set.clear();
		rep(i,0,n)
			if(iset[i])
				m1.add(i) , m2.add(i) , ind_set.push_back(i);
	}
	return {ans, ind_set};
}
