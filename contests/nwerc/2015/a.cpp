#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
struct event{
  bool t;
  int x;
};
int32_t main(){
  int n , m;
  scanf("%d%d" , &n , &m);
  vector<event> v;
  rep(i,0,n){
    int a , s;
    scanf("%d%d" , &a , &s);
    v.push_back({0,a});
    v.push_back({1,s+a});
  }
  sort(all(v),[&](event a , event b){
    if(a.x == b.x)
      return a.t > b.t;
    return a.x < b.x;
  });
  priority_queue<int, vector<int> , greater<int> > pq;
  int ans = 0;
  for(auto w : v){
    while(sz(pq) && (w.x - pq.top()) > m)
      pq.pop();
    if(w.t == 0){
      if(sz(pq)){
        pq.pop();
      }
      else
        ans++;
    }
    else{
      pq.push(w.x);
    }
  }
  printf("%d\n" , n - ans);
}
