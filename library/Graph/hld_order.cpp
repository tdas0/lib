/**
 * Author: Tiago Domingos
 * Date: 2020-02-21
 * Description: HLD interface
 * Time: O(nlog^2) 
 * Usage: decompose(root) cria a HLD com os preferred-path  da raiz root
 * update_subtree aplica v na subarvore (mudar seg pra mudar a aplicação)
 * update_path se c== 0 atualiza as arestas, se c == 1 atualiza os nós do path
 * query_path se c== 0 da query nas arestas, se c== 1 query nos paths do nó
 * segments retorna na ordem de u->v as perguntas na seg, se l > r em algum range, então tem que perguntar em uma segtree que da merge na ordem reversa
 * Status:tested (not heavily)
 */


// #include "../data_structure/SegLazy.cpp"
template<class U = Node , class L = Lazy>
class HLD{
public:
	HLD(int n , U identity , L zero): Sz(n+1) , Hd(n+1) , p(n+1, -1) , g(n+1) , out(n+1) , in(n+1) , n(n){
		seg = SegmentTree<U,L>(n , identity , zero);
		vector<U> v(n , identity);
		seg.build(0,n-1,1,v);
		this->identity = identity;
		this->zero = zero;
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
	void update_subtree(int x , L v){
		seg.upd(in[x] , out[x]-1 , v, 0 , n-1 , 1);
		return ;
	}
	void update_path(int x , int y , L v , bool c = 0){
		int u = lca(x,y);
		for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			seg.upd(in[Hd[y]] , in[y] ,v, 0 , n-1 , 1);
		}
		if(in[x] > in[y]) swap(x,y);
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]) seg.upd(in[u] + 1 - (c? 1: 0) , in[y] , v, 0, n-1 , 1);
		return ;
	}
	vector< vpi >  segments(int x , int y , bool c = 0){ // segmentos que tenho que perguntar na segtree
		int u = lca(x,y);
		U ans = identity;
		bool cur = 1;
		vector<pair< int,int >  > paths[2];
		for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y) , cur ^= 1;
			pii range = {in[Hd[y]] , in[y]};
			paths[cur].push_back(cur ? range : pii(range.S,range.F));
		}
		if(in[x] > in[y]) swap(x,y) , cur ^= 1;
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]){ 
			pii range = {in[u] + 1 - (c ? 1 : 0) , in[y]};
			paths[cur].push_back(cur ? range : pii(range.S,range.F));
		}
		reverse(all(paths[1]));
		return {paths[0] , paths[1]};		
	}
	U query_path(int x , int y , bool c = 0){  // se a ordem nao importar
		int u = lca(x,y);
		U ans = identity;
		for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			ans =  ans + seg.query(in[Hd[y]] , in[y] , 0, n-1, 1);
		}
		if(in[x] > in[y]) swap(x,y);
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]){ 
			ans = ans + seg.query(in[u] + 1 - (c ? 1 : 0) , in[y],  0 , n-1, 1);
		}
		return ans;
	}
	U query_subtree(int x){
		return seg.query(in[x] , out[x]-1 , 0, n-1, 1);
	}

private:
	U identity;
	L zero;
	SegmentTree<U,L> seg;
	vector < vi > g; 
	vi Sz , Hd , in , out ,p ; 
	int n , edges =0  , tin = 0;
};	
