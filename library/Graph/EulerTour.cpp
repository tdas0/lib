/**
 * Author: Matheus Leal
 * Date: 2020-01-15
 * Description: Achar um Euler TOur
 * Time: O(N + M)
 * Usage: 
 * Status:tested
 */

/*
  grafo[x] guarda um pair (v, w) indicando que uma aresta liga (x, v) e possui id = w
  g[x] = grau do vertice x
  tour = ciclo do tipo [comeco] ... [comeco]
  del[x] = (1, se aresta ja foi utilizada. 0 caso contrário)
  tour_e = ids das arestas usadas . se necessário, trocar vector<int> pilha para vector<pii> pilha
  ver comentarios para isso ^
  caso seja um tour incompleto ([comeco] ... [fim]) lembrar de dar reverse no tour
  funciona com self loop (mas deve aumentar em 2 o grau/botar 2 vezes no grafo) -> tested on 527E - #296 div2
  Se for incompleto e direcionado lembrar de ver que degOut[incio] - degIn[inicio] == 1, degIn[fim] - getOut[fim]==1
  E degIn[i] == degOut[i] para todo o resto. 
  DA REVERSE NO TOUR
  Tested on https://codeforces.com/gym/102411/problem/C and https://cses.fi/problemset/task/1693
*/


class EulerTour{	
public:
	vi tour , tour_e;
	EulerTour() = default;
	EulerTour(int _n , bool _directed){ 
		dg.assign(_n+1,0);
		g = vector< vector<pii> >(_n+1);
		directed = _directed;
	}
	void addEdge(int a, int b){
		int id = sz(del);
		g[a].push_back({b,id});
		del.push_back(0);
		dg[a]++;
		if(!directed){
			g[b].push_back({a,id});
			del.push_back(0);
			dg[b]++;
		}
	}
	void find(int start){
	    vector<int> pilha = {start};
	    while(sz(pilha)){
	        int x = pilha.back();
	        while(sz(g[x]) and del[g[x].back().second]){
	            dg[x]--;
	            g[x].pop_back();
	        }
	        if(!dg[x]){
	            tour.push_back(x); 	 // tour_e.push_back(x.second) ;
	            pilha.pop_back();
	            continue;
	        }
	        auto v = g[x].back();
	        g[x].pop_back();
	        dg[x] -- , del[v.second] = true;
	        pilha.push_back(v.first); 	    // pilha.push_back(v)
	    }		
	}
private:
	vi dg , del;
	vector< vector<pii> > g;
	bool directed = true;
};
