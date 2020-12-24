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
  Tested on https://codeforces.com/gym/102411/problem/C and https://cses.fi/problemset/task/1693
*/


int g[N]; 
vector<pii> grafo[N];
vi tour;
int del[N]; // N = max(n,m) !!!
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
            // tour_e.pb(x.ss) ;
            pilha.pop_back();
            continue;
        }
        auto v = grafo[x].back();
        grafo[x].pop_back();
        g[x] --;
        del[v.s] = 1;
        pilha.pb(v.f);
        // pilha.pb(v)
    }
}

// USAGE:
int ID = 0;
void addEdge(int a,int b,int direcionado = 1){
  ID++;
  grafo[a].pb(pii(b,ID));
  g[a]++;
  if(!direcionado){
    grafo[b].pb(pii(a,ID));
    g[b]++;
  }
}
//
find(inicio);
