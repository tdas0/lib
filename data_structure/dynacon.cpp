class dynacon{
public:
	struct query{
		int u , v, l , r ;
	};	
	void init(int n){
		T.init(n);
	}
	void add_edge(int u , int v , int l , int r){ // adiciona uma aresta que existe no tempo [l,r) conectando u a v
		q.push_back({u,v,l,r}); 
	}
	void d_c(int l , int r , const vector<query> &q ){
		int mid = (l+r)/2;
		if(l == r){
			ans[l] = (T.get_comp() );
			return ;
		}
		int torb = 0;
		vector<query> left , right;
		for(auto w : q){
			if(w.l <= l  && mid < w.r){
				T.join(w.u  , w.v);
				torb++;
			}
			else if(w.l <= mid){
				left.push_back(w);
			}
		}
		d_c(l, mid , left );
		left.clear();
		while(torb > 0){
			T.rb();
			torb--;
		}
		for(auto w : q){
			if(w.l <= mid+1 &&   r < w.r){
				T.join(w.u , w.v);
				torb++;
			}
			else if(w.r > mid){
				right.push_back(w);
			}
		}
		d_c(mid+1,r,right );
		while(torb > 0){
			T.rb();
			torb--;
		}
		right.clear();
	}
	void solve(int l , int r ){ // resolve pra o tempo [l,r] -> todo mundo em q ta contido em l,r
		ans.clear();
		ans.resize(r-l+1);
		d_c(l , r , q );
	}
	int get(int x){
		return ans[x];
	}
private: 
	vector< query> q;
	vector<int> ans;
	dsu T;
};
