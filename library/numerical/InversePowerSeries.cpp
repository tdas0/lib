/**
 * Author: Tiago
 * Description: Acha o inverso de uma série formal até o n-ésimo termo. A[0] != 0 para existir inverso.
 * Time: O(N \log N)
 * Status: testado em https://judge.yosupo.jp/problem/inv_of_formal_power_series
 */


vl inverse(vl A , int n){
	assert(sz(A) != 0 && A[0] != 0);
	vl cur = {modpow(A[0] , mod-2 , mod)};
	auto fix = [&](vl v , int n) -> vl{
		vl ans(n,0);
		for(int i = 0 ; i < min(n , sz(v)) ; i ++)
			ans[i] = v[i];
		return ans;
	};
	for(int step = 0 ; (1<<step) < n ; step ++ ){
		vl B = conv(fix(A,(1<<(step+1))) , cur);
		for(auto &w : B){
			w = (mod - w);
		}
		B[0] = (B[0] + 2)%mod;
		cur = fix(conv(cur , B),1<<(step+1));
	}
	return fix(cur,n);
}
