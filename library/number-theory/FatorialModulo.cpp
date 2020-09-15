/* Author: Common Knowledge
 * Description: Acha n! modulo P, mas tirando os fatores P.
 * Res = n!modP , e = expoente de P
 * O(log_p(N))
 * Status: tested on Petrozavodsk Summer-2008. Warsaw U Contest - problem B
 */
void fatorial(ll n,int p,ll &res,ll &e){
  e=0;
  ll nn = n;
  res = 1;
  while(nn){
    res = 1ll * res * fat[nn%p]%p;
    e+=(nn/p);
    nn/=p;
  }
  if(e&1)res = res * (p-1)%p;
  return;
}

// for a modulo p^k , w.ff = p, k = w.ss
// tested on 2019-2020 ICPC Asia Taipei - divmod
// mod == p^k
ll factorial_without_factor(ll n , auto w , ll mod){
	vl fat(mod+10);
	ll p = w.first;
	ll k = w.second;
	ll a = 1;
	for(int i=0;i<k;i++)a*=p;
	fat[0] = 1;
	ll ans = 1;
	for(int i=1;i<mod;i++){
		fat[i] = fat[i-1];
		if(i%p==0)continue;
		fat[i] = (i*fat[i-1])%mod;
	}
 
	while(n){
 
		ll cic = n/mod;
		ans = (ans * modpow(fat[mod - 1],cic,mod))%mod;
		ans%=mod;
		ans = (ans * fat[n%mod])%mod;
		n/=p;
	}
	return ans;
}
