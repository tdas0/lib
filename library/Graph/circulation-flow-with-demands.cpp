/* Fluxo com demandas. Resolve o problema da circulação: Achar fluxo (entrada = saida) que satisfaz demandas,
* sem necessariamente uma sink e source. Para forçar sink/source adicionar aresta da source pra sink com
* capacidade infinita.
* Complexity: O(Dinic)
* Author: common knowledge
* Status: tested on ASC1 B and XXII Open Cup. Grand Prix of Seoul problem I and ABC 285-G
* Dinic() precisa ter id na struct (modificar o addEdge pra receber(a,b,cap,id)) caso queira recuperar
* os fluxos nas arestas. Deixar ids invalidos nas arestas extras e nas arestas do grafo residual
* Resolve pra arestas que tem lower bound e upper bound o maxflow
* consegue resolver também pra demanda nos nós, h[x] representa a demanda do nó x
* Consegue resolver para mincost.
* Para mincost-maxflow primeiro ache o fluxo máximo m. Depois adicionar edge: (source,sink,lower = m,upper = m,custo = 0)
*/


class Demands{
public:
	Demands(int n){
		this->n = n;
		source = n + 1,  sink = n + 2;
		h = vi(n+3, 0);
		flow = Dinic(n+3);
	}
	void addEdge(int a , int b , int L , int R , int i){
		h[a] -= L;
		h[b] += L; 
		flow.addEdge(a,b,R-L,i);
	}
	bool solve(){ // solve(s,t) se tiver source/sink
		// forçar que possa circular o máximo de fluxo entre sink e source:
		// addEdge(t,s,0,inf,300000); 
		int dx = 0 , sx = 0;
		for(int i = 0 ; i <= n; i ++){ // 0-index?
			if(h[i] < 0){
				flow.addEdge(i,sink,-h[i],300000);
				sx += -h[i];
			}
			else if(h[i] > 0){
				flow.addEdge(source,i,h[i],300000);
				dx += h[i];
			}
		}
		if(flow.calc(source, sink) != sx || sx != dx){
			return 0;
		}
		return 1;
	}
private:
	vi h;
	Dinic flow;
	int source , sink , n;
};
