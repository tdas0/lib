/**
 * Author: tdas
 * Complexity: $O(N \log^2N)$ ?
 * Description: Given a power series $A = \sum x^i \cdto A_i$, find $e^A mod x^{n+1}$ i,e. the first
 * $n$ terms of the exponential
 * Useful for generating functions. Example:
 * If A(x) is a EGF, then $C(x) = A(x)^k$ is 
 * $c_{n} = \sum_{i_{1}+i_{2}+...+i_{k}=n}\frac{n!}{i_{1}!i_{2}!...i_{k}!}a_{i_{1}}a_{i_{2}}...a_{i_{k}}$
 * Which is basically summing all the ways to select $k$ elements. Example: Permutation with $k$ cycles. 
 * $A(x) = \sum \frac{(n-1)!}{n!}x^n$, because there are $(n-1)!$ permutations with exaclty 1 cycle. The extra $n!$ is added to due
 * The definition of EGF. Note that $C(x) = A(x)^k$ is the same as $C(x) = exp(k \cdot ln(A))$.
 * Example 2: 
 * Number of permutations where each cycle size is in $ S $. 
 * Use $\sum_{k \ge 0}\frac{1}{k!}C(x)^{k} = [x^{n}]\exp(C(x))$, which basically sums over all possible number of cycles $k$.
 * Here, $c_i = 1$ iff $i$ is in $ S $.
*/


// #include ... LogPowerSeries.cpp
vl exp(vl A , int n){
	assert(A[0] == 0 && sz(A));
	vl ans = {1};
	auto ha = ln(ans,n);
	for(int step = 0 ; (1<<step) < n ; step ++){
		auto P = ln(ans , (1<<(step+1)));
		auto Q = fix(A , (1<<(step+1)));
		for(int i = 0 ; i < (1<<(step+1)) ; i ++){
			Q[i] = (Q[i] - P[i] + (i == 0 ? 1 : 0)) % mod;
			if(Q[i] < 0)
				Q[i] += mod;
		}
		ans = fix(conv(ans,Q),(1<<(step+1)));
	}
	return fix(ans , n);
}
