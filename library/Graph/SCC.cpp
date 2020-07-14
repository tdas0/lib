/**
 * Author: Tiago
 * Date: 2020-04-28
 * Description: Computa a SCC, comp[x] diz a componente que o nó x está, comps são as componentes
 * O(n)
 * Usage: SCC(lista de adjacencia, tamanho) (lista é 1 indice)
 * grafo indexado no 1
 * Status: tested
 */

struct SCC{
	vector< vi> g , comps;
	vi val, z, cont, comp;
	int Time =0, ncomps= 0 , n; 
	SCC(vector<vi> g, int n ):n(n) , g(g) , val(n+1,0), comp(n+1, -1) {}
	int dfs(int j){
		int low = val[j] = ++Time , x ; z.push_back(j);
		trav(e, g[j]) if(comp[e] < 0)
			low = min(low , val[e] ?: dfs(e));
		if(low == val[j]){
			do{
				x = z.back() ; z.pop_back();
				comp[x] = ncomps;
				cont.push_back(x);
			} while(x != j);
			comps.push_back(cont) , cont.clear();
			ncomps++;
		}
		return val[j] = low;
	}
	void scc(){
		val.assign(n+1,0); comp.assign(n+1,-1);
		Time = ncomps = 0 ;
		rep(i,1,n+1) if(comp[i] < 0 ) dfs(i);
	}
};