/* Uses pentaghonal numbers to calculate p[0...n] mod M
 * O(N*sqrt)
 * Status: Tested on https://judge.yosupo.jp/problem/partition_function
*/
p[0] = 1;
  for(int i=1;i<=n;i++){
    p[i] = 0;
      for(int it=-1;it<=1;it+=2){
          for(int K=1;;K ++){
              int k = K*it;

              if(k*(3*k-1)/2 > i)break;
              ll cur = p[i - (k*(3*k-1)/2)];
              if((k-1)%2)cur = -cur;
              p[i] = p[i] + cur;
              if(p[i]<0)p[i]+=M;
              if(p[i]>=M)p[i]-=M;
          }
      }
  }
