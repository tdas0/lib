/* Gaussin for Z_2
 * Author: Common knowledge
 * Status: Tested on https://codeforces.com/contest/662/problem/A
 */
const int MAXL = 20; // ~62 for long long
struct gaussXOR{
  int basis[MAXL]; // change to long long if needed
  gaussXOR(){
    for(int i=0;i<MAXL;i++)basis[i]=0;
  }
  
  bool can(int x){
    for(int i = MAXL-1;i>=0;i--){
      x = min(x,x^basis[i]);
    }
    return x==0;
  }

  void insert(int val){
    for(int i=MAXL-1;i>=0;i--){
      if(!(val&(1LL<<i)))continue;
      if(!basis[i]){
        basis[i] = val;
        return;
      }
      val^=basis[i];
    }
  }

  int maxi(){
    int x=0;
    for(int i = MAXL-1;i>=0;i--){
      if(!basis[i])continue;
      x = max(x,x^basis[i]);
    }
    return x;
  }
  int size(){
    int res=0;
    for(int i=0;i<MAXL;i++)if(basis[i])res++;
    return res;
  }

};
