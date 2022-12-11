/**
  * Source: https://codeforces.com/blog/entry/105192
  * Tested on https://codeforces.com/problemsets/acmsguru/problem/99999/529
  * Complexity: O(NlogN \alpha (N))
  */

const int N = 50100;
int a[N],b[N],c[N];
int last[N];
// a,b 0-index
struct edge_interval{
  int l,r;
  int a,b,c;
};
struct dsu{
	vi p , ps;
	dsu(int n){
		p = vi(n+1),ps = vi(n+1,1);
		rep(i,0,n+1) p[i] = i;
	}
  void reset(int n){rep(i,0,n)p[i]=i,ps[i]=1;}
	int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
	bool join(int x , int y){
		x = find(x) , y = find(y);
		if(x == y) return 0;
		if(ps[x] > ps[y]) swap(x,y);
		p[x] = y, ps[y] += ps[x];
		return 1;
	}
};
int t;

ll ans[N];
int full_overlap(int l1,int r1,int l2,int r2){
  return l2<=l1 && r1<=r2;
}

int no_overlap(int l1,int r1,int l2,int r2){
  return r1 < l2 || l1 > r2;
}
int id[N];
void build(int l,int r,vector<edge_interval> edges,int n,ll cost){
  vector<edge_interval> nedges;
  for(auto &e : edges)if(!no_overlap(l,r,e.l,e.r))nedges.pb(e);
  edges = nedges;

  dsu d1(n),d2(n);
  // reduce number of vertices:
  for(auto e : edges){
    if(!full_overlap(l,r,e.l,e.r))d1.join(e.a,e.b);
  }
  for(auto e : edges)if(full_overlap(l,r,e.l,e.r)){
    if(d1.join(e.a,e.b)){
      d2.join(e.a,e.b);
      cost+=e.c;
    }
  }

  if(l==r){
    ans[l] = cost;
    return;
  }
  // reduce number of edges:
  int cnt=0;
  for(int i=0;i<n;i++)if(d2.find(i)==i)id[i] = cnt++;
  dsu d3(cnt);
  for(auto &e : edges){
    e.a = id[d2.find(e.a)],e.b = id[d2.find(e.b)];
    if(e.a==e.b || (full_overlap(l,r,e.l,e.r) && !d3.join(e.a,e.b))){
      e.l = N,e.r = -N;// useless edge
    }
  }
  int m = (l+r)/2;
  build(l,m,edges,cnt,cost);
  build(m+1,r,edges,cnt,cost);
}

int32_t main(){
  fastio;
  int n,m;
  cin >> n >> m;
  cin >> t;
  rep(i,0,m){
    cin >> a[i] >> b[i] >> c[i];
    --a[i],--b[i];
    last[i] = -1;
  }
  vector<edge_interval> edges;
  rep(i,1,t+1){
    int id,cc;
    cin >> id >> cc;
    id--;
    edges.push_back({last[id]+1,i-1,a[id],b[id],c[id]});
    c[id] = cc;
    last[id] = i-1;
  }
  rep(i,0,m){
    edges.pb({last[i]+1,t,a[i],b[i],c[i]});
  }
  sort(all(edges),[&](edge_interval a,edge_interval b){
    return a.c < b.c;
  });

  build(0,t,edges,n,0);

  for(int i=1;i<=t;i++)cout<<ans[i]<<endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
