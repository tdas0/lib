/*
    There are n
    people who want to get to the top of a building which has only one elevator. 
    You know the weight of each person and the maximum allowed weight in the elevator.
    What is the minimum number of elevator rides?
*/

  int n,x;
  cin>>n>>x;
  for(int i=0;i<n;i++){
    cin >> w[i];
  }
 
  for(int i=0;i<(1<<n);i++)dp[i] = pii(inf,0);
  
  dp[0] = pii(0,0);
 
  for(int msk = 0;msk<(1<<n);msk++){
 
    for(int j=0;j<n;j++){
      if(msk>>j&1)continue;
      // coloca o cara j na mask:
      if(dp[msk].ss + w[j] <=x){
        dp[msk|(1<<j)] = min(dp[msk|(1<<j)],pii(dp[msk].ff,dp[msk].ss + w[j]));
      }else dp[msk|(1<<j)] = min(dp[msk|(1<<j)],pii(dp[msk].ff + 1,w[j]));
      // cria uma nova:
 
    }
 
  }
 
  int res = dp[(1<<n) - 1].ff;
  if(dp[(1<<n)-1].ss > 0)res++;
  cout << res << endl;