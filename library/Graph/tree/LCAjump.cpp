/**
 * Description: Calculates least common ancestor in tree with verts 
 	* $0\ldots N-1$ and root $R$ using binary jumping. 
 * Time: O(N\log N) build, O(\log N) query
 * Memory: O(N\log N)
 * Source: USACO Camp, KACTL
 * Verification: *
 */
#define pb push_back

struct LCA {
	int N;
	 vector<vi> ans, adj; vi depth;

	void init(int _N) {  // 0 ou 1 indexado
		N = _N + 10;
		int d = 1; while ((1<<d) < N) d ++;
		ans.assign(d,vi(N)); adj.resize(N); depth.resize(N);
	}
	void gen(int R = 0) { ans[0][R] = R; dfs(R); }
	
	void addEdge(int x, int y) { adj[x].pb(y), adj[y].pb(x); }

	void dfs(int x = 0) {
		
		rep(i,1,sz(ans)) ans[i][x] = ans[i-1][ans[i-1][x]];

		for(int y : adj[x]) if (y != ans[0][x]) 
			depth[y] = depth[ans[0][y]=x]+1, dfs(y);
	}
	int jmp(int x, int d) {
		per(i,0,sz(ans)) if ((d>>i)&1) x = ans[i][x];
		return x; }
	int lca(int x, int y) {
		if (depth[x] < depth[y]) swap(x,y);
		x = jmp(x,depth[x]-depth[y]); if (x == y) return x;
		per(i,0,sz(ans)) {
			int X = ans[i][x], Y = ans[i][y];
			if (X != Y) x = X, y = Y;
		}
		return ans[0][x];
	}
	int dist(int x, int y) { // # edges on path
		return depth[x]+depth[y]-2*depth[lca(x,y)]; }
};
