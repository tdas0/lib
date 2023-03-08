// A substring is called special if every character that appears in the string appears
// the same number of times in the substring.
// contar num
const int N = 200100;
int cnt[32];
int L[N];
int res[N];
 
 
array<int,30> get(vi S){ 
  array<int,30> dif = {0};
  rep(i,sz(S),30)dif[i]=0;
  rep(i,0,sz(S)){
    dif[i] = (cnt[S[0]] - cnt[S[i]]);
  }
  return dif;
}
int s[N];
int32_t main(){
  fastio;
  string t;
  cin >> t;
  int n = sz(t);
  rep(i,0,n)s[i] = t[i] - 'a';
  vi S;
  rep(i,0,n){
    L[i+1]=-1;
    S.pb(s[i]);
  }
  Unique(S);
  map<array<int,30>,int> mp;
  mp[get(S)] = 0;
  rep(i,1,n + 1){
    cnt[s[i-1]]++;
    if(mp.count(get(S))){
      L[i] = mp[get(S)];
    }
    mp[get(S)] = i;
  }
  ll tot=0;
  rep(i,1,n + 1){
    if(L[i]==-1)continue;
    res[i] = 1  + res[L[i]];
    tot+=res[i];
  }
  cout << tot << endl;
}