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
*/

int g[N];
vector<pii> grafo[N];
vi tour;
int del[N];
inline void find(int u){
    vector<int>pilha;
    pilha.pb(u);
    while(!pilha.empty()){
        int x = pilha.back();
        while(!grafo[x].empty() and del[grafo[x].back().s]){
            g[x]--;
            grafo[x].pop_back();
        }
        if(!g[x]){
            tour.pb(x);
            pilha.pop_back();
            continue;
        }
        auto v = grafo[x].back();
        grafo[x].pop_back();
        g[x] --;
        del[v.s] = 1;
        pilha.pb(v.f);
    }
}

