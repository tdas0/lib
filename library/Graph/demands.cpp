/* Fluxo com demandas
* Complexity: O(Dinic)
* Author: common knowledge
* Status: tested on ASC1 B
* Dinic() precisa ter id na struct (modificar o addEdge pra receber(a,b,cap,id))
* Capacidade do fluxo
* Resolve pra arestas que tem lower bound e upper bound o maxflow
* consegue resolver também pra demanda nos nós, h[x] representa a demanda do nó x
*/


class Demands{
public:
	Demands(int n){
		this->n = n;
		source = n + 1,  sink = n + 2;
		h = vi(n+3, 0);
		flow = Dinic(n+3);
	}
	void addEdge(int a , int b , int c , int d , int i){
		h[a] -= c;
		h[b] += c; 
		flow.addEdge(a,b,d-c,i);
	}
	bool solve(){
		int dx = 0 , sx = 0;
		for(int i = 1 ; i <= n; i ++){
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