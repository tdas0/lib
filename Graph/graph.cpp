/**
 * Author: Tiago Domingos
 * Date: 2020-03-16
 * Description: Graph class
 * Usage: Graph<SZ> g; onde SZ o tamanho do grafo 
 * Modificar edge e add_edge juntos, originamente (x) , onde x == nó vizinho
 * pra usar, *g[x] retorna o vetor de arestas do x-esimo nó 
 * Status:tested
 */

struct edge{
	int x; 
};
template <int SZ> class graph{
public:
	vector<edge> g[SZ+1];
	void add_edge(int x , int y){
		g[x].push_back({y});
	}
	vector<edge>* operator[](int id){
		return &g[id];	
	}
};