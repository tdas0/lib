#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
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
#define sz(v) ((int)v.size())
//#define int long long  
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}
const int N = 2e5 + 100;
int c[N];
int p[N];
int ID=0;
int sum[N];
int solve(int k,int P){
  if(k&1){
    int cur = ++ID;
    p[cur] = P;
    k--;
    if(k == 0){
      sum[cur] = 1;
      c[cur] = 1;
      return cur;
    }
    int A = ++ID;
    int B = ++ID;
    sum[cur] = 1;
    c[A] = c[B] = 1;
    p[A] = cur;
    p[B] = A;

    int fi = solve(k/2,cur);
    sum[cur]+=sum[fi];
    c[cur] = sum[cur];
    return cur;
  }else{
    
    int cur = ++ID;
    c[cur] = 1e9;
    p[cur] = P;
    sum[cur]=0;

    int A = ++ID;
    int B = ++ID;
    sum[cur] = 1;
    c[A] = c[B] = 1;
    p[A] = cur;
    p[B] = A;

    int fi = solve(k/2,cur);
    sum[cur]+=sum[fi];

    return cur;
  }
}
int32_t main(){
  fastio;
  int k;
  cin >> k;
  if(k == 1){
    cout << 2 << endl;
    cout << 1 << endl;
    cout << 2 <<" "<<1<<endl;
    return 0;
  }
  solve(k,-1);
  cout << ID << endl;
  int n = ID;
  
  for(int i=2;i<=ID;i++)cout << p[i]<<" \n"[i==ID];
 
  for(int i=1;i<=ID;i++)cout << c[i]<<" \n"[i==ID];
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
