/* 
* Description: Computa isomorfismo de duas arvores rooteadas
* Complexity: O(n)
* Author: Tiago
* Status: tested on CSES
* Para arvores sem raiz, enraize em cada centroid
* Duas arvores rooteadas são iguais se elas retornam o mesmo valor para a mesma seed e mod
*/

template <class T>
class tree_isomorphism{
public:
	tree_isomorphism(int _n , T _mod , long long seed){
		n = _n , mod = _mod , rng = mt19937(seed);
		g = vector< vector<int> >(n+1) , depth = vector<T>(n+1);
		for(int i = 0 ; i <= n ; i ++)
			depth[i] = rng();
	}
	tree_isomorphism() = default;
	void addEdge(int u , int v){
		g[u].push_back(v);
		g[v].push_back(u);
	}
	T dfs(int root , int pai = -1 , int height = 0){
		T ans = 1;
		for(auto w : g[root]){
			if(w == pai)
				continue;
			ans = (ans * (depth[height] + dfs(w,root,height+1)))%mod;
		}
		return ans;
	}
private:
	int n;
	T mod;
	vector<T> depth;
	vector< vector<int> > g;
	mt19937 rng;
};
