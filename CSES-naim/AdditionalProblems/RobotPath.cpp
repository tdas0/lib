//kienthesun
// robo para quando chega em ponto ja visitado
#include <bits/stdc++.h>
using namespace std; 
typedef long long LL;
 
struct pt {
  LL x , y ;
}; 
 
struct seg {
  pt p , q ; 
  seg() {}
} ; 
 
bool operator<(const seg &a , const seg &b){
  return a.p.y < b.p.y ;
}
 
bool intersect1d(LL l1 , LL r1, LL l2, LL r2){
  if (l1 > r1) swap(l1, r1) ; 
  if (l2  > r2) swap(l2, r2) ; 
  return max(l1, l2) <= min(r1, r2) ;
}
 
struct event {
  LL x ; 
  int k , id;
  event(LL x , int k, int id) : x(x) , k(k), id(id) {  } 
  bool operator<(const event &e) const {
    return x != e.x ? x < e.x : k < e.k ; 
  }
} ;
 
bool intersect(const seg &a,  const seg &b){
  return intersect1d(a.p.x , a.q.x, b.p.x, b.q.x  ) && intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) ; 
}
 
vector<seg> a ;
int n ;
 
set<seg> s  ; 
 
bool check(int m ){
  s.clear();
  vector<event> e ;
  for (int i = 0 ; i <= m ; i++){
    e.push_back(event(min(a[i].p.x, a[i].q.x), 0, i));
    e.push_back(event(max(a[i].p.x, a[i].q.x), 1, i)) ;
  }
  sort(e.begin(), e.end()) ;
  for (auto &u : e){
    if (!u.k ){
      auto nxt = s.lower_bound(a[u.id]) ; 
      auto prv = nxt ; 
      if (prv != s.begin()) --prv ; 
      if (prv != s.end() && intersect(*prv, a[u.id]) || nxt != s.end() && intersect(a[u.id], *nxt)   ) return false  ;
      s.insert(nxt, a[u.id])  ; 
    } else {
      s.erase(s.find(a[u.id])) ;
     }
  }
  return true ;
  
}
 
pt cut(const seg &a, const seg &b){
  if (a.p.y == a.q.y){
    return { a.p.x < a.q.x ? min(b.p.x, b.q.x) : max(b.p.x, b.q.x) , a.p.y  } ; 
  }
 
  return { a.p.x, a.p.y < a.q.y ? min(b.p.y, b.q.y) : max(b.p.y, b.q.y)  } ;
 
}
 
int calc(pt &a , pt &b) {
  return abs(a.x - b.x) + abs(a.y-b.y) ;
}
 
int main() {
  ios_base::sync_with_stdio(0); 
  cin.tie(0), cout.tie(0) ;
  cin >> n ; 
  LL x = 0 , y = 0 ;
  a.resize(n+1) ;
  for (int i = 0 ; i < n ; i++){
    char c; int w ;
    cin >> c >> w; 
    int m = c == 'R' ? 1 : c == 'L' ? -1 : 0,
        n = c == 'D' ? -1 : c == 'U' ? 1 : 0 ; 
    LL X = x + m * w , Y = y + n * w ; 
    if (i) {x += m, y +=n ; }  
    a[i].p = {x,y} , a[i].q = {x=X,y=Y} ;
  }
 
  int l = 0 ;
 
  for (int k = n ; k ; k>>=1)
    for(; l + k < n && check(l+k) ; ) l+=k ; 
 
  LL res = 0 ;
  for (int i = 0 ; i <= l ;i++) {
   if (i) a[i].p = a[i-1].q ; 
   res += calc(a[i].p, a[i].q) ; 
  }
  int last = l + 1 < n && !intersect(a[l], a[l+1]) ? 1e9 : 0 ;
 
  a[l+1].p = a[l].q; 
  a[n].q = a[n].p ; 
 
  for (int i = 0 ; i < l ; i++){
    if (intersect(a[l+1] , a[i] )) {
      pt p = cut(a[l+1], a[i]) ; 
      last = min(last,  calc(a[l+1].p, p)) ;
    }
  }
  cout << res + last ;
}