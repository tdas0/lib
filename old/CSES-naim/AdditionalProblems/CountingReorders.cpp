// numero de permutacoes sem ter 2 adjacentes iguais
  string s;
  cin >> s;
  map<char,int> mp;
  int mx=0;
  for(auto it : s)mp[it]++;
  for(auto it : mp)mx=max(mx,it.ss);
  if(sz(s)==1){
    cout << 1 << endl;
    return 0;
  }
  if(mx  > (sz(s) + 1)/2){
    cout << 0 << endl;
    return 0;
  }
  init();
  vector<Mint> dp(1);
  dp[0] = 1;
  for(auto it : mp){
    int f = it.ss;
    vector<Mint> nv(f + sz(dp),0);
    rep(i,1,f+1)rep(j,0,sz(dp)){
      nv[i+j]+=dp[j] * C(f-1,i-1) * C(i+j,i);
    }
    dp = nv;
  }
  Mint ans=0;
  rep(i,0,sz(dp)){
    ans+=((sz(s) - i)%2==0 ? 1 : -1) * dp[i];
  }
  cout << ans << endl;