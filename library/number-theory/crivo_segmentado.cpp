/* Author: Common knowledge
 * Descrição: Crivo para decompor numeros no range [L,R] , R<=10^12 para casos de R-L pequeno i.e R-L<=1e6
 * Precisa precomputar os primos menores que sqrtR com outro crivo
 * Após o crivo, mark[i-l] tem 1 se i não for primo, caso contrário, mark[i-l] é um primo.
 * Status: Tested on Petrozavodsk Summer-2017. Songyang Chen Contest 1 - problem C
 */
const int N = 1e6 + 100; // N>=sqrt(MaxR)
ll mark2[N]; 
bool mark[N];
vi pr;
void crivo(){ // mark deve estar zerado
	for(int i=2;i<N;i++){
		
		if(!mark[i]){
			pr.pb(i);
			for(int j=2*i;j<N;j+=i){
				mark[j]=1;
			}
		}
	}
}

void crivo_segmentado(ll l,ll r){
	crivo();
  
	for(ll i = l;i<=r;i++){
		mark2[i-l] = i;
		ans[i-l] = 1;
	}

	for(ll p : pr){
	  
		for(ll i = (l + p -1)/p * p ;i<=r;i+=p){
			ll cnt =0;
			while(mark2[i-l]%p==0){
				mark2[i-l]/=p;
				cnt++;
			}
			ans[i-l] = ans[i-l]*(cnt + 1)%M; // exemplo -> qtd de divisores de i
		}
	}
	
	for(ll i = l;i<=r;i++){
	  if(mark2[i-l]!=1){//é um primo > Sqrt
		ans[i-l] = ans[i-l] * (1 + 1) %M;    
	  }
	}
  
}
