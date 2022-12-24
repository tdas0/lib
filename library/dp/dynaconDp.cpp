/** Author: Naim
  * Description: d&c optimizaion for when you want the value without the i-th value
  * Useful for when rollback is not possible. ex: double, max, min
  * O(NlogN * O(add))
  * Status: tested on https://codeforces.com/contest/303/problem/E
  */ 

void copy(...){...}

void addRange(int l,int r){
  rep(i,l,r+1)add(i); // add i-th element to dp state
}

void calc(int l,int r){
  if(l==r){
    // dp ignoring l-th value
    return; 
  }

  int m = (l+r)/2;
  vector< ... > save;
  
  copy(dp,save);
  addRange(l,m);
  calc(m+1,r);
  
  copy(save,dp);
  addRange(m+1,r);
  calc(l,m);
}
