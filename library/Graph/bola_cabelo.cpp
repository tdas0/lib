/*
  tripinha[x] = 1 se é tripa (nao ciclo) 0 caso contrário
  len_ciclo[x] = tamanho do ciclo que o x liga
  dist_ciclo[x] = distancia de x para o ciclo
  id_pai[x] = qual vértice partindo de x ta no ciclo
*/
//1-indexado
const int LOG = 20;

int vis[N];
int prox[N], grau[N], id_pai[N], dist_pai[N], dist_ciclo[N], len_ciclo[N];
int tripinha[N]; // um vértice é tripa se nao ta no ciclo xD
vector<int> chega[N];

// 1-indexado
struct bola_cabelo{
	int numVertices;
	
	void init(int numv = 0){
		numVertices = numv;
		// FICA NLOGN CASO FOR USAR BIN LIFT
	}
	void addAresta(int a, int b, int peso = 1){
		prox[a] = b; dist_pai[a] = peso;
		chega[b].pb(a);
		grau[b] ++;
	}
	void dfs(int x, int p){
		id_pai[x] = id_pai[p];
		dist_ciclo[x] = dist_ciclo[p] + dist_pai[x];
		len_ciclo[x] = len_ciclo[p];
		for(auto v: chega[x]) dfs(v, x);
	}
	void solve(){
		vector<int> lista;
		for(int i = 1; i <= numVertices; i++)
			if(!grau[i]) lista.pb(i);
		for(int i = 0; i < sz(lista); i++){
			int x = lista[i];
			tripinha[x] = 1; grau[prox[x]] --;
			if(!grau[prox[x]]) lista.pb(prox[x]);
		}
		for(int x = 1; x <= numVertices; x++){
			if(tripinha[x]) continue;
			id_pai[x]=x;
			for(auto v: chega[x]) if(tripinha[v]) id_pai[v] = x;
			if(vis[x]) continue;
			int y = prox[x], len = 1; vis[x]=1;
			vector<int> caras={x};
			while(y != x){
				vis[y]=1;
				caras.pb(y);
				len ++;
				y=prox[y];
			}
			for(auto w: caras) len_ciclo[w] = len;
		}
		for(int x = 1; x <= numVertices; x++){
			if(!tripinha[x] or tripinha[prox[x]]) continue;
			dfs(x,prox[x]);
		}
	}
  // Maior caminho começando em X sem repetir vertice
	int longest_path(int x){
		return len_ciclo[x] + dist_ciclo[x];
	}
};
