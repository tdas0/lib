#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
/**
 * Author: Tiago Domingos
 * Date: 2020-03-16
 * Description: Graph class
 * Usage: Graph<> is the size of graph 
 * lca(x,y) e dist(x,y)
 * Status:tested
 */

struct edge{
	int x; // modifica com o que for útil
};
template <int SZ> class graph{
public:
	vector<edge> g[SZ+1];
	void add_edge(int x , int y){
		g[x].push_back(y);
	}
	vector<edge> operator[](int id){
		return g[id];	
	}
};


int32_t main(){
	graph<32> v;
	v.add_edge(1,3);
	for(auto w : v[1]){
		cout << (w.x ^ w.y  ^ 1) << endl;
	}	
}

