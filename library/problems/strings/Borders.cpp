// calculate total number of borders of all its substrings

struct SuffixArray {
  //kactl
};
const int N = 400100;
struct RMQ{
  //benq
};

int rev[N];
 
ll pa(ll x){
  return 1ll*x*(x+1)/2;
}

int32_t main(){
  fastio;

  string s;
  cin>>s;

  int n = sz(s);
  SuffixArray sa(s);
  
  vi vec;
  for(int i=0;i<n+1;i++){
    vec.pb(sa.lcp[i]);
  //  cout <<i<<" "<< sa.lcp[i]<<" "<<s.substr(sa.sa[i],n-sa.sa[i])<<endl;
    rev[sa.sa[i]] = i;
  }

  RMQ rmq;
  rmq.build(vec);
  ll res = pa(n);
  for(int i=1;i<=n;i++){
    if(sa.lcp[i]){
      int l = i,r = n;
      int ans = i;
      while(l<=r){
        int mid = (l+r)>>1;
        if(rmq.query(i,mid) == sa.lcp[i]){
          ans = mid;
          l = mid + 1;
        }else r = mid - 1;
      }
      l = 0,r = i-1;
      int ans2 = i;
      while(l<=r){
        int mid = (l+r)>>1;
        if(rmq.query(mid,i-1) > sa.lcp[i]){
          ans2 = mid;
          r = mid - 1;
        }else l = mid + 1;
      }
  //    cout << i<<" "<<ans2<<" "<<ans << endl;
      res+=1ll*(ans - i + 1)*(i - ans2 + 1)*sa.lcp[i];
    }
  }

  cout << res << endl;
}
