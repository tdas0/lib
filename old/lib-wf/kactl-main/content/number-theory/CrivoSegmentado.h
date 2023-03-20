/**
 * Author: Common knowledge
 * Description: Crivo para decompor numeros no range [L,R] , $R<=10^12$
 * Precisa precomputar os primos menores que sqrtR com outro crivo
 * Após o crivo, mark[i-l] tem 1 se i não for primo, caso contrário, mark[i-l] é um primo.
 * Time: O(R-L + SQRT(R))
 * Status: Tested on Petrozavodsk Summer-2017. Songyang Chen Contest 1 - problem C
 */
const int N = 1e6 + 100; // N>=sqrt(MaxR)
bool mark[N];
vi pr;
void crivo_segmentado(ll l,ll r){
	//crivo(); jogando primos em pr
	for(ll i = l;i<=r;i++){
		mark2[i-l] = i;
		ans[i-l] = 1;
	}
	for(ll p : pr)
		for(ll i = (l + p -1)/p * p ;i<=r;i+=p){
			ll cnt =0;
			while(mark2[i-l]%p==0){
				mark2[i-l]/=p;
				cnt++;
			}
			ans[i-l] = ans[i-l]*(cnt + 1)%M; // exemplo -> qtd de divisores de i
		}
	for(ll i = l;i<=r;i++)
	  if(mark2[i-l]!=1)//eh um primo > Sqrt
		ans[i-l] = ans[i-l] * (1 + 1) %M;    
}
