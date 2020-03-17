#include <bits/stdc++.h>
using namespace std;
// graph class
struct edge{
	int x , y; 
};
template <int SZ> class graph{
public:
	vector<edge> g[SZ+1];
	void add_edge(int x , int y){
		g[x].push_back({x,y});
		g[y].push_back({x,y});
	}
	vector<edge>* operator[](int id){
		return &g[id];	
	}
};
// end
// lowlink dfs


// end of lowlink dfs



int32_t main(){

}