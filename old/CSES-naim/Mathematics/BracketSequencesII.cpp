  int n;
  cin >> n;
  string s;
  cin >> s;
  int k=sz(s);
  int op=0,t=0;
  rep(i,0,sz(s)){
    if(s[i]=='(')op++,t++;
    else op--;
  if(op<0)return cout<<0<<endl,0;
  }
  if(n&1)cout <<0<<endl;
 
  else{
    n/=2;
 
    int right = n - t;
    int up = n - (k - t);
    int res = C(up + right,up) - C(up + right,up+1);
    cout << mod(res,M) << endl;
 
  }