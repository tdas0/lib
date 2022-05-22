// Other aprroachs:
// Boruvka:
// Add everyone in the trie. Remove current component
// For everyone get the smallest, insert back to trie
// Connect while comps > 1
// This Aprroach:
// Divide & Conquer; Connect first with the maximum common prefix


const int N = 100100;
const int MAXL = 30;


map<int,int> rev; 
vi g[N];
int w[N];
int trie[N * (MAXL + 1)][2];
int num = 1;
int valor[N*(MAXL+1)];
void add(int v,int id){
	int no = 1;
    for(int i=MAXL;i>=0;i--){
		int b = v>>i&1;
		if(!trie[no][b])trie[no][b] = ++num;
		no = trie[no][b];
	}
	valor[no] = v;
}

int find_mn(int v,int change){
	int no=1;
	int resp=0;
	for(int i=MAXL;i>=0;i--){
		int b = v>>i&1;
		if(i!=change && trie[no][b])
			no = trie[no][b];
		else
			no = trie[no][b^1];
	}
	return valor[no];
}

int build(int no,vi &v,int H){
	if(v.size()==0)return 0;
	if(H<0){
		for(int i=0;i+1<v.size();i++){
			
			g[v[i]].push_back(v[i+1]);
			g[v[i+1]].push_back(v[i]);
		}
		return 1;
	}
	vi nv[2];
	for(int i : v)nv[w[i]>>H&1].push_back(i);
	int a = build(trie[no][0],nv[0],H-1);
	int b = build(trie[no][1],nv[1],H-1);
	if(a && b){
		int i = 0;
		if(nv[a].size() > nv[b].size())i=1;
		pii mn = pii(inf,inf);
		for(int id : nv[i]){
			int to = find_mn(w[id],H);
			mn = min(mn,pii(to^w[id],id));
		}
		int id = mn.ss;
		int v_to = mn.ff ^ w[id];
		int to = rev[v_to];
		g[id].push_back(to);
		g[to].push_back(id);
	}
	return 1;
}
