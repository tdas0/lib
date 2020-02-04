class dsu{
public:
	void init(int n){
		pai.clear() , peso.clear() , rollback.clear();
		pai.resize(n+1) , peso.resize(n+1) , comp = n;
		for(int i = 0 ; i <= n; i ++){
			pai[i] = i , peso[i] = 1 ; 
		}
	}
	int fd(int x){
		return pai[x] == x ? x : fd(pai[x]) ; 
	}
	void snapshot(int u , int v){
		rollback.push_back({u , v , pai[v] , comp}) ; 
	}
	bool rb(){
		if(!rollback.size()) return 0;
		state u = rollback.back(); rollback.pop_back();
		if(u.u != u.v){
			peso[u.u] -= peso[u.v];
			pai[u.v] = u.paiv;
			comp = u.comp;
		}
		return 1;
	}
	void join(int u , int v){
		u = fd(u) , v = fd(v);
		if(peso[u] < peso[v]) swap(u,v);
		snapshot(u,v);
		if(u != v){
			pai[v] = u , peso[u] += peso[v] , comp -- ;
		}
	}
	int get_comp(){
		return comp;
	}
private:
	struct state{
		int u , v , paiv, comp;
	};
	vector<int> pai , peso; int comp ; vector<state> rollback;
};
