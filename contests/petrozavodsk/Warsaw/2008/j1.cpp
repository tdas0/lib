#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define ms(v,x) memset(v,x,sizeof(v))
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define Unique(v) sort(all(v));v.erase(unique(all(v)),v.end());
#define sz(v) (int)v.size()
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
#define prl cerr<<"called: "<< __LINE__ << endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll a,ll b,ll m){
    if(b==0LL) return 1LL;
    if(b==1LL) return mod(a,m);
    ll k = mod(exp(a,b/2,m),m);
    if(b&1LL){
        return mod(a*mod(k*k,m),m);
    }
    else return mod(k*k,m);
}

struct SuffixArray {
  vi sa, lcp;
  SuffixArray(string& s, int lim=256) { // or basic_string<int>
    int n = sz(s) + 1, k = 0, a, b;
    vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
    sa = lcp = y, iota(all(sa), 0);
    for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
      p = j, iota(all(y), n - j);
      rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
      fill(all(ws), 0);
      rep(i,0,n) ws[x[i]]++;
      rep(i,1,lim) ws[i] += ws[i - 1];
      for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
        (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
    }
    rep(i,1,n) rank[sa[i]] = i;
    for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
      for (k && k--, j = sa[rank[i] - 1];
          s[i + k] == s[j + k]; k++);
  }
};

const int N = 1e6 + 10;
ll cnt[N];
ll sum[N];
int r[N];

int n,m;
#define DB 0

ll calc(vi pos){
  sort(all(pos));
  ll tot=0;
  if(DB){
  for(auto i : pos)cout << i << " ";
  cout << endl;
  

  }
  for(int i=0;i<sz(pos);i++){
    int p1 = pos[i],p2 = pos[(i + 1)%sz(pos)];
    if(p1 < p2){

      int mid = (p1 + p2)/2;
      tot+=(sum[mid] - sum[p1]) - (cnt[mid] - cnt[p1])*p1;
      tot+=(cnt[p2] - cnt[mid])*p2 - (sum[p2] - sum[mid]);
    }else{
      // pega o sufixo:
      // 1 ... p2 .... p1 ... m
      int x = min(m,(p1 + p2 + m)/2);
      // [p1,x] -> p1
      tot+=(sum[x] - sum[p1]) - (cnt[x] - cnt[p1])*p1;
      // sufixo pt2:
      if(x<m){
        // [x+1,m] + [1,p2]
        tot+=(cnt[m] - cnt[x])*p2 + (cnt[m] - cnt[x])*m - (sum[m] - sum[x]);
      }
      // prefixo:
      x = max(1,(p1 + p2 - m + 1)/2);
      // [x,p2] -> p2
      tot+=(cnt[p2] - cnt[x-1]) * p2 - (sum[p2] - sum[x-1]);
      // [1,x-1] -> p1 ,  [p1,m]:
      if(x!=1){
        tot+=(sum[x-1] - sum[0]) - (cnt[x-1] - cnt[0]) * 1;
        tot+=(cnt[x-1] - cnt[0]) * (m - p1 + 1);
      }
    }
  }

  if(DB)cout <<"saindo == "<<tot<<endl;

  return tot;
}

int32_t main(){
  fastio;
  string s;
  cin >> n >> m;
  cin >> s;
  string t = s + s;
  for(int i=1;i<=n;i++){
    cin >> r[i];
    r[i]++;
    cnt[r[i]]++;
    sum[r[i]]+=r[i];
  }
  for(int i=1;i<=m;i++){
    cnt[i]+=cnt[i-1];
    sum[i]+=sum[i-1];
  }
  SuffixArray sa(t);
  if(DB){

  for(int i=0;i<=sz(t);i++){
    cout << sa.sa[i]<<" "<<t.substr(sa.sa[i])<<" "<<sa.lcp[i] << endl;
  }

  }

  ll res=1e18;
  for(int i=0;i<sz(sa.lcp);){
    vi vec;
    if(sa.sa[i]+1<=m)vec.pb(sa.sa[i] + 1);
    i++;
    while(i < sz(sa.lcp) and sa.lcp[i] >= m){
      if(sa.sa[i] + 1<=m)vec.pb(sa.sa[i] + 1);
      i++;
    }

    if(sz(vec)>=1)res = min(res,calc(vec));

  }
  
  cout << res << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
