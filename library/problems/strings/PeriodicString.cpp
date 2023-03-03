// Dada uma string s achar maior K tal que alguma substring eh
// concatenacao de K strings iguais
struct SuffixArray {
  //kactl
};

const int N = 4e5 + 100;
int pai[N];
int f(int x){
  return pai[x] = (pai[x]==x?x:f(pai[x]));
}
int best[N];
set<int> val[N];

void join(int a,int b){
  a=f(a),b=f(b);
  if(sz(val[a]) > sz(val[b]))swap(a,b);
  best[b] = min(best[b],best[a]);
  for(int x : val[a]){
    // smallest greater:
    auto it = val[b].upper_bound(x);
    if(it!=val[b].end() and *it != x)best[b] = min(best[b],abs(*it - x));
    
    // largest smaller:
    it = val[b].lower_bound(x);
    if(*it!=x)best[b] = min(best[b],abs(x - *it));
    if(it!=val[b].begin())it--;
    if(*it!=x)best[b] = min(best[b],abs(x - *it));
    val[b].insert(x);
  }
  //for(int x : val[a])val[b].insert(x);

  val[a].clear();
  pai[a] = b;
}
const int inf = 1e9;

int32_t main(){
  fastio;
  
  string s;
  cin>>s;

  SuffixArray sa(s);
  int n =sz(s);
  
  int ans = 1;
  vector<pii> inter;
  for(int i=1;i<=n;i++){
    inter.pb(pii(sa.lcp[i],i));
    ans = max(ans,1 + (sa.lcp[i]/abs(sa.sa[i] - sa.sa[i-1])));
  }
  for(int i=0;i<=n+1;i++)pai[i] = i,best[i] = inf;
  sort(all(inter),greater<pii>());

  for(auto seg : inter){
    int lcp = seg.ff;
    int id = seg.ss;
    int op1 = sa.sa[id-1],op2= sa.sa[id];
    
    if(op1 > op2)swap(op1,op2);
    
    val[id].insert(op1);
    val[id].insert(op2);  
    assert(op1 < op2);
    best[id] = op2 - op1;
    if(best[f(id-1)]!=inf)join(id,id-1);
    if(best[f(id+1)]!=inf)join(id,id+1);
    
    ans = max(ans,1 + lcp/(best[f(id)]));
  }
  cout << ans << endl;
}
