/**
 * Author: Naim
 * Description: adj[i] -> todos os vizinhos (grafo nao direcionado)
 * g[i] -> vizinhos de i tal que deg[i]>deg[j] ou deg[i] == deg[j] e i<j
 * deg[i] -> grau
 * int ok(int i,int j){return deg[i]==deg[j]?i<j:deg[i]>deg[j];}
 * if(ok(i,j))g[i].pb(j);else g[j].pb(i);
 * Time: O(MsqrtM)
 */
rep(i,0,n){
	// Quadrados:
	for(int to1 : g[i]){
		cnt[to1]=0;
		for(int to2 : adj[to1])
			cnt[to2]=0;
	}
	for(int to1 : g[i]){
		for(int to2 : adj[to1])if(ok(i,to2)){
			res+=cnt[to2]; // qtd de quadrados
			cnt[to2]++;
			if(res>=M)res-=M;
		}
	}
	// triangulo:
	for(int to : adj[i])vis[to]=1;
  	for(int to : g[i])for(int to2 : g[to])if(vis[to2])res++;
  	for(int to : adj[i])vis[to]=0;
}
