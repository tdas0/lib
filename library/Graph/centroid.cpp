/* Compute the centroid of a tree
* Complexity: O(NlogN) * O(cost of querys)
* Author: common knowledge
* Status: tested on https://codeforces.com/contest/715/problem/C
* g[i] -> vizinhos de i
* del[i] -> se já foi deletado na decomposição
*/

template <class T>
class Centroid{
public:
	vector<vector<T> > dist;
	vector<vi> tree;
	vi pai;
	vi level;
	vector<vi> in; // problem G Dhaka
	vector< ST<pii> > op;
	int n;
	Centroid(int n , int LGMAX = 20){
		this->n = n;
		g = vector< vector<pair< int, T> > >(n+1, vector<pair<int, T>>());
		dist = vector< vector<T> > (n+1 , vector<T>(LGMAX , numeric_limits<T>::max()));
		tree = vector<vi> (n+1 , vi());
		level = del = sz = pai = vi(n+1);
		in = vector<vi>(n+1, vi());
		op = vector< ST<pii> >(n+1 , ST<pii>());
	}
	void initq(){
		for(int i = 1; i <= n; i ++){
			sort(all(in[i]));
			op[i] = ST<pii>(sz(in[i]));
			for(int j = 0 ; j < sz(in[i]) ; j ++){
				op[i].upd(j,{dist[in[i][j]][level[i]] , in[i][j]});
			}
		}
	}
	pii query(int c , pii range){
		pii cur = pii(INT_MAX, - 1);
		int u = c;
		while(u != -1){
			int a = dist[c][level[u]];
			int L = lower_bound(all(in[u]) , range.first)  - begin(in[u]), R = upper_bound(all(in[u]) , range.second) - begin(in[u]) - 1;
			if(L <= R){
				pii b = op[u].query(L,R);
				cur = min(cur , {b.first + a, b.second}) ; 
			}
			u = pai[u];
		}
		return cur;
	}
	int calc_sz(int v,int p=-1){
	  sz[v] = 1;
	  for(auto to : g[v])if(to.F!=p and !del[to.F]){
	    sz[v]+=calc_sz(to.F,v);
	  }
	  return sz[v];
	}
	int find_centroid(int v,int p,int tam){
	  for(auto to : g[v])if(to.F!=p and !del[to.F]){
	    if(sz[to.F]*2>tam)return find_centroid(to.F,v,tam);
	  }
	  return v;
	}
	void dfs(int v,int root,int lv = 0, int p=-1,T d = 0){
		dist[v][lv] = d;
		in[root].push_back(v);
		for(auto w : g[v]) if(w.first != p && !del[w.first]){
			dfs(w.first,root,lv,v,d+w.second);
		}
	}
	void decompose(int v , int p = -1 , int lv = 0){
	  int tam = calc_sz(v);
	  int cent = find_centroid(v,-1,tam); 
	  dfs(cent, cent, lv); // answer querys if needed
	  del[cent] = 1;
	  if(p != -1){
	  	tree[cent].push_back(p);
	  	tree[p].push_back(cent);
	  }
	  pai[cent] = p;
	  level[cent] = lv;
	  for(auto to : g[cent]){
	    if(del[to.F])continue;
	    decompose(to.F,cent,lv+1);
	  }
	}	
	void add_edge(int x , int y , T z){
		g[x].push_back({y,z});
		g[y].push_back({x,z});
	}

	void build(){
		decompose(1);
	}
private:
	vector<vector<pair<int, T>> > g;
	vi del, sz;
};
