// upsolving
#include <bits/stdc++.h>
#define ld long double
//#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define ms(v,x) memmultiset(v,x,sizeof(v))
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define td(v) v.begin(),v.end()
#define sz(v) (int)v.size()
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
typedef long long ll;
typedef pair<int,int> pii;

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

int n;

int ask1(int id){
  assert(id>=1 and id<=n);
  cout <<1 <<" "<<id<<endl;
  cout.flush();
  int val;
  cin>>val;
  return val;
}
const int N = 255;
int a[N],b[N];
int M;
vi ask2(int l,int r){
  if(l == r)return vi();
  cout << 2<<" "<<r-l+1<<" ";
  for(int i=l;i<=r;i++)cout<<i<<" \n"[i==r];
  cout.flush();
  int tam = r-l+1;
  vi v(tam*(tam-1)/2);
  for(int i=0;i<sz(v);i++){
    cin >> v[i];
    M = max(M,v[i]);
  }
  return v;  
}
multiset<int> ask2(multiset<int> S){
  if(sz(S) == 1)return multiset<int>();
  cout << 2<<" "<<sz(S)<<" ";
  for(int x : S)cout<<x<<" ";
  cout<<endl;
  cout.flush();
  int tam = sz(S);
  multiset<int> v;
  for(int i=0;i<(tam*(tam-1)/2);i++){
    int x;
    cin>>x;
    v.insert(x);
    M = max(M,x);
  }
  return v;
}
int pos;

multiset<int> F(multiset<int> S){
  multiset<int> v1 = ask2(S);
  S.insert(pos);
  multiset<int> v2 = ask2(S);
  set<int> ans;
 
  for(auto it : v2)if(v1.count(it) != v2.count(it)){
    ans.insert(it);
  }
  multiset<int> sla;
  for(int x : ans)sla.insert(x);
  return sla;
}

struct Range{
  int l,r;
  multiset<int> B;
  multiset<int> ids;
  Range(){}
};
multiset<int> inter(multiset<int> A,multiset<int> B){
  multiset<int> r;
  for(auto it : A)if(B.count(it))r.insert(it);
  return r;
}
multiset<int> exclui(multiset<int> a,multiset<int> b){
  multiset<int> r;
  for(auto it : a)if(b.count(it) == 0)r.insert(it);
  return r;
}
void go(vector<Range> vec){
  vector<Range> vec2;

  for(auto it : vec){
    if(sz(it.ids) == 1){
      b[*it.ids.begin()] = *it.B.begin();
      continue;
    }
    vec2.pb(it);
  }
  vec = vec2;
  if(sz(vec) == 0){
    return;
  }
 // cout <<"gogo "<<sz(vec) << endl; 
  vector<Range> novo;
  for(auto it : vec){
    int tam = sz(it.ids);

    int put = tam/2;
    assert(put>=1);
    multiset<int> S1;
    while(put--){
      int id = *it.ids.begin();
      S1.insert(id);it.ids.erase(id);
    }
    multiset<int> S2;
    while(sz(it.ids)){
      int id = *it.ids.begin();
      S2.insert(id);it.ids.erase(id);
    }
    /*
    cout <<"split in ";
    for(int x : S1)cout<<x<<" ";
    cout<<" and in ";
    for(int x : S2)cout<<x<<" ";
    cout<<endl;  
    */
    Range r1,r2;
    r1.ids = S1,r2.ids = S2;

    novo.pb(r1);novo.pb(r2);
  }

  multiset<int> Query;
  multiset<int> ids;
  for(int i=0;i<sz(novo);i+=2){
    for(int id : novo[i].ids)ids.insert(id);
  }
  Query = F(ids);
  for(int i=0;i<sz(novo);i+=2){
    novo[i].B = inter(Query,vec[i/2].B);
    novo[i+1].B = exclui(vec[i/2].B,novo[i].B);
  }

  go(novo);
}

int32_t main(){
 // fastio;
  cin>>n;
  if(n<=4){
    for(int i=1;i<=n;i++){
      a[i] = ask1(i);
    }
    cout << 3 <<" ";
    for(int i=1;i<=n;i++)cout << a[i]<<" \n"[i==n];
    return 0;
  }
  ask2(1,n);
  
  int l = 2,r = n-1;
  int ans = n;
    int mx = M;

  while(l<=r){
    int mid = (l+r)/2;
    M=0;
    ask2(1,mid);
    if(M == mx){
      ans = mid;
      r = mid-1;
    }else l = mid + 1;
  }
  pos = ans;
  
  vector<Range> vec;
  Range ini;
  multiset<int> tudo;
  for(int i=1;i<=n;i++)if(i!=pos)tudo.insert(i);
  ini.B = F(tudo);
  
  ini.ids = tudo;
  vec.pb(ini);

  go(vec);
  a[pos] = ask1(pos);
  int pos2=0;
  for(int i=1;i<=n;i++){
    if(i!=pos){
      if(b[i] == mx){
        a[i] = ask1(i);
        pos2=i;
        break;
      }
    }
  }
  for(int i=1;i<=n;i++){
    if(i == pos || i == pos2)continue;
    if(a[pos] < a[pos2]){
      a[i] = b[i] + a[pos];
    }else a[i] = a[pos] - b[i];
  }
  cout << 3 <<" ";
  for(int i=1;i<=n;i++)cout<<a[i]<<" \n"[i==n];
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
