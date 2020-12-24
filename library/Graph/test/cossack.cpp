#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
const int N = 2000005;
// begin of GRAPH::
struct edge{
	int x , id; 
};
template <int SZ> class graph{
public:
	int grau[SZ+1];
	vector<edge> g[SZ+1];
	void add_edge(int x,int y,int id){
		g[x].push_back({y,id});
		grau[y]++;
	}
	vector<edge>* operator[](int id){
		return &g[id];	
	}
	int dg(int x){
		return grau[x];
	}	
};
// end
graph<N> grafo; vi tour;
int del[N];
set<pair<int,int> > ff; 
void find(int u){
    vector<int> pilha;
    pilha.push_back(u);
    while(!pilha.empty()){
        int x = pilha.back();
        while(!(*grafo[x]).empty() and del[(*grafo[x]).back().id]){
            grafo.grau[x] -- , (*grafo[x]).pop_back();
        }
        if(!grafo.grau[x]){
            tour.push_back(x) , pilha.pop_back();
            continue;
        }
        auto v = (*grafo[x]).back();
        (*grafo[x]).pop_back();
        grafo.grau[x]--;
        del[v.id] = 1;
        pilha.push_back(v.x);
    }
}
vector<pair<int,int> > edges;

int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	#define endl '\n'
	int n , m;
	cin >> n >> m ;
	for(int i = 1, x , y ; i <= m ; i ++ ){
		int a , b;
		cin >> a >> b;
		edges.push_back({min(a,b) , max(a,b)}) ;
		grafo.add_edge(a , b ,i);
		grafo.add_edge(b , a ,i);			
	}
	for(int i = 1; i <=n ; i ++){
		if(grafo.grau[i]%2 == 0) continue;
		grafo.add_edge(0,i, m+i);
		grafo.add_edge(i,0, m+i);
	}
	vector<pair<int,int> > ans;
	for(int st = 0 ; st <= n ; st ++ ){
		find(st);
		vi rem(tour.size()+ 1,0); 		
		for(int i = 1 ; i < tour.size() - 1 ; i += 2){
			int x = tour[i] , y = tour[i+1];		
			int u = (i>=1 ? tour[i-1] : -1) , v = (i+2 < tour.size() ? tour[i+2] : -1);
			if(!x || !y) rem[i] = 1; 
			else{
				if(!u && !rem[i-1]) rem[i-1] = 1;
				else if(!v) rem[i+1] = 1;
				else  ff.insert({min(x,y),max(y,x)}), rem[i] = 1;
			}
		}
		tour.clear();
	}
	for(auto w :edges){
		if(!ff.count(w)) ans.push_back(w);
	}
	cout << ans.size() << endl;
	for(int i = 0 ; i < ans.size() ; i ++){
		cout << ans[i].first <<" " << ans[i].second << endl;
	}
}
