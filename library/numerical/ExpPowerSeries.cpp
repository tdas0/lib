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
