// Solves CSES fixed-lenght paths
// finds all paths from size k1 to k2 (edges)
// Idea: Small to large, keeping at most the height of the tree
// Keep a prefix sum for each node
// Total complexity is O(N)

const int N = 200100;
vi g[N];
ll res=0;

ll sum(deque<int>& v,int x){
  if(x<0)return 0;
  return v[0] - (x+1<sz(v) ? v[x+1] : 0);
}

void merge(deque<int>& a,deque<int>& b){// |a| > |b|
  rep(i,0,sz(b))a[i] += b[i];
}


deque<int> solve(int v,int k1,int k2,int p=-1){

  deque<int> dq;
  dq.pb(1);
  for(int to : g[v])if(to!=p){
    auto b = solve(to,k1,k2,v);
    if(sz(b) > sz(dq))swap(b,dq);

    b.pb(0);
    for(int i=0;i<sz(b)-1;i++){
      res += (b[i] - b[i+1])*(ll)(sum(dq,k2-i) - sum(dq,k1-i-1));
    }
    b.pop_back();

    merge(dq,b);
  }
  dq.push_front(dq.front());
  return dq;
}


int32_t main()
{
  fastio;
  int n,k1,k2;
  cin >> n >> k1 >> k2;
  k2=k1;
  rep(i,1,n){
    int a,b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  solve(1,k1,k2);
  cout << res << endl;
}
