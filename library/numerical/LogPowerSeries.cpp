vl log(vl A , int n){
	assert(sz(A) != 0 && A[0] == 1);
	vl P(n,0) , ans(n,0);
	vl fat(n,1);
	for(int i = 1; i < n ; i ++){
		fat[i] = (fat[i-1] * i)%mod;
		P[i-1] = (A[i] * i) % mod;
	}
	vl F = conv(P,inverse(A,n));
	ll ifat = modpow(fat[n-1],mod-2,mod);
	for(int i = n-2 ; i >= 0; i --){
		ll cur = (ifat * fat[i])%mod;
		ifat = (ifat * (i+1))%mod;
		ans[i+1] = (F[i] * cur)%mod;
	}
	return ans;
}
