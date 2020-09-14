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
