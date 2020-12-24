/**
 * Author: Tiago Domingos
 * Date: 14/02/2020
 * Description:
	Retorna o matching bipartido de um grafo com partições de tamanho N(esquerda) e M(direita)
	addLR(x,y) aresta do lado esquerdo(x) para lado direito(y)
	addRL(x,y) aresta do lado direito(x) para lado esquerdo(y)
	solve() retorna maior matching
	matchL(x) retorna o valor que o cara x do lado esquerdo ta pareado com, ou 0 caso contrario
	matchR(x) retorna o valor que o cara x do lado direito  ta pareado com, ou 0 caso contrario
 * Status: tested 
 * Time: O?? (passa pra 1e6)
*/



struct bipartite_match{ // 1 indice
	int n , m;
	vector<vi> g; vi vis , match;
	bipartite_match(int n , int m) : n(n) , m(m), vis(n+m+2) , match(n+m+2) , g(n+m+2){}
	void addLR(int x , int y){ // aresta da esquerda pra direita
		g[x].push_back(y + n);
		return ;
	}
	void addRL(int x , int y){ // aresta da direita pra esquerda
		g[x+n].push_back(y);
		return ;
	}
	bool dfs(int x){
		allin(w,g[x]){
			if(vis[w]) continue;
			vis[w] = true;
			if(match[w] == 0 || dfs(match[w])){
				match[w] = x, match[x] = w; 
				return true;
			}
		}
		return false;
	}
	int solve(){
		int ans = 0; bool haspath;
		do{
			haspath = false;
			fill(all(vis) , false);
			for(int i = 1 ; i<= n + m; i ++){
				if(!match[i] && dfs(i)) haspath = 1 , ans ++ ;
			}
		} while(haspath);
		return ans;
	}
	int matchL(int x){return (match[x] ? match[x] - n : 0);}
	int matchR(int x){return match[x+n];}
};