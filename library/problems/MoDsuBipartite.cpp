/* 
 * Problema: saber se usando as arestas de [l,r]
 * Grafo é bipartido
 * Source: https://codeforces.com/gym/100513/problem/A
*/ 

struct event{
  int a,b,sz;
  int pai;
  int ca;
  int good;
  event(){}
  event(int a,int b,int sz,int pai,int ca,int good):a(a),
  b(b),sz(sz),pai(pai),ca(ca),good(good){}
};
 
struct dsu_roolback{
  vi pai,sz;
  vi cor;// for this problem
  int good = 1;
  dsu_roolback(){}
  dsu_roolback(int _n){
    int n = _n + 100;
    pai.resize(n);
    sz.resize(n);
    cor.resize(n);
    rep(i,0,n){
      pai[i] = i;
      sz[i] = 1;
      cor[i] = 0;
    }
  }
 
  int F(int x){// no path-compression allowed
    while(x!=pai[x])x=pai[x];
    return x;
  }
  int Cor(int x){
    int c=0;
    while(x!=pai[x])c^=cor[x],x=pai[x];
    return c;
  }
 
  stack<event> Rool;
 
  void foto(int a,int b){
    Rool.push(event(a,b,sz[a],pai[a],cor[a],good));
  }
 
  void join(int a,int b){
	dbg(a,b);
    if(sz[F(a)] > sz[F(b)])swap(a,b);
    int ca = Cor(a),cb = Cor(b);
    a = F(a),b = F(b);
    foto(a,b);
    
    if(a!=b){
      sz[b]+=sz[a];
      pai[a] = b;
      cor[a] = (ca^cb^1);
    }
    else{
 
      if(ca == cb)good = 0;
 
    }
 
  }
  void roolback(int t){
    while((int)Rool.size() > t){
      event ev = Rool.top();Rool.pop();
      if(ev.a!=ev.b){
        sz[ev.b]-=ev.sz;
 
        pai[ev.a] = ev.pai;
        cor[ev.a] = ev.ca;
      }
      good = ev.good;
    }
  }
 
};
 
struct query{
	int l,r,id;
	query(int a,int b,int c){
		l=a,r=b,id=c;
	}
};
const int N = 100100;
const int SQ = 350;
int ans[N];
vector<query> here[N];
int x[N],y[N];
 
int32_t main(){
    fastio;
	int n,m,q;
	cin >> n >> m >> q;
 
	rep(i,0,m){
		cin >> x[i] >> y[i];
	}
 
	rep(i,0,q){
		int l,r;
		cin >> l >> r;
		l--,r--;
		here[l/SQ].pb(query(l,r,i));
	}
 
 
 
	for(int i=0;i<N;i++)if((here[i].size())){
		sort(all(here[i]),[&](query a,query b){
			return a.r < b.r;
		});
		dsu_roolback dsu(n);
		int l = i * SQ;
		int r = (i+1)*SQ;
		int RR = r;
		for(auto it : here[i]){
			while(r <= it.r){
				dsu.join(x[r],y[r]);
				r++;
			}
			int tam = dsu.Rool.size();
			for(int p=min(it.r,RR-1);p>=it.l;p--){
				dsu.join(x[p],y[p]);
			}
			ans[it.id] = dsu.good;
			dsu.roolback(tam);
		}
	}
 
	rep(i,0,q){
		cout << (ans[i] ? "Possible" : "Impossible") << endl;
	}
 
}
