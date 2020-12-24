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
#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
#define prl cerr<<"called: "<< __LINE__ << endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b, ll e ,ll m) {
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
    if (e & 1) ans = ans * b % m;
  return mod(ans,m);
}

struct dado{
  int x;
  ll last;
  int id;
  dado(){}
  dado(int X,ll Last,int Id){
    x = X;
    last = Last;
    id = Id;
  }
  bool operator<(const dado& o)const{
    if(x!=o.x)return x < o.x;
    if(last!=o.last)return last < o.last;
    return id < o.id;
  }
};

//set<pair<ll,dado> > heap;
const ll inf = (ll)1e9;

map<ll,set<dado> > heap;

dado best(dado op1,dado op2,int pos){
  
  /*
  db3(op1.x,op1.last,op1.id);
  db3(op2.x,op2.last,op2.id);
  */
  
  if(abs(op1.x - pos) != abs(op2.x-pos) ){
    if(abs(op1.x-pos) > abs(op2.x-pos))return op2;
    return op1;
  }
  if(op1.last!=op2.last)return (op1.last<op2.last ? op1 : op2);
  return (op1.id < op2.id ? op1 : op2);
}

int32_t main(){
  fastio;
  int n,k,m;
  cin >> n >> k >> m;
  set<dado> taxis; 
  for(int i=1;i<=k;i++){
    int x;
    cin>>x;
    taxis.insert(dado(x,0,i));
  }
    
  int ITER=0;//TIRAR ISSO!!!!
  auto kill = [&]() -> void{
    ITER++;
    if(ITER > 10)exit(0);
  };
  while(m--){
    ll t,a,b;
    cin>>t>>a>>b;
    while(!heap.empty() and heap.begin()->ff<=t){

      auto it = heap.begin();

      dado d = *((it->ss).begin());
      
      (it->ss).erase(d);
      
      if((it->ss).empty()){
        heap.erase(begin(heap));
      }
      taxis.insert(d);
    }
    ll resT = 0;
    dado res;
    if(taxis.empty()){
     // cerr <<"CASO1"<<endl;
      ll tempo = heap.begin()->ff;
      auto& Set = heap.begin()->ss;

      auto it1 = Set.lower_bound(dado(a,-1,-1));
      dado op1 = dado(-inf,inf,inf);
      dado op2 = dado(-inf,inf,inf);
      auto it2 = it1;
      if(it1 != Set.end()){
        op1 = *it1;
        //cout<<"op1 "<<op1.id<<endl;
      }
      if(it2!=Set.begin()){
        it2 = prev(it2);
        ll X = it2->x;
        it2 = Set.lower_bound(dado(X,-1,-1));
        
        if(it2!=Set.end())
          op2 = *it2;

      }

      res = best(op1,op2,a);
      resT = tempo - t + abs(res.x - a);
      Set.erase(res);
      
      if(Set.empty())
        heap.erase(begin(heap));

    }else{
     // cerr<<"CASO2"<<endl;
      auto& Set = taxis;

      auto it1 = Set.lower_bound(dado(a,-1,-1));
      dado op1 = dado(-inf,inf,inf);
      dado op2 = dado(-inf,inf,inf);
      auto it2 = it1;
      if(it1 != Set.end()){
        op1 = *it1;
      }
      if(it2!=Set.begin()){
        it2 = prev(it2);
        ll X = it2->x;
        it2 = Set.lower_bound(dado(X,-1,-1));
        
        if(it2!=Set.end())
          op2 = *it2;

      }
      res = best(op1,op2,a);
      resT = 0 + abs(res.x - a);
      
      Set.erase(res);

    }

   // db3(res.x,res.last,res.id);

    cout << res.id<<" "<<resT<<endl;


    ll novoT = t + resT + abs(a - b);
    res.last = novoT;
    res.x = b;
    heap[novoT].insert(res);
  }



  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
