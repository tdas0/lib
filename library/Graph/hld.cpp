/**
 * Author: Tiago Domingos
 * Date: 2020-02-21
 * Description: HLD interface
 * Time: O(nlog^2) 
 * Usage: decompose(root) cria a HLD com os preferred-path  da raiz root
 * update_subtree aplica v na subarvore (mudar seg pra mudar a aplicação)
 * update_path se c== 0 atualiza as arestas, se c == 1 atualiza os nós do path
 * query_path se c== 0 da query nas arestas, se c== 1 query nos paths do nó
 * Status:tested (not heavily)
 */


template<class T>
class HLD{
public:
	lazy_seg<T> seg;
	HLD(int n): Sz(n+1) , Hd(n+1) , p(n+1, -1) , g(n+1) , out(n+1) , in(n+1) , n(n){
		seg = lazy_seg<T>(n);
		seg.build(0 , n-1 , 1);
	}
	void add_edge(int x , int y){
		g[x].push_back(y);
		g[y].push_back(x);
		edges ++ ;
		assert(edges < n);
	}
	void dfs_sz(int x , int par = -1){
		Sz[x] = 1;
		trav(w, g[x]){
			if(w == par) continue;
			dfs_sz(w,x);
			Sz[x] += Sz[w];
			if(Sz[w] > Sz[g[x][0]] || g[x][0] == par) swap(w, g[x][0]);
		}
	}
	void dfs_dec(int x , int par = -1){ 
		in[x] = tin++;
		allin(w, g[x]){
			if(w == par) continue;
			p[w] = x;
			Hd[w] = ((w == g[x][0]) ? Hd[x] : w);
			dfs_dec(w,x); 
		}
		out[x] = tin;
	}
	void decompose(int root){
		Hd[root] = root;
		dfs_sz(root);
		dfs_dec(root);
	}
	int lca(int x , int y){
		while(Hd[x] != Hd[y]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			y = p[Hd[y]];
		}
		return in[x] < in[y] ? x : y ;
	}
	void update_subtree(int x , T v){
		seg.upd(in[x] , out[x]-1 , v, 0 , n-1 , 1);
		return ;
	}
	void update_path(int x , int y , T v , bool c = 0){
		int u = lca(x,y);
		for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			seg.upd(in[Hd[y]] , in[y] ,v, 0 , n-1 , 1);
		}
		if(in[x] > in[y]) swap(x,y);
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]) seg.upd(in[u] + 1 - (c? 1: 0) , in[y] , v, 0, n-1 , 1);
		return ;
	}
	T query_path(int x , int y , bool c = 0){  
		int u = lca(x,y);
		T ans = - LLONG_MAX;
		for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			ans = max(ans , seg.qry(in[Hd[y]] , in[y] , 0, n-1, 1));
		}
		if(in[x] > in[y]) swap(x,y);
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]) ans = max(ans ,seg.qry(in[u] + 1 - (c ? 1 : 0) , in[y],  0 , n-1, 1)); 
		return ans;
	}
	T query_subtree(int x){
		return seg.qry(in[x] , out[x]-1 , 0, n-1, 1);
	}

private:
	vector < vi > g; 
	vi Sz , Hd , in , out ,p ; 
	int n , edges =0  , tin = 0;
};