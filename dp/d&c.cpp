/* Source: cp-algorithms
 * Complexity: O(N*K*log(N)*cost())
 * Needs to be monotonic
 * !! compute(1,n,1,n) vs compute(i,n,i,n)  
 * Tested on https://codeforces.com/contest/321/submission/81919245
*/

vector<long long> dp_before(N), dp_cur(N);
const int inf = ;
 
long long cost(int l,int r); 
 
// compute dp_cur[l], ... dp_cur[r] (inclusive) 
void compute(int l, int r, int optl, int optr)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    pair<int, int> best = {inf, -1}; // se for maximizar muda pra -inf
  
    rep(k,optl,min(mid,optr)+1){
        best = min(best, { dp_before[k-1] + cost(k,mid), k});
    }
 
    dp_cur[mid] = best.first;
    int opt = best.second;
 
    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

void init(){
   rep(i,1,n+1){
    dp_before[i] = cost(1,i);
  }
 
  rep(i,2,k+1){
    rep(j,i,n+1)dp_cur[j] = inf;
    compute(i,n,i,n);
    swap(dp_cur,dp_before);  
  }
  
}
