/* Source: weakest_topology,benq codes on "pick your own nim"
 * tested on "Pick your own nim" https://codeforces.com/gym/102156/problem/D
 * Complexity: O(N^2 * R * (C1 + C2)), N = size of ground set,R = rank of intersection,
 * C1 e C2 custos dos oráculos (abaixo C1 == 1 , C2 = 62)
 */
struct Matroid{
	const int n;
	Matroid(int n):n(n){}
	virtual bool oracle(int x) const = 0; // inserir indice X
	virtual bool oracle(int x,int y) const = 0; // (insere,remove)
	virtual void insert(int x) = 0;
	virtual void prepare(const vector<bool>&A) = 0;
};

struct ColorFullMatroid : public Matroid{
	vi cor,cnt;
	ColorFullMatroid(const vi& cores):Matroid(sz(cores)),cor(cores),cnt(vi(n,0)){}
	bool oracle(int x)const override{
		return !cnt[cor[x]];
	}
	bool oracle(int x,int y) const override{
		return !cnt[cor[x]] || cor[x] == cor[y];
	}
	void insert(int x) override{
		cnt[cor[x]]++;
	}
	void prepare(const vector<bool>&A){
		fill(all(cnt),0);
		rep(i,0,n)if(A[i])insert(i);
	}
};
const int MAXL = 62; // se maior usar bitset
struct gaussXOR{
		ll basis[MAXL];
		gaussXOR(){
		   rep(i,0,MAXL)basis[i]=0;
		}
		  
		bool can(ll x) const{
		   for(int i = MAXL-1;i>=0;i--){
		     x = min(x,x^basis[i]);
		   }
		   return x==0;
		}

		void insert(ll val){
		  for(int i=MAXL-1;i>=0;i--){
		    if(!(val&(1LL<<i)))continue;
		    if(!basis[i]){
		        basis[i] = val;
		        return;
		      }
		      val^=basis[i];
		   }
	  }
 };
struct LinearMatroid : public Matroid {


  gaussXOR base,base_sem[MAXL];
  vector<ll> val;
  vi id;
  LinearMatroid(vector<ll>& v):Matroid(sz(v)),val(v),id(vi(n,-1)){}
  bool oracle(int x)const override{
  	return !base.can(val[x]);
  }
  bool oracle(int x,int y)const override{
  	return !base_sem[id[y]].can(val[x]);
  }
  void insert(int x)override{
  	base.insert(val[x]);
  }
  void prepare(const vector<bool>&A)override{
  	base = gaussXOR();
  	rep(i,0,MAXL)base_sem[i] = gaussXOR();
  	fill(all(id),-1);
  	int cur=0;
  	rep(i,0,n){
  		if(A[i]){
  			base.insert(val[i]);
  			id[i] = cur++;
  			rep(j,0,n)if(i!=j and A[j])base_sem[id[i]].insert(val[j]);
  		}
  	}
  }

};

vector<bool> matroidInsersection(Matroid& M1,Matroid& M2){ // 0 -index
	int n = M1.n;
	assert(M1.n == M2.n);
	vector<bool> A(n,0),B(n,0);
	
	while(1){
		M1.prepare(A);
		M2.prepare(A);
		vi pai(n,0);
		vi S[2];
		rep(i,0,n){
			if(M1.oracle(i) and M2.oracle(i)){
				A[i] = 1;
				M1.prepare(A);
				M2.prepare(A);
			}
			S[A[i]].pb(i);
		}

		queue<int> q;
		trav(i,S[0])if(M1.oracle(i)){
			pai[i] = -1;
			q.push(i);
		}
		int lst = -1;

		while(!q.empty()){
			int cur = q.front();
			q.pop();
			if(A[cur]){
				trav(to,S[0])if(!pai[to] and M1.oracle(to,cur)){
					pai[to] = cur;
					q.push(to);
				}
			}else{
				if(M2.oracle(cur)){
					lst = cur;
					break;
				}
				trav(to,S[1])if(!pai[to] and M2.oracle(cur,to)){
					pai[to] = cur;
					q.push(to);
				}
			}
		}
		if(lst ==- 1)break;
		for(int v =lst;v!=-1;v=pai[v])A[v] = !A[v];
	}
	return A;
}

// usage
ColorFullMatroid M1(cor);
LinearMatroid M2(val);
auto A = matroidInsersection(M1,M2);
