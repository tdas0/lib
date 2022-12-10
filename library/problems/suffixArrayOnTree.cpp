#include <bits/stdc++.h>
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define all(v) v.begin(),v.end()
#define sz(v) ((int)v.size())
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
using namespace std;
typedef vector<int> vi;
typedef long long ll;

const int N = 200100;
const int MAXL = 18;
int op[N];
int c[N];

int trie[N][26];
int curId=0;

int ans[MAXL][N];
int rnk[MAXL][N];
int H[N];
int sa[N];
int lcp[N];

int cmp(int id1,int id2,int j){
    if(!j)return rnk[j][id1] < rnk[j][id2];
    if(rnk[j-1][id1]!=rnk[j-1][id2]){
      return rnk[j-1][id1] < rnk[j-1][id2];
    }
    return rnk[j-1][ans[j-1][id1]] < rnk[j-1][ans[j-1][id2]];
}
int eq(int id1,int id2,int j){
  return !cmp(id1,id2,j) && !cmp(id2,id1,j);
}

int getLcp(int id1,int id2){
  int tot=0;
  for(int j=MAXL-1;j>=0;j--){
    if(rnk[j][id1]==rnk[j][id2]){
      tot+=1<<j;
      id1 = ans[j][id1];
      id2 = ans[j][id2];
    }
  }
  return tot;
}

template<class T> struct RMQ { // floor(log_2(x))
  int level(int x) { return 31-__builtin_clz(x); } 
  vector<T> v; vector<vi> jmp;
  int comb(int a, int b) { // index of min
    return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); } 
  void init(const vector<T>& _v) { // 0-index
    v = _v; jmp = {vi(sz(v))}; iota(all(jmp[0]),0);
    for (int j = 1; 1<<j <= sz(v); ++j) {
      jmp.pb(vi(sz(v)-(1<<j)+1));
      rep(i,0,sz(jmp[j])) jmp[j][i] = comb(jmp[j-1][i],
                  jmp[j-1][i+(1<<(j-1))]);
    }
  }
  int index(int l, int r) { // get index of min element
    assert(l <= r); int d = level(r-l+1);
    return comb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
  T query(int l, int r) { return v[index(l,r)]; } // [l,r], 0-index
};
RMQ<int> rmq;
int fastLcp(int i,int j){
  if(i>j)swap(i,j);
  if(i==j)return H[sa[i]];
  return rmq.query(i+1,j);
}
int cnt[N];

int32_t main(){
  fastio;
  string s;
  cin >> s;
  string t;
  cin >> t;

  int n = sz(s);
  rep(i,0,n){
    op[i] = 1;
    c[i] = s[i]-'A';
  }
  rep(i,0,sz(t)){
    op[i+n]=(t[i]=='-' ? -1 : 1);
    c[i + n] = t[i]-'A';
  }
  ans[0][0] = 0;
  rnk[0][0] = 0;
  int id = curId;

  for(int i=0;i<sz(t)+sz(s);i++){
    if(op[i] == 1){
      if(!trie[id][c[i]]){
        trie[id][c[i]] = ++curId;
        H[curId] = H[id] + 1;
        ans[0][curId] = id;
        rnk[0][curId] = c[i] + 1;
      }
      id = trie[id][c[i]];
    }else id = ans[0][id];
  }

  n = curId;
  vector<int> ids,nids(n+1);
  rep(i,0,n+1)ids.pb(i);
  sort(all(ids),[&](int id1,int id2){
    return rnk[0][id1] < rnk[0][id2];
  });
  rep(j,1,MAXL){
    rep(i,0,n+1){
      ans[j][i] = ans[j-1][ans[j-1][i]];
    }
    sort(all(ids),[&](int id1,int id2){
      return cmp(id1,id2,j);
    });
    int curRnk = 0;
    for(int i=0;i<sz(ids);){
      int k = i;
      while(k + 1 < sz(ids) && eq(ids[k],ids[k+1],j)){
        rnk[j][ids[k]] = curRnk;
        k++;
      }
      rnk[j][ids[k]] = curRnk;
      i = k+1;
      curRnk++;
    }
  }

  // calculate LCP:
  rep(i,0,sz(ids)){
    sa[rnk[MAXL-1][ids[i]]] = ids[i];
  }
  // n = max(rnk) if tree is not a trie
  // (number of distinct strings)
  rep(i,1,n+1){
    lcp[i] = getLcp(sa[i-1],sa[i]);
  }
  // DEBUG:
  // rep(i,0,n+1){
  //   cout << sa[i]<<" "<<lcp[i]<<" ";
  //   string s="";
  //   int id = sa[i];
  //   while(id){
  //     s+=char(rnk[0][id]-1 + 'A');
  //     id = ans[0][id];
  //   }
  //   cout << s << "\n";
  // }
  {
  vector<int> _lcp;
  rep(i,0,n+1)_lcp.pb(lcp[i]);
  rmq.init(_lcp);
  }

  // Solve problem M: May I add a letter?
  set<int> act;
  
  auto get_count = [&](int id){
    auto pos = act.find(id);
    if(pos == act.begin())return 0;
    auto prv = prev(pos);
    if(prv==act.begin())return 0;
    auto pprv = prev(prv);
    return max(0,fastLcp(*prv,*pos) - fastLcp(*pprv,*prv));
  };

  act.insert(0);
  id = 0;
  ll resp=0;
  string curstr="";
  for(int i=0;i<sz(t)+sz(s);i++){
    if(op[i] == 1){
      curstr+=char(c[i]+'A');
      id = trie[id][c[i]];
      // add to set:
      auto nxt = act.lower_bound(rnk[MAXL-1][id]);
      int ct = 2;
      while(ct>0 && nxt!=act.end()){
        ct--,resp-=get_count(*nxt),nxt++;
      }
      act.insert(rnk[MAXL-1][id]);
      nxt = act.find(rnk[MAXL-1][id]);
       ct = 3;
      while(ct>0 && nxt!=act.end()){
        ct--,resp+=get_count(*nxt),nxt++;
      }
    }else{
      
      auto nxt = act.find(rnk[MAXL-1][id]);
      int ct = 3;
      while(ct>0 && nxt!=act.end()){
        ct--,resp-=get_count(*nxt),nxt++;
      }
      act.erase(rnk[MAXL-1][id]);
      nxt = act.lower_bound(rnk[MAXL-1][id]);
       ct = 2;
      while(ct>0 && nxt!=act.end()){
        ct--,resp+=get_count(*nxt),nxt++;
      }
      // remove from set:
      id = ans[0][id];
      curstr.pop_back();
    }
    if(i>=sz(s)-1)cout << resp << endl;
  }
  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
