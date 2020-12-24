/* Source: cp-algorithms
 * Complexity: O(N*K*log(N)*cost())
 * Needs to be monotonic
 * !! compute(1,n,1,n) vs compute(i,n,i,n)  
 * Tested on https://codeforces.com/contest/321/submission/81919245
 * Tested on https://codeforces.com/contest/868/problem/F
 * Usefull Strat: if is difficult to precompute all cost, one can use two pointers
 * Similar to MO's algorithm, resulting in O(K*Nlog\N) complexity, up only by a constant factor.
*/
struct DP{
	int n , inf; 
	vi dp[2];
	DP(int n , int inf) : n(n) , inf(inf) {dp[0] = vi(n+1) , dp[1] = vi(n+1);}
	int cost(int i,int j);
	// compute dp_cur[l], ... dp_cur[r] (inclusive) 
	void compute(int l, int r, int optl, int optr){
	    if (l > r) return;
	    int mid = l + (r-l)/2;
	    pair<int, int> best = {inf, -1}; // se for maximizar muda pra -inf
	    rep(k,optl,min(mid,optr)+1){
	        best = min(best, { dp[0][k-1] + cost(k,mid), k});
	    }
	    dp[1][mid] = best.first; int opt = best.second;
	    compute(l, mid - 1, optl, opt);
	    compute(mid + 1, r, opt, optr);
	}
	void solve(int k){
		rep(i,1,n+1){
			dp[0][i] = cost(1,i);
		}
		rep(i,2,k+1){
			rep(j,i,n+1) dp[1][j] = inf;
			compute(i,n,i,n) ;
			swap(dp[0] , dp[1]);
		}
	}
};
