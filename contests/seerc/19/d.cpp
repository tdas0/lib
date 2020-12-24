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

int cnt[30];

int32_t main(){
  fastio;
  string s;
  cin>>s;
    
  for(auto ch : s){
    cnt[ch - 'a']++;
  }
  int n = sz(s)/2;

  string t = "";
  if(n == 1){
    if(s[0] == s[1]){
      cout<<"NO"<<endl;
      return 0;
    }
    cout<<"YES"<<endl;
    cout<<s<<endl;
    return 0;
  }
  if(n == 2){
    sort(all(s));
    for(int i=0;i<30;i++){
      if(cnt[i]>=3){
        cout <<"NO"<<endl;
        return 0;
      }
    }
    cout << "YES"<<endl;
    cout << s << endl;
    return 0;
  }

  for(int j=0;j<30;j++){
    if(cnt[j]>=2*n-1){
      cout<<"NO"<<endl;
      return 0;
    }
    
    if(cnt[j] == 2*n - 2){

      for(int k=0;k<30;k++){
        if(k == j)continue;
        if(cnt[k] == 2){
          cout<<"NO"<<endl;
          return 0;
        }
      }
    }
    
  }

  int melhor = 0;
  for(int j=0;j<30;j++)if(cnt[j] > cnt[melhor])melhor = j;
  
  for(int i=0;i<n;i++){
    if(cnt[melhor] > 0){
    t+=char('a' + melhor);
    cnt[melhor]--;
    }
    else break;
  }
  for(int j=0;j<30;j++){
    if(cnt[j] > 0 and j!=melhor){
      t+=char('a' + j);
      cnt[j]--;
      break;
    }
  }
  while(cnt[melhor]){
    cnt[melhor]--;
    t+=char('a' + melhor);
  }
  for(int j=0;j<30;j++){
    while(cnt[j]){
      cnt[j]--;
      t+=char('a' + j);
    }
  }

  if(sz(t)!=sz(s)){
    assert(false);
  }
  cout <<"YES"<<endl;
  cout << t << endl;


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
