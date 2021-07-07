/*
  tripinha[x] = 1 se é tripa (nao ciclo) 0 caso contrário
  len_ciclo[x] = tamanho do ciclo que o x liga
  prefixo[x] = distancia de x para o ciclo(caso x for tripa), prefixo do ciclo caso x ta no ciclo
  id_pai[x] = qual vértice partindo de x ta no ciclo
*/
//1-indexado

int vis[N], tin[N], tout[N], total[N], tmp_cnt=0;
int componente[N], prox[N], grau[N], id_pai[N], dist_pai[N], dist_ciclo[N], len_ciclo[N];
int prefixo[N], tripinha[N]; // um vértice é tripa se nao ta no ciclo xD
vector<int> chega[N];
vector< vector<int> > tripas;

// 1-indexado
struct bola_cabelo{
	int numVertices;
	
	void init(int numv = 0){
		numVertices = numv;
	}
	void addAresta(int a, int b, int peso = 1){
		prox[a] = b; dist_pai[a] = peso;
		chega[b].pb(a);
		grau[b] ++;
	}
	void dfs(int x, int p){
		tin[x] = ++tmp_cnt;
		id_pai[x] = id_pai[p];
		len_ciclo[x] = len_ciclo[p]; componente[x]=componente[p];
		for(auto v: chega[x]){
			prefixo[v] = prefixo[x]+dist_pai[v];
			dfs(v, x);
		}
		tout[x] = tmp_cnt;
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
			int y = prox[x], len = 1, ant = x; vis[x]=1;
			int sum = dist_pai[x];
			prefixo[x] = 0;
			vector<int> caras={x};
			while(y != x){
				sum += dist_pai[y];
				vis[y]=1;
				caras.pb(y);
				len ++;
				y=prox[y];
			}
			reverse(all(caras));
			for(int i = 0; i < sz(caras); i++){
				if(!i) prefixo[caras[i]] = 0;
				else prefixo[caras[i]] = prefixo[caras[i-1]] + dist_pai[caras[i-1]];
				len_ciclo[caras[i]] = len;
				componente[caras[i]]=x;
				total[caras[i]] = sum;
			}
		}
		for(int x = 1; x <= numVertices; x++){
			if(!tripinha[x] or tripinha[prox[x]]) continue;
			prefixo[x] = dist_pai[x];
			dfs(x,prox[x]);
		}
	}
  // Maior caminho começando em X sem repetir vertice
	int longest_path(int x){
		return len_ciclo[x] + (tripinha[x]?prefixo[x]:0);
	}
	int menor_dist(int from, int to){
		if(componente[from] != componente[to]) return -1;
		if(id_pai[from] == id_pai[to] and tripinha[to] and tripinha[from] and tin[to] <= tout[from] and tout[from] <= tout[to]){
			if(prefixo[from] >= prefixo[to]) return prefixo[from] - prefixo[to];
			return -1;
		}
		if(tripinha[from] and !tripinha[to]){
			int cost = (prefixo[id_pai[from]] - prefixo[to]);
			if(cost < 0) cost += total[to];
			return prefixo[from] + cost;
		}
		if(!tripinha[from] and !tripinha[to]){
			if(prefixo[from] >= prefixo[to]) return prefixo[from] - prefixo[to];
			return total[from] - (prefixo[to] - prefixo[from]);
		}
		return -1;
	}
};
