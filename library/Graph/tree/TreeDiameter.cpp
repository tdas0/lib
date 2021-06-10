/**
 * Description: Calculates longest path in tree. The vertex furthest
 	* from 0 must be an endpoint of the diameter.
 * Source: Benq
 * Verification: 
   * http://www.spoj.com/problems/PT07Z/
   * https://codeforces.com/contest/1182/problem/D
 */

template<int SZ> struct TreeDiameter { // declarar global ou namespace
		
	// 0 INDEXADO !!!!

	int N, par[SZ];
	ll dist[SZ], diaLen;  
	vector<pii> adj[SZ];
	vi dia, center;
	void addEdge(int a, int b,int c = 1) {
		// se 1 indexado:
		// --a,--b;
	 adj[a].pb(pii(b,c)), adj[b].pb(pii(a,c)); 
	}
	void dfs(int x) {
		for(auto y : adj[x]) if (y.ff != par[x]) {
			par[y.ff] = x; dist[y.ff] = dist[x]+y.ss; 
			dfs(y.ff); }
	}
	void genDist(int x) { par[x] = -1; dist[x] = 0; dfs(x); }
	void init(int _N) {
		N = _N; dia = {0,0}; 
		
		genDist(0); rep(i,0,N) if (dist[i]>dist[dia[0]]) dia[0] = i; 
		
		genDist(dia[0]); rep(i,0,N) if (dist[i]>dist[dia[1]]) dia[1] = i;
		
		vector<int> path;
		int v = dia[1];
		while(v!=dia[0])path.pb(v),v=par[v];
		path.pb(dia[0]);
    return;
		cout << dist[dia[1]]<<" "<<sz(path)<<endl;
		for(auto it : path)cout << it<<" ";
		cout<<endl;
	}
};
