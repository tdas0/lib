/**
 * Author: tiago
 * Date: 2020-03-22
 * Description: acha um ciclo em um grafo funcional em o(1) de memoria
 * modificar nxt(x) pra o vizinho do nó x , Start pro valor inicial 
 * Time: O(Tail + Period) , memory: O(1)
 * Status:tested
 */

class cycle_finding{
public:
	const ll M = 1LL<<40;	
	const ll START = 0x600DCAFE;
	ll nxt(ll x){
		return (x + (x>>20LL) + 12345ll)%M;			
	}
	pair<ll,ll> find(){
		ll x = nxt(START) , y = nxt(x);
		while(x != y){
			x = nxt(x);
			y = nxt(nxt(y));
		}
		ll tail = 0;
		x = START;
		while(x != y){
			x = nxt(x);
			y = nxt(y);
			tail++;
		}
		ll period = 1 ; x = nxt(x);
		while(x != y){
			x = nxt(x);
			period++;
		}
		return {tail, period};
	}
};
